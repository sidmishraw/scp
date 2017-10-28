//============================================================================
// Name        : apriori.cpp
// Author      : sidmishraw, michael
// Version     :
// Copyright   : It's our copyright. Feel free to use it however you want.
// Description : C++ port of the https://github.com/bartdag/pymining/blob/master/pymining/seqmining.py module.
//============================================================================

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <time.h>

using namespace std;

// minimum support file
int min_support;

// for time profiling
long clockStart;
double runtimeAlgorithm;

// output result file
FILE *fpResult;

/**
 * Function to print vector
 */
string print_vec(vector<int>& v) {

	string s = "[";

	for (int i = 0; i < v.size(); i++) {

		s += to_string(v[i]) + " ";
	}

	s += "]";

	return (s);
}

/**
 * Function to print vectors
 */
string print_vec(vector<pair<int, vector<int> > >& v) {

	string s = "[";

	for (int i = 0; i < v.size(); i++) {

		s += "(" + to_string(v[i].first) + ", " + print_vec(v[i].second) + ") ";
	}

	s += "]";

	return (s);
}

/**
 * Function to print vectors
 */
string print_vec(vector<vector<int> >& v) {

	string s = "[";

	for (int i = 0; i < v.size(); i++) {

		s += print_vec(v[i]) + "\n";
	}

	s += "]";

	return (s);
}

/**
 * Function to print vectors
 */
string print_vec(vector<pair<int, int> >& v) {

	string s = "[";

	for (int i = 0; i < v.size(); i++) {

		s += "(" + to_string(v[i].first) + ", " + to_string(v[i].second) + ") ";
	}

	s += "]";

	return (s);
}

/**
 * Function to print vectors
 */
string print_vec(vector<pair<vector<int>, int> >& v) {

	string s = "[";

	for (int i = 0; i < v.size(); i++) {

		s += "(" + print_vec(v[i].first) + ", " + to_string(v[i].second) + ") ";
	}

	s += "]";

	return (s);
}

/**
 * Function to print vectors
 */
string print_vec(set<pair<vector<int>, int> >& v) {

	string s = "[";

	for (auto element : v) {

		s += "(" + print_vec(element.first) + ", " + to_string(element.second) + ") ";
	}

	s += "]";

	return (s);
}

/**
 * Computes the counts of the frequent items and puts them in the `freq_items` vector/list.
 *
 * @param &sdb : sequence database reference
 * @param *prefix : pointer to the prefix vector
 * @param min_support : minimum support threshold
 * @param *freq_items : list/vector of the frequent items and their respective counts
 */
void local_freq_items(vector<vector<int> >& sdb, vector<int>* prefix, int min_support,
                      vector<pair<int, int> > *freq_items) {

//	cout << "inside local_freq_items(): sdb=" << print_vec(sdb) << ", prefix=" << print_vec(*prefix) << ", min_support="
//	     << min_support << ", freq_items=" << print_vec(*freq_items) << endl;

	map<int, int> items;

	for (vector<vector<int> >::iterator entry = sdb.begin(); entry != sdb.end(); entry++) {

		vector<int> visited;

//		cout << "Now checking: " << print_vec(*entry) << endl;

		for (vector<int>::iterator element = entry->begin(); element != entry->end(); element++) {

//			cout << "Checking element: " << *element << endl;

			if (find(visited.begin(), visited.end(), *element) == visited.end()) {

				items[*element]++;
				visited.push_back(*element);
			}
		}

//		cout << "Visited: visited=" << print_vec(visited) << endl;
	}

	for (map<int, int>::iterator item = items.begin(); item != items.end(); item++) {

		int support = item->second;

		if (support >= min_support) {

			freq_items->push_back(make_pair(item->first, support));
		}
	}

//	cout << "Frequent items returning: " << print_vec(*freq_items);
}

/**
 * Generates the new sequence database taking into account the elements that occur after the
 * prefix in the original sequence database `sdb`.
 *
 * @param &sdb : sequence database reference
 * @param *prefix : pointer to prefix vector
 * @param *new_sdb : pointer to the newly created sequence database
 * that takes into account the elements occuring after the prefix
 */
void project(vector<vector<int> >& sdb, vector<int>* prefix, vector<vector<int> > *new_sdb) {

//	cout << "in project, sdb is:" << print_vec(sdb) << " and prefix is:" << print_vec(*prefix) << endl;

	if (prefix->size() <= 0) {

		copy(sdb.begin(), sdb.end(), back_inserter(*new_sdb));

		return;
	}

//	cout << "prefix: " << print_vec(*prefix) << endl;

	int current_prefix_item = prefix->back();

//	cout << "prefix[-1] a.k.a last element = " << current_prefix_item << endl;

	for (vector<vector<int> >::iterator entry = sdb.begin(); entry != sdb.end(); entry++) {

		int j = 0;

		// projection is the new transaction/sequence starting from the position of
		// the prefix element and to the end of the original sequence
		// in python it would look like a slice of the vector v[x:]
//		vector<int> *projection = new vector<int>;
		vector<int> projection;

//		cout << "Examining entry " << print_vec(*entry) << endl;

		for (vector<int>::iterator item = entry->begin(); item != entry->end(); item++) {

//			cout << "examining item " << *item << " int entry " << print_vec(*entry) << " against prefix item = "
//			     << current_prefix_item << endl;

			if (*item == current_prefix_item) {

//				copy(entry->begin() + j + 1, entry->end(), back_inserter(*projection));
				copy(entry->begin() + j + 1, entry->end(), back_inserter(projection));

//				cout << "projection matches current_prefix_item, projection = entry[j + 1], where j = " << j << " is: "
//				     << print_vec(*projection) << endl;

				break;
			}

			j++;
		}

//		if (projection->size() > 0) {
		if (projection.size() > 0) {

//			new_sdb->push_back(*projection);
			new_sdb->push_back(projection);
		}

//		cout << "new sdb returned from project(): " << print_vec(*new_sdb) << endl;
	}
}

/**
 * Checks if the pair exists in the vector, was needed before adopting a set for the freq_seqs
 *
 * @dead_for_now
 */
bool check_exists(vector<pair<vector<int>, int> >& freq_seqs, pair<vector<int>, int>& prefix_pair) {

	if (find(freq_seqs.begin(), freq_seqs.end(), prefix_pair) != freq_seqs.end()) {

		return (true);
	} else {

		return (false);
	}
}

/**
 * Generates and populates the frequent item set recursively.
 *
 * @param &sdb : the sequence database reference
 * @param *prefix : the pointer to the prefix vector
 * @param prefix_support : the frequency/support for the prefix element
 * @param min_support : the minimum support
 * @not_used_for_now -- @param *freq_seqs : the set of all the frequent item-sets
 */
void freq_seq(vector<vector<int> >& sdb, vector<int> *prefix, int prefix_support, int min_support) { // ,
	// set<pair<vector<int>, int> > *freq_seqs) {

	if (prefix->size() > 0) {

		cout << "Prefix exists, adding: (" << (print_vec(*prefix)) << ", " << to_string(prefix_support)
		     << ") to freq_seqs" << endl;

		pair<vector<int>, int> prefix_pair = make_pair(*prefix, prefix_support);

//		if (!check_exists(*freq_seqs, prefix_pair)) {

//		freq_seqs->insert(prefix_pair);

		// output to file inorder to reduce space
		fprintf(fpResult, "[%s] %d\n", print_vec(prefix_pair.first).c_str(), prefix_pair.second);

		fflush(fpResult);

//		}

//		cout << "now Prefix = " << print_vec(*prefix) << endl;
	}

//	cout << "inside freq_seq(): prefix size= " << prefix->size() << endl;

	vector<pair<int, int> > locally_frequents;

	local_freq_items(sdb, prefix, min_support, &locally_frequents);

//	cout << "local_freq_items returned locally_frequents: " << print_vec(locally_frequents) << endl;

	if (locally_frequents.size() <= 0) {

		return;
	}

	for (vector<pair<int, int> >::iterator locally_frequent = locally_frequents.begin();
	        locally_frequent != locally_frequents.end(); locally_frequent++) {

		vector<int> new_prefix;

		copy(prefix->begin(), prefix->end(), back_inserter(new_prefix));

//		new_prefix->push_back(locally_frequent->first);
		if (find(new_prefix.begin(), new_prefix.end(), locally_frequent->first) == new_prefix.end()) {

			new_prefix.push_back(locally_frequent->first);
		}

//		cout << "new_prefix: new_prefix=" << print_vec(new_prefix) << ", built from old prefix =  "
//		     << print_vec(*prefix) << " and item=" << locally_frequent->first << "  and sending to project" << endl;

		vector<vector<int> > new_sdb;

		// calling project
		project(sdb, &new_prefix, &new_sdb);

//		cout << "back from project() with new_sdb: " << print_vec(new_sdb) << ", and now calling freq_seq( new_sdb="
//		     << print_vec(new_sdb) << ", new_prefix=" << print_vec(new_prefix) << ", support="
//		     << locally_frequent->second << ", min_support=" << min_support << ", freq_seqs = " << print_vec(*freq_seqs)
//		     << ") " << endl;

// recursive call
		freq_seq(new_sdb, &new_prefix, locally_frequent->second, min_support); // , freq_seqs);
	}
}

/**
 * Final output generator
 * Enumerate all frequenct sequences.
 *
 * @param sequences: a sequence of sequences
 * @param min_support: The minimal support of a set to be included
 *
 * @not_used_for_now -- @param *freq_seqs : {(frequent_sequence, support)}
 */
void freq_seq_enum(vector<vector<int> >& sequences, int min_support) { //, set<pair<vector<int>, int> > *freq_seqs) {

	vector<int> prefix;

	// cout << "freq_seq_enum" << endl;

	freq_seq(sequences, &prefix, 0, min_support); //, freq_seqs);
}

/**
 *
 * Reads the input dat file and creates the sequence database for the apriori algorithm
 *
 * @param filename - name of the input file
 * @param rowcount - number of rows/ documents in the input dat file
 * @param colcount - number of columns/ words in the documents according to the dat file
 * @param *sequences - the sequence db
 */
void read_file(string& filename, int rowcount, int colcount, vector<vector<int> > *sequences) {

	FILE* fp;

	cout << "HARMLESS::" << sequences->max_size() << endl;

	fp = fopen(filename.c_str(), "rt");

	for (int row = 0; row < rowcount; row++) {

		(*sequences)[row].reserve(colcount);
	}

	int index, length;

	for (int row = 0; row < rowcount; row++) {

		fscanf(fp, "%d", &length);

		for (int i = 0; i < length; i++) {

			fscanf(fp, "%d", &index);

			(*sequences)[row].push_back(index);
		}
	}

	for (vector<vector<int> >::iterator it = sequences->begin(); it != sequences->end(); it++) {

		it->shrink_to_fit();
	}
}

/**
 * Prints the apriori to the results file
 *
 * @param *fpResult : pointer to the results file
 * @param &freq_seqs : frequent sequences reference
 *
 * @dead_for_now
 */
void print_apriori(FILE* fpResult, set<pair<vector<int>, int> >& freq_seqs) {

	for (auto entry : freq_seqs) {

		fprintf(fpResult, "[%s] %d\n", print_vec(entry.first).c_str(), entry.second);
	}
}

int main(int argc, char* argv[]) {

	if (argc < 5) {

		cout << "Usage: apriori rowcount colcount file_name support" << endl;
		return (0);
	}

	int rowcount = atoi(argv[1]);
	int colcount = atoi(argv[2]);
	string file_name = argv[3];

	// compute the min support
	int min_support = (int) (rowcount * atof(argv[4]));

	vector<vector<int> > sequences(rowcount);

//	set<pair<vector<int>, int> > freq_seqs;

	cout << "reading file= " << file_name << "rowcount= " << rowcount << "colcount= " << colcount << "min_support= "
	     << min_support << endl;

	fpResult = fopen("results.txt", "wt");

	// read dat file
	read_file(file_name, rowcount, colcount, &sequences);

	clockStart = clock();

	// apriori call
	freq_seq_enum(sequences, min_support); //, &freq_seqs);

	runtimeAlgorithm = (double) (difftime(clock(), clockStart) / CLOCKS_PER_SEC);

	cout << "Completed in: " << runtimeAlgorithm << "secs, Results printed to results.txt" << endl;

//	cout << "Open Output File" << " " << fpResult << endl;
//	print_apriori(fpResult, freq_seqs);
}

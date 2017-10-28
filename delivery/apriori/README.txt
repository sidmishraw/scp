**************************************
* CS - 267 Project - Spring 2017
* Author(s) - Michael Symonds, Sidharth Mishra, Samuel Ordonia, Wayne Huang
**************************************

Apriori Port is a C++ translation of the apriori algorithm implemented in the python version pymining/seqmining 
(python source code can be found on Github: https://github.com/bartdag/pymining/blob/master/pymining/seqmining.py)

This is a recursive implementation of the apriori algorithm which retains the order of the frequent item sets being counted.

The port is contained in 1 .cpp file called source.cpp. To run the port, open the solution/project file apriori.sln, located in the root of the apriori folder, in Visual Studio. The project must be run in x64.

Paramters are required to run the program. These parameters come in the following form:
<int:rows> <int:columns> <input_File_Path> <float: minSup>

For example, in the root of the apriori folder, there is a text file named "65k.txt" which may be used to test the operation. That input file has a row (document) count of 65536 and a column (word) count of 1256. Considering an example threshold of 0.69, the following parameters to run the application on the data set you be:
65536 1256 C:\Users\path\to\root\file\of\apriori\65k.dat 0.69

When using a .dat file that has been produced by the PDF Processor, you may calculate the needed row and column parameters as follows:

Calculating the row parameter value:
The row parameter reflects the number of documents, or traansactions, being examined. To calculate this value, you must have already run pdfs through the PDF Processor. Once doing so, the processor, in addition to supplying the .dat file, will also supply a document called "doc_map.json" located in the root of the PDF Processor folder. Open that file in any text editor, go to the end/bottom of the file and take note of the key value of the last item. An example of an item is: "499":"9_01409087.json". The first numeric value is the key.
The last key value in "doc_map.json" + 1 is the correct input value for the row parameter. 

Clculating the column parameter:
The column parameter represents the cardinality of the universal set of unique words collected from all the PDF documents being examined. As described above, running the PDF Processor on a collection of PDFs will also produce a file called "word_map.json". Open this file in any text editor, go to the end/bottom of the file, and take note of the key value of the last item. An example of an item is: "43648":"ridiculous". The numeric value represents the key.
The last key value in "word_map.json" + 1 is the correct input value for the column parameter.

Once apriori is run, it will produce a file called results.txt, which can be found in (root folder)/apriori. This file contains all of the frequent item sets in their numeric representation and the corresponding frequency for each set. If you want to translate the numeric values back into their original word representations, please consult the README.txt file in the root of the PDF Processor project file for instructions on doing so.
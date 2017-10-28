
from collections import defaultdict


def freq_seq_enum(sequences, min_support):
    '''Enumerates all frequent sequences.
       :param sequences: A sequence of sequences.
       :param min_support: The minimal support of a set to be included.
       :rtype: A set of (frequent_sequence, support).
    '''
    freq_seqs = set()
    _freq_seq(sequences, tuple(), 0, min_support, freq_seqs)
    return freq_seqs


def _freq_seq(sdb, prefix, prefix_support, min_support, freq_seqs):
    if prefix:
        #print "prefix exisits, adding: ", (prefix, prefix_support), " to freq_seqs\n"
        freq_seqs.add((prefix, prefix_support))
    locally_frequents = _local_freq_items(sdb, prefix, min_support)
    #print "_local_freq_items returned locally_frequents: ", locally_frequents, "\n"
    if not locally_frequents:
        return
    for (item, support) in locally_frequents:
        new_prefix = prefix + (item,)
        #print "new_prefix: ", new_prefix, " built from: ", prefix, " and ", (item,), " and sending to _project"
        new_sdb = _project(sdb, new_prefix)
        #print "back from project with new_sdb: ", new_sdb, " and now calling _freq_seq(", new_sdb, ", ", new_prefix, ", ", support, ", ", min_support, ", ", freq_seqs, "\n"
        _freq_seq(new_sdb, new_prefix, support, min_support, freq_seqs)


def _local_freq_items(sdb, prefix, min_support):
    #print "in _local_freq_items, sdb is: ", sdb, " prefix is: ", prefix, " min_support is: ", min_support
    items = defaultdict(int)
    freq_items = []
    for entry in sdb:
        visited = set()
        for element in entry:
            if element not in visited:
                items[element] += 1
                visited.add(element)
    # Sorted is optional. Just useful for debugging for now.
    for item in items:
        support = items[item]
        if support >= min_support:
            freq_items.append((item, support))
    #print "Frequent items returnung: ", freq_items
    return freq_items


def _project(sdb, prefix):
    #print "in _project, sdb is: ", sdb, " and prefix is: ", prefix
    new_sdb = []
    if not prefix:
        return sdb
    #print "prefix", prefix
    current_prefix_item = prefix[-1]
    #print "prefix[-1]", current_prefix_item
    for entry in sdb:
        j = 0
        projection = None
        #print "examining entry", entry, "\n"
        for item in entry:
            #print "examining item ", item, " in entry ", entry, " against prefix_item ", current_prefix_item, "\n"
            if item == current_prefix_item:
                projection = entry[j + 1:]
                #print "projection matches current_prefix_item, projection = entry[j + 1], where j = ", j, " is: ", projection, "\n"
                break
            j += 1
        if projection:
            new_sdb.append(projection)
    #print "new_sdb returned from _project: ", new_sdb
    return new_sdb

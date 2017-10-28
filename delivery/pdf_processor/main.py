# main.py
# -*- coding: utf-8 -*-
# @Author: Samuel Ordonia
# @Date:   2017-04-04 18:32:49
# @Last Modified by:   Sidharth Mishra
# @Last Modified time: 2017-05-14 18:43:35


"""
The main driver for CS 267 Project.
"""


# Python Standard library imports
from re import sub
from json import dumps
from json import loads
from os.path import sep
from os.path import exists
from logging import basicConfig
from logging import error
from pprint import pprint

basicConfig(format='%(asctime)s %(message)s', datefmt='%m/%d/%Y %I:%M:%S %p')


# Numpy
import numpy as np
import pandas as pd


# nltk
from nltk import download


# CS 267 Project imports
from preprocessor import *
from simplicial_complex import SimplicialComplex


# globals
corpus = None
tokens = None
token_list = None
docs = None
df_output = None
props = None


# constants
__INPUT_FILEPATH__ = 'input_jsons_filepath'
__SHARED_OBJ_FILEPATH__ = 'shared_obj_filepath'
__OUTPUT_FILEPATH__ = 'output_filepath'


# # nltk stop words resource setup
def nltk_stopwords_setup():
  '''
Sets up the `corpora/stopwords` resource which is used for stemming by
NLTK.

  :return: `None`
  '''

  if exists('mystopwords/corpora/stopwords') == False:
    download(download_dir='mystopwords')

  return


# read in data and init
def read_data_init():
  '''
  Reads in data and initializes the pipeline.

  :return: `None`
  '''

  global corpus, token_list, docs, props

  with open('properties.json', 'r') as props_read:
    props = loads(props_read.read())

  (corpus, tokens) = read_input_files(props[__INPUT_FILEPATH__])

#  num_word_map = {}
#  docs_map = tokens['docs']
#
#  for i, value in enumerate(corpus.keys()):
#    num_word_map[i] = value
#
#  with open('word_mapping.json', 'w') as fopen:
#    fopen.write(dumps(num_word_map))
#
#  bitmap = [[0 for doc in tokens['docs']] for word in corpus.keys()]
#
#  for row, word in enumerate(corpus.keys()):
#    for doc, pos in corpus[word]:
#      col = docs_map.index(doc)
#      bitmap[row][col] = 1
#
#  pprint(bitmap)
#
#  with open('auxillary_bitmap.txt', 'w') as fopen:
#    for row in bitmap:
#      fopen.write(' '.join(list(map(str, row))))
#      fopen.write('\n')
#
#  with open('outputs/output_doc_freq.txt', 'w') as fopen:
#    for row in bitmap:
#      fopen.write(' '.join(list(map(str, row))))
#      fopen.write('\n')
#
#  max_rows = len(bitmap)
#  max_cols = len(docs_map)
#
#  return bitmap, max_cols, max_rows, num_word_map, docs_map
  # token_list = list(tokens.keys())

  # docs = sorted(corpus.keys())


# # Part1 section: tf - compute term frequencies
# def get_term_frequency():
#   '''
#   Compute the term frequencies.

#   :return: `None`
#   '''

#   global docs, props

#   term_frequency_with_positions = dict()

#   for doc in docs:
#     term_frequency_with_positions[
#         doc] = determine_word_positions(corpus[doc])

#   # Print to json file & prettify
#   with open('{filepath}{sep}output_term_freq.json'.format(
# filepath=props[__OUTPUT_FILEPATH__], sep=sep), 'w') as tf_file_output:

#     tf_file_output.write(
#         dumps(term_frequency_with_positions, sort_keys=True, indent=2))


# # compute document frequency
# def compute_df():
#   '''
#   Computes the df.
#   '''

#   global docs, token_list, corpus, props, df_output

#   # Part 2 section:  df
#   df_output = determine_doc_frequency(docs, token_list, corpus)

#   # Print to csv file
#   df_output.to_csv('{filepath}{sep}output_doc_freq.csv'.format(
# filepath=props[__OUTPUT_FILEPATH__], sep=sep), header=token_list,
# sep=',')

#   # Print to txt file
#   np.savetxt('{filepath}{sep}output_doc_freq.txt'.format(
# filepath=props[__OUTPUT_FILEPATH__], sep=sep), df_output.values,
# fmt='%d')


# simplical complex
#def process_simplical_cmplx(max_cols, max_rows):
#  '''
#  Use Simplical Complex algorithm to find frequent itemset.
#
#  :return: `None`
#  '''
#
#  global df_output, props
#
#  with open('properties.json', 'r') as props_read:
#    props = loads(props_read.read())
#
#  string_vector_all = ''

  # for index, series in df_output.iterrows():
  #   whitespace_regex = r'\s+'
  #   string_vector = np.array_str(series.values)
  #   string_vector = sub(whitespace_regex, '', string_vector)
  #   string_vector_all += string_vector_all + \
  #       string_vector[1:len(token_list)]
  #   bit_vector_as_string = string_vector[
  #       1:(len(token_list))].encode('utf-8')
  # bit_vector_as_string = string_vector_all.encode('utf-8')
#  bitmap_s = None
#
#  with open('outputs/output_doc_freq.txt', 'r') as fin:
#    bitmap_s = fin.read()
#
#  bitmap_s = bitmap_s.replace(" ", "")
#  bitmap_s = bitmap_s.replace("\n", "")
#
#  pprint(bitmap_s)
#
#  sc2 = SimplicialComplex(shared_obj_path=props[__SHARED_OBJ_FILEPATH__])
  # sc2.directProcess(
  #     4, 0.05, max_cols, max_rows, bytes(
  #         bitmap_s, encoding='utf-8'))
#  sc2.directProcess(
#      4, 0.97, max_rows, max_cols, bytes(
#          bitmap_s, encoding='utf-8'))


# simplex dictionary, the final word mapping
simplex_dict = {}


def split_replace_simplex(x, simplex_l, num_word_map):
  simplex_l.append(num_word_map[int(x)])


def process_results_txt(num_word_map, docs_map):
  '''
  Processes the results.txt to obtain final_results.txt replacing all the numbers with the words
  from the number - word mapping while constructing the bitmap
  '''

  from re import compile
  from re import findall

  pattern = compile(r'\[(.*)\]\s(\d*)')

  with open('results.txt', 'r') as fin:
    for s_in in fin:
      if len(findall(pattern, s_in)) > 0:
        simplex, freq = findall(pattern, s_in)[0]
        simplex_l = []
        list(
            map(
                lambda x: split_replace_simplex(
                    x,
                    simplex_l,
                    num_word_map),
                simplex.split(' ')))
        new_simplex = '[{}]'.format(' '.join(simplex_l))
        simplex_dict[new_simplex] = int(freq)


if __name__ == '__main__':

  with open('properties.json', 'r') as props_read:
    props = loads(props_read.read())

  read_input_files(props[__INPUT_FILEPATH__])

  # nltk_stopwords_setup()
  # bitmap, max_cols, max_rows, num_word_map, docs_map = read_data_init()
  # get_term_frequency()
  # compute_df()
  # error('Started Simplical Complex')
  # process_simplical_cmplx(max_cols, max_rows)
  # process_simplical_cmplx(4, 3)
  # error('Ended Simplical Complex')
  # process_results_txt(num_word_map, docs_map)

  # with open('almost_final_op.txt', 'w') as fopen:
  #   fopen.write(dumps(simplex_dict))

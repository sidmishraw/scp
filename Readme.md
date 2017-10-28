# PDF Processing and text mining pipeline using Simplicial Complex and Apriori

Authors: Michael Symonds, Samuel Ordonia, Sidharth Mishra, Wei Chung Huang(Wayne Huang)

Advisor: Dr. T.Y Lin

### Motive:

* Process and extract PDF(from IEEE Xplore) contents into JSON structures for easy consumption by text-mining applications.

* Analyze the processed PDF documents by passing it through the Simplicial Complex C++ program(old version).

* Write a Simplicial complex version(python wrapper) to work with PDF processor's output(directly); basically construct a data pipline that takes PDF documents, extracts contents out of it into JSON documents, and then consumes the JSON documents to analyze them using our Simplicial complex python wrapper.

* Write the C++ port of Apriori algorithm program included in the Python library "pymining/seqmining" by Barthelemy Dagenais(also called [bartdag](https://github.com/bartdag/pymining))

Note: The port was a one-to-one copy of the Python version.

More information about the project layout, contributions and working principles are located in the [Team1_CS267_Readme.docx](./delivery/Team1_CS267_Readme.docx)
Please refer to the document incase of any concerns.


You are welcome to create issues for this repository to report any issues you run into whilst using this project.

### Requirements:
* Python3 (atleast 3.5.2)
* Java 8
* C++ 11 (Visual Studio 2012 or better on Windows)

> Note: Python dependecies are included in the `requirements.txt`. We make use of `pdfminer` by Yusuke Shinyama for parsing PDFs, after that it is custom logic.

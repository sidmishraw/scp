**************************************
* CS - 267 Project - Spring 2017
* Author(s) - Michael Symonds, Sidharth Mishra, Samuel Ordonia, Wayne Huang
**************************************

PDF Processor is a data mining pipeline which accepts PDF documents from IEEE Xplore, parses the content from them,
treats the text by removing stop words, trimming, and stemming, then converts each document to a word set representation 
(one version in reading order, and a second in ascending order) represented as lines in a .dat file. The .dat file may be
run as input for either simplicial complex or the c++ apriori port. Once the results from those applications are generated,
the pipeline can then convert the numeric word representation back into the original words using a seperate step.

In order to run PDF Processor, the minimum supported version is Python v3.5.2.
In order to run Simplicial Complex or apriori port, you need to have Visual Studio (2013) installed. 


Installing PDF Processor:

Running PDF Processor will check for and install any dependencies needed to run the python code. Follow the instructions
to run below.

Recommended - Run in a python virtual environment:
To create and run a virtual environment, first install the dependency needed to set up your virtual environment
Open your command console as administrator and execute:
in Windows> pip install virtualenv
in Mac/Linux> sudo pip install virtualenv

Then set up the virtual environemnt itself:
1. Change to the root of your project (PDF Processor) directory
2. execute the following command:
in Windows/Mac/Linux> virtualenv finalproj_venv

Then when you are ready to run the PDF conversion, start your virtual environment by executing:
in Windows> finalproj_venv\Scripts\activate.bat
in Mac/Linux> source finalproj_venv/bin/activate

You will know you are operating in the virtual environment when your command prompt looks like this:
(finalproj_venv) C:\Users\your\present\working\directory>


Running the conversion process:

*Before starting the conversion process, be sure to copy your PDFs into the "input_pdfs" directory inside the project folder

Converting the PDFs into the dat file needed to run in simplicial complex or apriori is a 2-step process. 

1. Open your command console and execute:
in Windows>:
>start_json_generation.bat

in Mac/Linux>:
>chmod +x start_json_generation.sh
>./start_json_generation.sh

Note: during the process, the console will output status messages starting with "ERROR: pdf_processor", this is only a log message and not an actual error.

When complete, the console will report if bad PDFs were found in your input folder. If so, the bad PDFs (PDf which are images or scanned documents) are moved out of the input_pdfs folder automatically and into a "badPDFs" folder. You may either rerun the start_json_generation process again or add more PDFs into your input_pdfs folder and run again.

2. The second step involves converting the JSON files created from the first step into the final outputs. To do this, execute the following:
in Windows>:
>dat_file_generation.bat

in Mac/Linux>:
>chmod +x dat_file_generation.sh
>./dat_file_generation.sh

This will convert the generated JSON files into several different outputs:
The file needed to run in the simplicial complex or apriori c++ code is found in the folder "output_s_dats" and there are 2 versions: 
s_output.dat -  where the reading order for each line (document) is preserved.
sorted_s_output.dat - where the values for each line (document) are sorted in ascending order

In the main project folder, the other 2 output files can be found:
word_map.json - open this json file, move to the end of the file, and note the key value of the last item, this value + 1 is the total number of words/columns needed to be entered as the columns parameter for simplicial complex and apriori c++ port.

doc_map.json - open this json file, move to the end of the file, and note the key value of the last item, this value +1 is the total number of rows/documents needed to be entered as the rows parameter for simplicial complex and apriori c++ port.

Please consult the README files for those applications for instructions on how to run them.


3. Once you've run either simplicial complex or apriori, the results.txt file generated will list the frequent item sets by their numeric value representations. To convert these values back to their original words, move the results.txt file into the root of the PDF Processor project folder and execute in your command console:
in windows>:
>process_results.bat

in Mac/Linux>:
>chmod +x process_results.sh
>./process_results.sh

This will convert the numeric values of the frequent item sets into their corresponding words and output to the file:
final_apriori_results.txt or
final_simplicialcmplx_results.txt
depending on which application you ran the .dat file through.



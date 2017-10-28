@REM @Author: sidmishraw
@REM @Date:   2017-05-17 19:05:15
@REM @Last Modified by:   sidmishraw
@REM Modified time: 2017-05-18 14:43:17

@echo off

echo.
echo ............................................
echo CS - 267 Project - Spring 2017
echo Author(s) - Michael, Sid, Sam, Wayne
echo ............................................
echo. 
echo Starting the `.dat` file generation process
echo. 

python main.py

echo. 
echo. 
echo Generated cleansed JSON files in `output_s_jsons` directory.
echo These files will be used for generating `.dat` files inside the
echo `output_s_dats` directory.
echo. 
echo. 

java -jar SimplicalComplexDataCreator.jar

echo. 
echo. 
echo Generated `s_output.dat` file and `sorted_s_output.dat`.
echo The `s_output.dat` contains the reading order of the word indices.
echo. 
echo The `sorted_s_output.dat` contains the word indices in ascending(sorted) order.
echo.
echo The `word_map.json` and `doc_map.json` are mapping files that give you
echo information on the number of rows(docs) and number of columns(words) to be
echo used for the Simplicial Complex and Apriori C++ port programs.
echo.
echo. 
echo The `.dat` files can now be used by either of SimplicialComplex C++ program
echo or the Apriori C++ port. 
echo.
echo.
echo Generating recommended configuration for Apriori C++ port and Simplicial Complex
echo.

python conf_generator.py

echo.

pause

@REM @Author: sidmishraw
@REM @Date:   2017-05-17 18:01:47
@REM @Last Modified by:   sidmishraw
@REM Modified time: 2017-05-17 19:52:41

@echo off

echo.
echo ............................................
echo CS - 267 Project - Spring 2017
echo Author(s) - Michael, Sid, Sam, Wayne
echo ............................................
echo.
echo Starting generation of JSONs from the `input_pdfs`
echo JSON files will be generated in `pdf_jsons` directory
echo Grouped JSON files will be generated in `pdf_grouped_jsons` directory
echo.
echo Running PDF processor on the PDF documents in `input_pdfs`

if exist pdfprocessor.log (
  echo Deleting old pdfprocessor.log
  del /f pdfprocessor.log
  echo Deleted old pdfprocessor.log
)

pip install -r requirements.txt

python pdf_downloader_script.py

echo.
echo.
echo Completed generation of JSON files. The files have been written to
echo `pdf_jsons` directory and `pdf_grouped_jsons` directory
echo.
echo .................................
echo Checking for bad PDFs
echo .................................

java -jar DocPruner.jar pdfprocessor.log pdf_jsons pdf_grouped_jsons

echo.
echo If the Output was: "Successfully moved the generated files"
echo.
echo The bad PDFs have been pruned and moved into `badPDFs` directory and the generated
echo directories `pdf_jsons` and `pdf_grouped_jsons` have been moved into 
echo `badGeneratedFiles` directory , please verify your PDF counts, replace the bad PDFs and
echo re-run this batch script.
echo.
echo.
echo Else if it said "Nothing to move :)"
echo you can now run the `dat_file_generation.bat` to generate the dat files
echo.
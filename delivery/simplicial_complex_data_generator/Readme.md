## Simplical Complex Data generator

This application reads the PDF JSON files(cleansed) and generates the simplicial complex `.dat` input file.

> Usage:
```
java -jar simplicalcomplexdatgen.jar <path to folder containing cleansed .json files> <absolute file path for word_map.json> <absolute file path for doc_map.json> <absolute file path for .dat file>
```  

Default values for the params:

```	
	<path to folder containing cleansed .json files> = ./output_s_jsons
	<absolute file path for word_map.json> = ./word_map.json
	<absolute file path for doc_map.json> = ./doc_map.json
	<absolute file path for .dat file> = ./output_s_dats
```

Incase of any concerns please contact - Sidharth Mishra <sidharth.mishra@sjsu.edu>
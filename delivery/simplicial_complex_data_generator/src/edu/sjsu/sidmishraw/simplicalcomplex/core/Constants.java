/**
 * Project: SimplicalComplexDataCreator
 * Package: edu.sjsu.sidmishraw.simplicalcomplex.core
 * File: Constants.java
 * 
 * @author sidmishraw
 *         Last modified: Apr 24, 2017 4:16:38 PM
 */
package edu.sjsu.sidmishraw.simplicalcomplex.core;

/**
 * @author sidmishraw
 *
 *         Qualified Name: edu.sjsu.sidmishraw.simplicalcomplex.core.Constants
 *
 */
public class Constants {
	
	/**
	 * path to the directory containing all the standardized jsons
	 * They have json of format
	 */
	public static final String	DEFAULT_FILE_NAME									= "output_s_jsons";
	
	/**
	 * Writes the files that are to be used by simplical complex to there
	 * also writes a props file that has the total number of rows and total
	 * number of columns and a recommended threshold value
	 * for the files.
	 */
	public static final String	DEFAULT_SIMPLICAL_COMPLEX_IP_PATH	= "output_s_dats";
	
	/**
	 * word map and doc map offline storage locations
	 */
	public static final String	DEFAULT_WORD_MAP_PATH							= "word_map.json";
	public static final String	DEFAULT_DOC_MAP_PATH							= "doc_map.json";
}

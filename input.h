#ifndef input_h__
#define input_h__

/**
 * Reads the Sudoku from file
 * @param path The File to read from
 * @param sf The struct where to write the Data
 * @param o The options with the functions to use
 */
int s_einlesen(char * path, sudoku * sf, options * o);

#endif /* input_h__ */
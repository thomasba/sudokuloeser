#ifndef output_std_h__
#define output_std_h__

/**
 * Print the Sudoku on stdout using unicode borders
 * @param s The Sudoku
 * @param color Use colors or not
 */
void std_ausgabe_unicode(sudoku* s,int color);

/**
 * Print the Sudoku on stdout using ascii
 * @param s The Sudoku
 * @param color Use colors or not
 */
void std_ausgabe(sudoku* s,int color);

#endif /* output_std_h__ */
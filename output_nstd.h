#ifndef output_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define output_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

/**
 * Print the Sudoku on stdout using unicode borders
 * @param s The Sudoku
 * @param color Use colors or not
 */
void nstd_ausgabe_unicode(sudoku* s,int color);

/**
 * Print the Sudoku on stdout using ascii
 * @param s The Sudoku
 * @param color Use colors or not
 */
void nstd_ausgabe(sudoku* s,int color);

/**
 * Choose border-elements
 * @param v which elemnt to return
 */
char* rahmen(char v);

/**
 * Choose color by value
 * @param val which color
 */
char* colors(char val);

#endif /* output_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

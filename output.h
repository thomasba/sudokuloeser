#ifndef output_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define output_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

/**
 * Write the sudoku to a file
 * @param fn The Filename
 * @param s The Sudoku to write
 */
int s_write(char* fn,sudoku* s);

/**
 * Write error-message in output-file
 * @param fn The Filename
 * @param err The Error-Code
 */
int s_write_error(char* fn,int err);

/**
 * Prints the plain sudoku
 * @param s The Sudoku
 * @param color Takes no effect
 */
void s_plain(sudoku* s, int color);

#endif /* output_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

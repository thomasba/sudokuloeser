#ifndef output_h__
#define output_h__

#include "main.h"

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

#endif /* output_h__ */
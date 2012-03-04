#ifndef solver_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define solver_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

#include "types.h"

/**
 * Tries to solve the Sudoku with logic
 * @param s the sudokue to solve
 */
int  sl_loes(sudoku* s, options * o);

/**
 * Tries to solve a sudoku with backtracking (bruteforce)
 * @param s the sudokue to solve
 * @param pos the actual position, usualy start with 0
 */
int s_loes_track(sudoku * s, int pos, options * o);

#endif /* solver_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

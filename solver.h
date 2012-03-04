#ifndef solver_h__
#define solver_h__

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

#endif /* solver_h__ */
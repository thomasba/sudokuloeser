#ifndef solver_std_h__
#define solver_std_h__

/**
 * Checks if there are other posibilities for the number if not return 1
 * @param s The sudoku struct
 * @param zahl The number to check
 * @param z row
 * @param sp column
 */
int solver_check_nums(sudoku* s,int zahl,int z, int sp);

/**
 * Stroke out the number (Logic Solver)
 * @param s The sudoku struct
 * @param zahl The number to check
 * @param z row
 * @param sp column
 */
void solver_set_num(sudoku* s,int zahl,int z, int sp);

/**
 * Checks if the number fits
 * @param s The sudoku struct
 * @param z row
 * @param sp column
 * @param zahl The number to check
 */
int  solver_test(sudoku *s, int z, int sp, int zahl);

#endif /* solver_std_h__ */
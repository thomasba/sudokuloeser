#ifndef solver_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define solver_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

#include "types.h"

/**
 * Checks if there are other posibilities for the number if not return 1
 * @param s The sudoku struct
 * @param zahl The number to check
 * @param z row
 * @param sp column
 */
int solver_nstd_check_nums(sudoku* s,int zahl,int z, int sp);

/**
 * Stroke out the number (Logic Solver)
 * @param s The sudoku struct
 * @param zahl The number to check
 * @param z row
 * @param sp column
 */
void solver_nstd_set_num(sudoku* s,int zahl,int z, int sp);

/**
 * Checks if the number fits
 * @param s The sudoku struct
 * @param z row
 * @param sp column
 * @param zahl The number to check
 */
int  solver_nstd_test(sudoku *s, int z, int sp, int zahl);

#endif /* solver_nstd_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

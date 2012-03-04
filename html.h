#ifndef html_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define html_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

#include "types.h"

#include <stdio.h>

void genHTML(sudoku * s,FILE * fp);
void printHead(FILE * fp);
void printFoot(FILE * fp);
void out_html(sudoku * s,int c);
int write_html(char* fn,sudoku * s);

#endif /* html_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

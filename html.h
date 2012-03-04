#ifndef html_h__
#define html_h__

#include <stdio.h>

void genHTML(sudoku * s,FILE * fp);
void printHead(FILE * fp);
void printFoot(FILE * fp);
void out_html(sudoku * s,int c);
int write_html(char* fn,sudoku * s);

#endif /* html_h__ */
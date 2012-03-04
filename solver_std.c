#include "solver_std.h"

int solver_check_nums(sudoku* s,int zahl,int z, int sp) {
	int x=z-(z%3) , y=sp-(sp%3) , i, j, sum=0;
	zahl--;
	if(s->mgl[z][sp][zahl] == 1) return 0;
	/* Spalte pruefen */
	for(i=0;i<9;i++)
		if(s->mgl[z][i][zahl] != 1 && i!=sp) { sum=1; break; }
	if(sum==0) return 1;
	/* Zeile pruefen  */
	sum = 0;
	for(i=0;i<9;i++)
		if(s->mgl[i][sp][zahl] != 1 && i!=z) { sum=1; break; }
	if(sum==0) return 1;
	/* Block pruefen   */
	sum=0;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(s->mgl[x+i][y+j][zahl] != 1 && !((x+i) == z && (y+j) == sp)) { sum=1; break; }
	if(sum==0) return 1;
	return 0;
}

void solver_set_num(sudoku* s,int zahl,int z, int sp) {
	int x=z-(z%3) , y=sp-(sp%3) , i, j;
	zahl--;
	
	for(i=0;i<9;i++) {
		s->mgl[z][sp][i] = 1;    /* Zelle sperren */
		s->mgl[z][i][zahl] = 1;  /* Spalte austragen */
		s->mgl[i][sp][zahl] = 1; /* Zeile austragen  */
	}
	/* Block austragen   */
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			s->mgl[x+i][y+j][zahl] = 1;
}

int  solver_test(sudoku *s, int z, int sp, int zahl) {
	/* prueft, ob eine zahlen stimmt _kann_ */
	int x=z-(z%3) , y=sp-(sp%3) , i, j;
	for(i=0;i<9;i++) {
		if(s->feld[z][i] == zahl || s->feld[i][sp] == zahl) return 0;
	}
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(s->feld[x+i][y+j] == zahl) return 0;
	return 1;
}

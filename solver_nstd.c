#include "types.h"
#include "solver_nstd.h"

int solver_nstd_check_nums(sudoku* s,int zahl,int z, int sp) {
	int l = s->belegung[z][sp] , i, j, sum=0;
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
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if( s->belegung[i][j] == l && s->mgl[i][j][zahl] != 1 && !(i == z && j == sp)) {
				sum=1; break;
			}
	if(sum==0) return 1;
	return 0;
}

void solver_nstd_set_num(sudoku* s,int zahl,int z, int sp) {
	int l = s->belegung[z][sp] , i, j;
	zahl--;
	for(i=0;i<9;i++) {
		s->mgl[z][sp][i] = 1;    /* Zelle sperren */
		s->mgl[z][i][zahl] = 1;  /* Spalte austragen */
		s->mgl[i][sp][zahl] = 1; /* Zeile austragen  */
	}
	/* Block austragen */
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(s->belegung[i][j] == l)
				s->mgl[i][j][zahl] = 1;
}

int  solver_nstd_test(sudoku *s, int z, int sp, int zahl) {
	/* prueft, ob eine zahlen stimmt _kann_ */
	int l = s->belegung[z][sp] , i, j;
	/* Spalte und Reihe */
	for(i=0;i<9;i++) {
		if(s->feld[z][i] == zahl || s->feld[i][sp] == zahl) return 0;
	}
	/* Passendes Feld */
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			if( s->belegung[i][j] == l && s->feld[i][j] == zahl ) {
				return 0;
			}
		}
	}
	return 1;
}
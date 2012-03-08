#include "output_nstd.h"
#include <stdio.h>

char* rahmen(char v) {
	/* 1 = oben; 2 = rechts; 4 = unten; 8 = links */
	switch(v) {
		case 0: return "┼───";
		case 1: return "╀───";
		case 2: return "┾━━━";
		case 3: return "╄━━━";
		case 4: return "╁───";
		case 5: return "╂───";
		case 6: return "╆━━━";
		case 7: return "╊━━━";
		case 8: return "┽───";
		case 9: return "╃───";
		case 10: return "┿━━━";
		case 11: return "╇━━━";
		case 12: return "╅───";
		case 13: return "╉───";
		case 14: return "╈━━━";
		case 15: return "╋━━━";
	}
	return "+---";
}

void nstd_ausgabe_unicode(sudoku* s,int color) {
	int i,j;
	/* Rahmen oben */
	printf("┏━━━");
	for(i = 0; i < 8 ; i++) {
		printf("%s━━━",(s->belegung[0][i] == s->belegung[0][i+1]) ? "┯" : "┳" );
	}
	printf("┓\n");
	/* Die Zeilen ausgeben */
	for(i = 0; i < 9; i++) {
		/* Zeile*/
		printf("┃");
		for(j = 0; j<9; j++) {
			if(color) {
				printf(" %s%c\033[0m %s",
						(s->vorgabe[i][j] == 1) ? "\033[32;1m" : ( (s->vorgabe[i][j] == 2) ? "\033[33;1m" : "") ,
						(s->feld[i][j] == 0) ? ' ' : s->feld[i][j]+48,
						(j == 8 || s->belegung[i][j] != s->belegung[i][j+1]) ? "┃" : "│" );
			}else{
				printf(" %c %s",
						(s->feld[i][j] == 0) ? ' ' : s->feld[i][j]+48,
						(j == 8 || s->belegung[i][j] != s->belegung[i][j+1]) ? "┃" : "│" );
			}
		}
		printf("\n");
		/* trenner für i != 8 */
		if(i<8) {
			printf("%s", (s->belegung[ i ][ 0 ] == s->belegung[i+1][ 0 ]) ? "┠───" : "┣━━━" );
			for(j = 0; j < 8; j++) {
				printf("%s", rahmen(
							  (s->belegung[ i ][ j ] != s->belegung[ i ][j+1]) * 1
							+ (s->belegung[ i ][j+1] != s->belegung[i+1][j+1]) * 2
							+ (s->belegung[i+1][ j ] != s->belegung[i+1][j+1]) * 4
							+ (s->belegung[ i ][ j ] != s->belegung[i+1][ j ]) * 8
						)
					);
			}
			printf("%s", (s->belegung[ i ][ j ] == s->belegung[i+1][ j ]) ? "┨" : "┫" );
			printf("\n");
		}
	}

	/* Rahmen unten */
	printf("┗━━━");
	for(i = 0; i < 8 ; i++) {
		printf("%s━━━",(s->belegung[8][i] == s->belegung[8][i+1]) ? "┷" : "┻" );
	}
	printf("┛\n");
}

char* colors(char val) {
	switch(val) {
		case 1: return "\033[48;5;16m";
		case 2: return "\033[48;5;105m";
		case 3: return "\033[48;5;19m";
		case 4: return "\033[48;5;28m";
		case 5: return "\033[48;5;52m";
		case 6: return "\033[48;5;55m";
		case 7: return "\033[48;5;100m";
		case 8: return "\033[48;5;172m";
		case 9: return "\033[48;5;129m";
		case 0: return "\033[48;5;129m";
	}
	return "";
}

void nstd_ausgabe(sudoku* s,int color) {
	int i,j;
	for(i=0;i<9;i++) {
		if(i%3==0 && !color) printf("+-------+-------+-------+\n");
		for(j=0;j<9;j++) {
			if(j%3==0 && !color) printf("| ");
			if(color) {
				printf("%s%d \033[0m",colors(s->belegung[i][j]),s->feld[i][j]);
			}else
				printf("%d ",s->feld[i][j]);

		}
		if(!color) printf("|");
		printf("\n");
	}
	if(!color) printf("+-------+-------+-------+\n");
}

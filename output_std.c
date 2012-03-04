#include "types.h"
#include "output_std.h"
#include <stdio.h>

void std_ausgabe_unicode(sudoku* s,int color) {
	int i,j;
	printf("┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓\n");
	for(i=0;i<9;i++) {
		if(i%3==0 && i!=0) printf("┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫\n");
			else if (i!=0) printf("┠───┼───┼───╂───┼───┼───╂───┼───┼───┨\n");
		for(j=0;j<9;j++) {
			if(j%3==0) printf("┃ ");
				else printf("│ ");
			if(color) {
				if(s->feld[i][j] == 0) {
					/* printf("\033[30;1m?\033[0m "); */
					printf("  ");
				}else if(s->vorgabe[i][j] == 1){ 
					printf("\033[32;1m%d\033[0m ",s->feld[i][j]);
				}else if(s->vorgabe[i][j] == 2){ 
					printf("\033[33;1m%d\033[0m ",s->feld[i][j]);
				}else{
					printf("%d ",s->feld[i][j]);
				}   
			}else{
				if(s->feld[i][j] == 0) {
					printf("  ");
				}else{
					printf("%d ",s->feld[i][j]);
				}
			}

		}   
		printf("┃\n");
	}
	printf("┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛\n");
}

void std_ausgabe(sudoku* s,int color) {
	int i,j;
	for(i=0;i<9;i++) {
		if(i%3==0) printf("+-------+-------+-------+\n");
		for(j=0;j<9;j++) {
			if(j%3==0) printf("| ");
			if(color) {
				if(s->feld[i][j] == 0) {
					printf("\033[30;1m?\033[0m ");
				}else if(s->vorgabe[i][j] == 1){
					printf("\033[32;1m%d\033[0m ",s->feld[i][j]);
				}else if(s->vorgabe[i][j] == 2){
					printf("\033[33;1m%d\033[0m ",s->feld[i][j]);
				}else{
					printf("%d ",s->feld[i][j]);
				}
			}else
				printf("%d ",s->feld[i][j]);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}
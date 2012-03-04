#include "output.h"
#include <stdio.h>

int s_write(char* fn,sudoku* s) {
	/* Sudoku in Datei schreiben */
	int i,j;
	FILE * fp = fopen(fn,"w");
	if(fp == NULL) return 0;
	printf("Schreibe in Datei `%s'...\n",fn);
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			fputc(s->feld[i][j]+48,fp);
		}
		fputc( 10, fp);
	}
	fclose(fp);
	return 1;
}

int s_write_error(char* fn,int err) {
	/* Fehler in Datei schreiben */
	FILE * fp = fopen(fn,"w+");
	if(fp == NULL) return 0;
	printf("Schreibe Fehler in Datei `%s'...\n",fn);
	switch(err) {
		case 0:
			fputs("Eingabefehler\nEingabedatei ist Fehlerhaft!\n",fp);
			break;
		case 1:
			fputs("Eingabefehler\nSudoku ist nicht Loesbar! (Kein Loeseversuch)\n",fp);
			break;
		case 2:
			fputs("Eingabefehler\nSudoku ist nicht Loesbar!\n",fp);
			break;
		default:
			fputs("Eingabefehler\n",fp);
	}
	fclose(fp);
	return 1;
}

void s_plain(sudoku* s, int color) {
	int i,j;
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			printf("%d",s->feld[i][j]);
		}
		printf("\n");
	}
}

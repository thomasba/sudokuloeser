/*
 *      sudokuloeser.c
 *      
 *      Copyright 2010 Thomas Battermann <software@thomasba.de>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef linux
	#include <regex.h>
#endif

typedef struct sudoku {
	char feld[9][9];    /* Feld mit den Zahlen */
	char vorgabe[9][9]; /* Fuer Farbige Ausgabe auf der Linuxkonsole benoetigt */
	char mgl[9][9][9];  /* Moegliche Zahlen (fuer Logik); 0=moeglich; 1=nicht moeglich; !! */
	char notnull;       /* Anzahl der verbleibenden leeren zellen, nur fuer logik */
} sudoku;

/* Allgemeine Funktionen */
	int  s_einlesen(char*, sudoku*); /* Einlesen aus Datei*/
	void s_ausgabe(sudoku*); /* Auf dem bildschirm ausgeben */
	void print_help(int,char**); /* "Hilfe" ausgeben */
/* Loeserfunktionen */
	/* Funktion fuer Backtracking */
		int  s_loes_track(sudoku*,int); /* Funktion zum loesen des Sudokus mithilfe von Backtracking */
		int  s_test(sudoku*,int,int,int); /* Testen ob eine Zahl in ein "Feld" passt */
	/* Funktionen fuer Logik */
		int  sl_loes(sudoku*); /* Versuch das Sudoku auf logischem wege zu loesen */
		void sl_set_num(sudoku*,int,int,int); /* Setzt eine Zahl, wenn diese via logik gefunden wurde. */  
		int  sl_check_nums(sudoku*,int,int,int); /* prueft ob eine zahl alleine in einem block... ist*/
/* Ausgabe in Datei */
	int  s_write(char*,sudoku*); /* Ausgabe in Datei schreiben */
	int  s_write_error(char*,int); /* Bei Fehler in Datei schreiben */

#ifdef linux
const int OUTPUT_COLOR=1;
#else
const int OUTPUT_COLOR=0;
#endif

int main(int argc, char **argv) {
	sudoku s={ {{0}}, {{0}}, {{{1}}}, 81 };
	int st=0,sl=0,ret=0;
#ifdef linux
	struct timespec ts,te,l_ts,l_te;
	long double t;
	clock_gettime(CLOCK_REALTIME, &ts);
#endif
	/* Hilfe ausgeben, wenn angefordert oder zuwenig Parameter */
	if(argc < 2 || strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
		print_help(argc,argv);
		exit(0);
	}
	/* Aus Datei einlesen und Fehler auswerten */
	st = s_einlesen(argv[1],&s);
	if(st == 0) {
		fprintf(stderr,"Ungueltiges Dateiformat!\n");
		s_write_error( (argc == 3) ? argv[2] : "sudoku_geloest.txt",0 );
		return 2;
	}else if(st == -1) {
		#ifdef linux
		fprintf(stderr,"\033[31;1mDas Sudoku ist nicht loesbar!!\033[0m\n\n");
		#else
		fprintf(stderr,"Das Sudoku ist nicht loesbar!!\n\n");
		#endif
		s_write_error( (argc == 3) ? argv[2] : "sudoku_geloest.txt",1 );
		return 1;
	}
	/* Sudoku Loesen, Loseung ausgeben und in Datei schreiben */
	printf("Suche...\nProbiere es mit Logik...     ");
#ifdef linux
	clock_gettime(CLOCK_REALTIME, &l_ts);
#endif
	sl = sl_loes(&s);
	if(sl != 1) {
		printf("FAIL\nNun mit Backtracking...      ");
		sl = s_loes_track(&s,0);
		printf("%s\n",(sl != 1 ? "FAIL" : "OK" ));
	}else{
		printf("OK\n");
	}
#ifdef linux
	clock_gettime(CLOCK_REALTIME, &l_te);
#endif
	if(sl == 0) {
		#ifdef linux
		printf("\033[31;1mDas Sudoku ist nicht loesbar!!\033[0m\n");
		#else
		fprintf(stderr,"Das Sudoku ist nicht loesbar!!\n");
		#endif
		s_write_error( (argc == 3) ? argv[2] : "sudoku_geloest.txt",2 );
		ret = 1;
	}else{
		#ifdef linux
		printf("\033[32;1mLoesung gefunden:\033[0m\n\n");
		#else
		printf("Loesung gefunden:\n\n");
		#endif
		s_ausgabe(&s);
		s_write( (argc == 3) ? argv[2] : "sudoku_geloest.txt",&s );
	}
#ifdef linux
	clock_gettime(CLOCK_REALTIME, &te);
	t = (l_te.tv_sec + l_te.tv_nsec*0.000000001)-(l_ts.tv_sec + l_ts.tv_nsec*0.000000001);
	printf("\nBenoetigte Zeit (loesen): %Lfs\n",t);
	t = (te.tv_sec + te.tv_nsec*0.000000001)-(ts.tv_sec + ts.tv_nsec*0.000000001);
	printf("Benoetigte Zeit (gesamt): %Lfs\n",t);
#endif
	return ret;
}

int s_einlesen(char * path, sudoku * sf) {
	int k;
	FILE * fp = fopen(path,"r");
	char ch;
	char tmp[50] = "";
	char line[150] = "";
	int z=0,sp=0;
#ifdef linux
	regmatch_t m[1];
	regex_t reg;
#endif
	if(fp == NULL) return 0;
#ifdef linux
	while(fgets(tmp,100,fp)) {
		if(strlen(line)+strlen(tmp) >= 150) {
			fprintf(stderr,"Datei ist zu lang!\n");
			return 0;
		}
		strcat(line,tmp);
	}
	if(regcomp(&reg,"([ 0-9]{0,9}\r?\n){8}[ 0-9]{0,9}\r?\n?$",REG_EXTENDED) == 0 && regexec(&reg,line,1,m,REG_EXTENDED) == 0 && m[0].rm_so == 0) {
		regfree(&reg);
	}else{
		fprintf(stderr,"Kein Sudoku gefunden!\n");
		regfree(&reg);
		return 0;
	}
	rewind(fp);
#endif
	while(fgets(line,100,fp)) {
		k=0;
		for(sp=0;sp<9;sp++) {
			ch = line[sp];
			if(k == 1 || ch == '\0' || ch == '\n' || ch == '\r') {
				k = 1;
				ch = 0;
			}else{
				ch-=48;
			}
			if(0<ch && ch<=9) {
				if(s_test(sf,z,sp,ch) == 0) return -1;
				sf->feld[z][sp] = (ch<0||ch>9)?0:ch;
				if(sf->feld[z][sp] > 0) {
					sl_set_num(sf,sf->feld[z][sp],z,sp);
				}
				sf->vorgabe[z][sp] = (ch<1||ch>9)?0:1;
				sf->notnull--;
			}
		}
		if(++z >= 9) break;
	}
	fclose(fp);
	if(z<9) return 0;
	return 1;
}

void s_ausgabe(sudoku* s) {
	int i,j;
	for(i=0;i<9;i++) {
		if(i%3==0) printf("+-------+-------+-------+\n");
		for(j=0;j<9;j++) {
			if(j%3==0) printf("| ");
#ifdef linux
			if(s->feld[i][j] == 0) {
				printf("\033[30;1m?\033[0m ");
			}else if(s->vorgabe[i][j] == 1){
				printf("\033[32;1m%d\033[0m ",s->feld[i][j]);
			}else if(s->vorgabe[i][j] == 2){
				printf("\033[33;1m%d\033[0m ",s->feld[i][j]);
			}else{
				printf("%d ",s->feld[i][j]);
			}
#else
			printf("%d ",s->feld[i][j]);
#endif

		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}

void print_help(int argc, char **argv) {
#ifdef linux
	printf("\033[0;1mUsage:\033[0m\n");
	printf("  %s <input_file> [<output_file>]\n",argv[0]);
	printf("\033[0;1mAusgabe:\033[0m\n");
	printf("  \033[32;1mgruen:\033[0m Vorgegebene Werte\n");
	printf("  \033[33;1mgelb:\033[0m  Mit Logik gefundene Werte\n");
	printf("  weis:  Per Backtracking gefundene Werte\n\n");
	printf("By Thomas Battermann\n");
#else
    printf("Usage:\n");
    printf("  %s <input_file> [<output_file>]\n\n",argv[0]);
    printf("By Thomas Battermann\n");
#endif
}

int  s_test(sudoku *s, int z, int sp, int zahl) {
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

int s_loes_track(sudoku * s, int pos) {
	int i,x=pos/9,y=pos%9;
	if(pos == 81) return 1;
	if(s->feld[x][y] != 0) {
		return s_loes_track(s,pos+1);
	}else{
		for(i=1;i<=9;i++) {
			if(s->mgl[x][y][i-1] != 1 && s_test(s,x,y,i) == 1) {
				s->feld[x][y] = i;
				if(s_loes_track(s,pos+1) == 1) {
					return 1;
				}
			}
		}
	}
	s->feld[x][y] = 0;
	return 0;
}

int  s_write(char* fn,sudoku* s) {
	/* Sudoku in Datei schreiben */
	int i,j;
	FILE * fp = fopen(fn,"w");
	if(fp == NULL) return 0;
	for(i=0;i<9;i++) {
		for(j=0;j<9;j++) {
			fputc(s->feld[i][j]+48,fp);
		}
		fputc( 10, fp);
	}
	fclose(fp);
	return 1;
}

int  s_write_error(char* fn,int err) {
	/* Fehler in Datei schreiben */
	FILE * fp = fopen(fn,"w+");
	if(fp == NULL) return 0;
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

void sl_set_num(sudoku* s,int zahl,int z, int sp) {
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

int sl_check_nums(sudoku* s,int zahl,int z, int sp) {
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

int  sl_loes(sudoku* s) {
	int z,sp,repl=1,zahl;
	while(repl) {
		repl = 0;
		for(z=0;z<9;z++) {
			for(sp=0;sp<9;sp++) {
				for(zahl=1;zahl<=9;zahl++) {
					if(s->mgl[z][sp][zahl-1] != 1 && s->vorgabe[z][sp] == 0 && s->feld[z][sp] == 0 && sl_check_nums(s,zahl,z,sp) == 1) {
						s->feld[z][sp] = zahl;
						s->vorgabe[z][sp] = 2;
						sl_set_num(s,zahl,z,sp);
						s->notnull--;
						repl = 1;
					}
				}
			}
		}
	}
	if(s->notnull != 0) return 0;
	return 1;
}

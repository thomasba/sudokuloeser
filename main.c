/*
 * main.c
 * 
 * Copyright 2012 Thomas Battermann <software@thomasba.de>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "main.h"
#include "input.h"
#include "input_nstd.h"
#include "solver.h"
#include "solver_std.h"
#include "solver_nstd.h"
#include "output.h"
#include "output_std.h"
#include "output_nstd.h"
#include "html.h"
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
#ifdef linux
	options o = {0,1,0,0,0,0,1,NULL,NULL,NULL,NULL,NULL,NULL};
#else
	options o = {0,0,0,0,0,0,1,NULL,NULL,NULL,NULL,NULL,NULL};
#endif
	sudoku s={ {{0}}, {{0}}, {{0}}, {{{1}}}, 81 };
	char st=0,ret=0;
	int i,j;
#ifdef linux
	struct timespec ts,te,l_ts,l_te;
	long double t;
	clock_gettime(CLOCK_REALTIME, &ts);
#endif
	/* Read the command line parameters */
	readOptions(argc,argv,&o);
	/* feed the functions */
	if(o.overlay == NULL) {
		newStandard(&o);
	}else{
		newNonStandard(&o);
	}
	/* die belegung der zellen einlesen */
	if( o.overlay != NULL) {
		if( s_b_einlesen(o.overlay,&s) == 0 ) {
			fprintf(stderr,"Ungueltiges Dateiformat (Overlay)!\n");
			return 2;
		}
	}else if(o.html == 1){
		for(i=0;i<9;i++) {
			for(j=0;j<9;j++) {
				s.belegung[i][j] = ((i/3)*3)+1+(j/3);
			}
		}
	}
	/* Aus Datei einlesen und Fehler auswerten */
	st = s_einlesen(o.infile,&s,&o);
	if(st == 0) {
		fprintf(stderr,"Ungueltiges Dateiformat!\n");
		if(o.outfile != NULL) s_write_error( o.outfile ,0 );
		return 2;
	}else if(st == -1) {
		if(o.color)
			fprintf(stderr,"\033[31;1mDas Sudoku ist nicht loesbar!!\033[0m\n\n");
		else
			fprintf(stderr,"Das Sudoku ist nicht loesbar!!\n\n");
		if(o.outfile != NULL) s_write_error( o.outfile ,1 );
		return 1;
	}
	/* falls nicht gelöst werden soll: */
	if(o.solve == 0) {
		o.ausgabe(&s,o.color);
		return 0;
	}
	/* Sudoku Loesen, Loseung ausgeben und in Datei schreiben */
	if(!o.silent) printf("Suche...\nProbiere es mit Logik...     ");
#ifdef linux
	clock_gettime(CLOCK_REALTIME, &l_ts);
#endif
	st = sl_loes(&s,&o);
	if( st != 1 ) {
		if(!o.silent) printf("FAIL\nNun mit Backtracking...      ");
		st = s_loes_track(&s,0,&o);
		if(!o.silent) printf("%s\n",(st != 1 ? "FAIL" : "OK" ));
	}else{
		if(!o.silent) printf("OK\n");
	}
#ifdef linux
	clock_gettime(CLOCK_REALTIME, &l_te);
#endif
	if(st == 0) {
		if(o.color)
			fprintf(stderr,"\033[31;1mDas Sudoku ist nicht loesbar!!\033[0m\n");
		else
			fprintf(stderr,"Das Sudoku ist nicht loesbar!!\n");
		if(o.outfile != NULL) s_write_error( o.outfile , 2 );
		ret = 1;
	}else{
		if(o.color) {
			if(!o.silent) printf("\033[32;1mLoesung gefunden:\033[0m\n\n");
		}else{
			if(!o.silent) printf("Loesung gefunden:\n\n");
		}
		o.ausgabe(&s,o.color);
		if(o.outfile != NULL) o.write( o.outfile ,&s );
	}
#ifdef linux
	if(!o.silent) {
		clock_gettime(CLOCK_REALTIME, &te);
		t = (l_te.tv_sec + l_te.tv_nsec*0.000000001)-(l_ts.tv_sec + l_ts.tv_nsec*0.000000001);
		printf("\nBenoetigte Zeit (loesen): %Lfs\n",t);
		t = (te.tv_sec + te.tv_nsec*0.000000001)-(ts.tv_sec + ts.tv_nsec*0.000000001);
		printf("Benoetigte Zeit (gesamt): %Lfs\n",t);
	}
#endif
	return ret;
}

/*
 * Read the given options and save them
 */
void readOptions(int argc, char **argv, options * o) {
	char c;
	while ((c = getopt (argc, argv, "chHo:O:uUnsp")) != -1) {
		switch(c) {
			case 'h':
				print_help(argc,argv);
				exit(0);
				break;
			case 'u':
			case 'U':
				o->unicode = 1;
				break;
			case 'H':
				if(o->html) o->force_html = 1;
				o->html = 1;
				break;
			case 'c':
				o->color = 0;
				break;
			case 'O':
				if(o->overlay == NULL && strcmp(optarg,"") != 0)
					o->overlay = optarg;
				break;
			case 'o':
				if(o->outfile == NULL && strcmp(optarg,"") != 0)
					o->outfile = optarg;
				break;
			case 'n':
				o->solve = 0;
				break;
			case 's':
				o->silent = 1;
				break;
			case 'p':
				o->plaintext = 1;
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);
				exit(1);
				break;
		}
	}
	if((argc-optind) != 1) {
		print_help(argc,argv);
		exit(0);
	}
	if(o->html != 0 && (o->outfile == NULL || o->force_html)) {
		o->silent = 1;
	}
	o->infile = argv[optind];
}
void newStandard(options * o) {
	o->check_nums = solver_check_nums;
	o->set_num = solver_set_num;
	o->test = solver_test;
	/* Check which out put to use */
	o->write = s_write;
	if(o->unicode) {
		o->ausgabe = std_ausgabe_unicode;
	}else if(o->plaintext) {
		o->ausgabe = s_plain;
	}else{
		o->ausgabe = std_ausgabe;
	}
	if(o->html) {
		if(o->outfile == NULL || o->force_html)
			o->ausgabe = out_html;
		o->write = write_html;
	}
}
void newNonStandard(options * o) {
	o->check_nums = solver_nstd_check_nums;
	o->set_num = solver_nstd_set_num;
	o->test = solver_nstd_test;
	/* Check which out put to use */
	o->write = s_write;
	if(o->unicode) {
		o->ausgabe = nstd_ausgabe_unicode;
	}else if(o->plaintext) {
		o->ausgabe = s_plain;
	}else{
		o->ausgabe = nstd_ausgabe;
	}
	if(o->html) {
		if(o->outfile == NULL || o->force_html)
			o->ausgabe = out_html;
		o->write = write_html;
	}
}

void print_help(int argc, char **argv) {
#ifdef linux
	printf("\033[0;1mUsage:\033[0m\n");
	printf("  %s [options] <input_file>\n",argv[0]);
	printf("\033[0;1mOptions\033[0m\n");
	printf("  -U         Unicode borders\n");
	printf("  -h         This help\n");
	printf("  -H         HTML-Output\n");
	printf("             twice: print on stdout, even if outfile given\n");
	printf("  -o <file>  Output-File\n");
	printf("  -O <file>  Overlay for non-standard files\n");
	printf("  -c         No colors\n");
	printf("  -p         Plaintext\n");
	printf("  -n         Dont solve, just print\n");
	printf("  -s         silent\n");
	printf("\033[0;1mOutput:\033[0m\n");
	printf("  \033[32;1mgreen:\033[0m     Given values\n");
	printf("  \033[33;1myellow:\033[0m      Values find by logic\n");
	printf("  white:      Values find by backtracking\n\n");
	printf("By Thomas Battermann\n");
#else
printf("Usage:\n");
	printf("  %s [options] <input_file>\n",argv[0]);
	printf("Options\n");
	printf("  -U         Unicode borders\n");
	printf("  -h         This help\n");
	printf("  -H         HTML-Output\n");
	printf("             twice: print on stdout, even if outfile given\n");
	printf("  -o <file>  Output-File\n");
	printf("  -O <file>  Overlay for non-standard files\n");
	printf("  -p         Plaintext\n");
	printf("  -n         Dont solve, just print\n");
	printf("  -s         silent\n\n");
	printf("By Thomas Battermann\n");
#endif
}

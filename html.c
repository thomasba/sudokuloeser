#include <stdio.h>
#include "html.h"

void out_html(sudoku * s,int c) {
	genHTML(s,stdout);
}

int write_html(char* fn,sudoku* s) {
	FILE * fp = fopen(fn,"w");
	if(fp == NULL) return 0;
	genHTML(s,fp);
	fclose(fp);
	return 1;
}

void genHTML(sudoku * s,FILE * fp) {
	int i,j;
	/* Header ausgeben */
	printHead(fp);
	/* Tabelle ausgeben */
	for(i=0;i<9;i++) {
		fprintf(fp,"			<tr>\n");
		for(j=0;j<9;j++) {
			fprintf(fp,"\t\t\t\t<td class=\"c%d%s\">%d</td>\n",
				s->belegung[i][j],
				((s->vorgabe[i][j] != 0) ? ((s->vorgabe[i][j] == 1) ? " v" : "") : " b"),
				s->feld[i][j]);
		}
		fprintf(fp,"			</tr>\n");
	}
	/* Footer ausgeben */
	printFoot(fp);
}

void printHead(FILE * fp) {
	fprintf(fp,"<!DOCTYPE html>\n");
	fprintf(fp,"<html>\n");
	fprintf(fp,"	<head>\n");
	fprintf(fp,"		<meta charset=\"utf-8\">\n");
	fprintf(fp,"		<title>Sudoku (solved)</title>\n");
	fprintf(fp,"		<style type=\"text/css\">\n");
	fprintf(fp,"			.c1{background:#c8ffc8}.c2{background:#ffff66}.c3{background:#83caff}.c4{background:#ff950e}.c5{background:#0084d1}.c6{background:#aecf00}.c7{background:#ffc8c8}.c8{background:#00ffff}.c9{background:#c8c8ff}\n");
	fprintf(fp,"			table{border-collapse:collapse}td{border:1px solid #000;height:3em;width:3em;text-align:center;vertical-align:middle;font-weight:bold}\n");
	fprintf(fp,"			.v{text-decoration:underline}.b{font-style:italic}.s{font-size:0.6em}\n");
	fprintf(fp,"		</style>\n");
	fprintf(fp,"	</head>\n");
	fprintf(fp,"	<body>\n");
	fprintf(fp,"		<table>\n");
}

void printFoot(FILE * fp) {
	fprintf(fp,"		</table>\n");
	fprintf(fp,"		<p class=\"s\">\n");
	fprintf(fp,"			<span class=\"v\">Given Values</span> - <span class=\"b\">Values found by backtracking</span>\n");
	fprintf(fp,"		</p>\n");
	fprintf(fp,"	</body>\n");
	fprintf(fp,"</html>\n");
}

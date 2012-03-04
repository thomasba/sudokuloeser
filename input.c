#include "input.h"
#include <string.h>
#include <stdio.h>
#ifdef linux
	#include <regex.h>
#endif

int s_einlesen(char * path, sudoku * sf, options * o) {
	int k;
	FILE * fp = fopen(path,"r");
	char ch;
	char line[150] = "";
	int z=0,sp=0;
#ifdef linux
	char tmp[50] = "";
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
				if(o->test(sf,z,sp,ch) == 0) return -1;
				sf->feld[z][sp] = (ch<0||ch>9)?0:ch;
				if(sf->feld[z][sp] > 0) {
					o->set_num(sf,sf->feld[z][sp],z,sp);
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

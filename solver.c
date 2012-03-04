#include "solver.h"

int  sl_loes(sudoku* s, options * o) {
	int z,sp,repl=1,zahl;
	while(repl) {
		repl = 0;
		for(z=0;z<9;z++) {
			for(sp=0;sp<9;sp++) {
				for(zahl=1;zahl<=9;zahl++) {
					if(s->mgl[z][sp][zahl-1] != 1 && s->vorgabe[z][sp] == 0 && s->feld[z][sp] == 0 && o->check_nums(s,zahl,z,sp) == 1) {
						s->feld[z][sp] = zahl;
						s->vorgabe[z][sp] = 2;
						o->set_num(s,zahl,z,sp);
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

int s_loes_track(sudoku * s, int pos, options * o) {
	int i,x=pos/9,y=pos%9;
	if(pos == 81) return 1;
	if(s->feld[x][y] != 0) {
		return s_loes_track(s,pos+1,o);
	}else{
		for(i=1;i<=9;i++) {
			if(s->mgl[x][y][i-1] != 1 && o->test(s,x,y,i) == 1) {
				s->feld[x][y] = i;
				if(s_loes_track(s,pos+1,o) == 1) {
					return 1;
				}
			}
		}
	}
	s->feld[x][y] = 0;
	return 0;
}

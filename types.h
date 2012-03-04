#ifndef types_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__
#define types_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__

typedef struct sudoku {
	char feld[9][9];     /* Feld mit den Zahlen */
	char vorgabe[9][9];  /* Fuer Farbige Ausgabe auf der Linuxkonsole benoetigt */
	char belegung[9][9]; /* Die Vorgegebenen Felder */
	char mgl[9][9][9];   /* Moegliche Zahlen (fuer Logik); 0=moeglich; 1=nicht moeglich; !! */
	char notnull;        /* Anzahl der verbleibenden leeren zellen, nur fuer logik */
} sudoku;

typedef struct options {
	char unicode;	/* Unicode output */
	char color;		/* Show colors */
	char plaintext;	/* Same format as the input */
	char silent;	/* just output the result */
	char html;		/* output html (implies silent) */
	char force_html;/* force html output on stdout even if outfile given */
	char solve;		/* solve it or not */
	char* outfile;	/* outfile NULL if none */
	char* overlay;	/* overlay NULL if none */
	char* infile;	/* input file with the sudoku */
	int (*check_nums)(sudoku*,int,int,int);
	void (*set_num)(sudoku*,int,int,int);
	int (*test)(sudoku*,int,int,int);
	void (*ausgabe)(sudoku*,int);
	int (*write)(char*,sudoku*);
} options;

#endif /* types_2b894a04_3a0c_4223_bf83_6ab40c0f5e57_h__ */

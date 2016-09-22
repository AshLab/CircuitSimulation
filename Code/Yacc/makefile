CC=gcc
CFLAGS=-I

parseSPICE: YaccSPICE.y LexSpice.l
	yacc -d YaccSPICE.y
	lex LexSpice.l
	$(CC) y.tab.c lex.yy.c Simulate.c -ll -o parseSPICE.o -I.


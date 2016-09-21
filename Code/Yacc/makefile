CC=gcc
CFLAGS=-I

parseSPICE: y.tab.c lex.yy.c
	yacc -d YaccSPICE.y
	lex LexSpice.l
	$(CC) y.tab.c lex.yy.c -ll -o parseSPICE.o -I.


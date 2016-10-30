CC=gcc
CFLAGS=-I

calc: calcyac.y calclex.l
	yacc -d calcyac.y
	lex calclex.l
	$(CC) y.tab.c lex.yy.c -ll -o calc.o -I.


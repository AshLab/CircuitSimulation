CC=gcc
CFLAGS=-I

parseSPICE: YaccSPICE.y LexSpice.l Simulate.c ParseVoltage.c ParseCurrent.c Gaussian.c GaussianDC.c
	yacc -d YaccSPICE.y
	lex LexSpice.l
	$(CC) y.tab.c lex.yy.c Simulate.c ParseVoltage.c ParseCurrent.c Gaussian.c GaussianDC.c -ll -o parseSPICE.o -I.


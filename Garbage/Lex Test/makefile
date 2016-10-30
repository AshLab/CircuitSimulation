lextext: lextext.l calcyac.y
	yacc -d calcyac.y
	lex lextext.l
	gcc lex.yy.c -ll -o lextext.o -I.

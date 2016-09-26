%{
	#include<stdio.h>
	#include"y.tab.h"

	void yyerror(char *);
%}

%%

[A-Z] { yylval=yytext[0];
	//printf("\n LEX : Found %d\n", yylval);
       	return ELEMENT;
      }

[0-9]+ {yylval=atoi(yytext);
	//printf("\n LEX : Found %d\n", yylval);
	return INTEGER;
       }

[\.][a-z]+ { yylval=yytext[1];
	   return OP;
	 }

^[%].* ;

[\n] {//printf("\n LEX : Found a newline\n");
      return *yytext;
     }

[ \t] ;

. { yyerror("\n--------Parser has found something mysterious-------\n");}

%%

int yywrap(void)
{
	return 1;
}


	
	
	


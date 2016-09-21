%{
	#include<stdio.h>
	#include"y.tab.h"

	void yyerror(char *);
%}

%%

[A-Z] { yylval=atoi(yytext);
	printf("\n LEX : Found %c\n", yyval);
       	return ELEMENT;
      }

[0-9]+ {yylval=atoi(yytext);
	printf("\n LEX : Found %d\n", yyval);
	return INTEGER;
       }

[\t] ;

[\n] {printf("\n LEX : Found a newline\n");
      return *yytext;
     }

. { yyerror("--------Parser has found something mysterious : %s--------", *yytext);}

%%

int yywrap(void)
{
	return 1;
}


	
	
	


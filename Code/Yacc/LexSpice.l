%{
	#include<stdio.h>
	#include"y.tab.h"

	void yyerror(char *);
%}

%%

[A-Z] { yylval.elem=yytext[0];
	//printf("\n LEX : Found %d\n", yylval);
       	return ELEMENT;
      }

[0-9]+[\.][0-9]+ {yylval.fVal=atof(yytext);
		  return INTEGER;
		 }

[0-9]+ {yylval.fVal=atof(yytext);
	//printf("\n LEX : Found %d\n", yylval);
	return INTEGER;
       }

[\.][a-z]+ { yylval.elem=yytext[1];
	     if(yylval.elem=='p')
	     {
		printf("\n Found PLOT");		
		return PLOT;
	     }

	     else
	     {
 		printf("\n Found OP");		
        	return OP;
	     }
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


	
	
	


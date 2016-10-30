%{
	#include<stdlib.h>
	void yyerror(char *);
	#include"y.tab.h"
%}

%%

[a-z] {
	yylval.index=*yytext-'a';
	return VARIABLE;
      }
[0-9]+[\.]+[0-9]+ {
	yylval.iValue=atof(yytext);
	return INTEGER;
       }

[-+*/()=\n] {
	 return *yytext;
	}

[\t] ;

. {	
    yyerror("Illegal Character");
  } 
%%

int yywrap(void)
{	
	return 1;
}

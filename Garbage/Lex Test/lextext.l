%{
	#include<stdlib.h>
	#include"y.tab.h"
	void yyerror(char *);
	


%}

%%

[0-9]+[\.][0-9]+ {yylval.iValue=atof(yytext);
		  return FLOAT;}
[+-] {yylval.index=*yytext-'a';
      return VARIABLE;}
. ;

%%

void main(void)
{
	yyin=fopen("lextext.txt","r");
	yylex();
	fclose(yyin);
}

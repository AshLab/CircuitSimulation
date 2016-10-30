%union {
	float iValue;
	char index;
	float nPtr;
	};


%token <nPtr> expr
%token <iValue> INTEGER
%token <index> VARIABLE

%left '+' '-'
%left '*' '/'

%{
	#define YYDEBUG 1
	#include<stdio.h>

	void yyerror(char *);
	int yylex(void);
	int sym[26];
	extern FILE *yyin;

%}

%%
program: program statement
	 |
	 ;

statement: expr '\n' {printf("\n Result:%f",$1);}
	   | VARIABLE '=' expr '\n' {sym[$1]=$3; printf("\nVar:%f",$3);}
	   ;

expr: INTEGER 
      | VARIABLE {$$=sym[$1];}
      | expr '-' expr {$$=$1-$3;}
      | expr '+' expr {$$=$1+$3;}
      | expr '*' expr {$$=$1*$3;}
      | expr '/' expr {$$=$1/$3;}
      | '(' expr ')' {$$=$2;}
      ;

%%
void yyerror(char *s)
{
	fprintf(stderr,"Error:%s\n",s);
        
}

int main(void)
{
	
	//yydebug=1;
	yyin=fopen("calc.txt","r");
	
	do
	{	
		yyparse();
	}
	while(!feof(yyin));

	return 0;
}



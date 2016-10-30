%union {
	float iValue;
	char index;
	};

%token <iValue> FLOAT
%token <index> VARIABLE


%{
	#define YYDEBUG 1
	#include<stdio.h>

	void yyerror(char *);
	int yylex(void);
	int sym[26];
	extern FILE *yyin;

%}

%%

expr: expr '\n'
      |FLOAT {printf("\nFloat:%f",$1);}
      |VARIABLE {printf("\nVariable:%c",$1;};
      
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



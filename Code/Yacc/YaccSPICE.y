%token INTEGER ELEMENT

%{
	#define YYDEBUG 1
	#include<stdio.h>
	
	void yyerror(char *);
	int yylex(void);
	int node1, node2, elementNumber;
        int elementValue;
	char element;
	
	extern FILE *yyin;
%}

%%

program: program branch '\n' {printf("element =%c \n elementNumber=%d \n node1=%d \n node2=%d \n elementValue=%d\n", element, elementNumber, node1, node2, elementValue);}
	 |program '\n'
	 |
 	 ;

branch:  ELEMENT INTEGER INTEGER INTEGER INTEGER {element=$1; elementNumber=$2; node1=$3; node2=$4; elementValue=$5;};



%%

void yyerror(char *error)
{

	printf("\n\n An error has occured while parsing the SPICE file \n\n\n %s", error);
}

int main(int argc, char *argv[])
{
		
	//yydebug=atoi(argv[1][0]);
	yydebug=0;
	yyin=fopen("cir.txt","r");
	
	do
	{	
		yyparse();
	}
	while(!feof(yyin));

	return 0;
}

	


 

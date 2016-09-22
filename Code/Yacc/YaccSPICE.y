%token INTEGER ELEMENT

%{
	#define YYDEBUG 1
	#include<stdio.h>
	#include"Simulate.h"
	
	void yyerror(char *);
	int yylex(void);
	int YaccParse(char *);

	int node1, node2, elementNumber;
        int elementValue;
	char element;
	struct elementData *tempAddress=NULL;

	
	extern FILE *yyin;
	
	
%}

%%

program: program branch '\n' {	
				
				parsedNode=(struct elementData*)(malloc(sizeof(struct elementData)));
				parsedNode->node1=node1;
				parsedNode->node2=node2;
				parsedNode->elementNumber=elementNumber;
				parsedNode->elementValue=elementValue;
				parsedNode->element=element;
				
				parsedNode->link=tempAddress;
				tempAddress=parsedNode;
				}
	 |program '\n'
	 |
 	 ;

branch:  ELEMENT INTEGER INTEGER INTEGER INTEGER {element=$1; elementNumber=$2; node1=$3; node2=$4; elementValue=$5;};



%%
void yyerror(char *error)
{

	printf("\n\n An error has occured while parsing the SPICE file \n\n\n %s", error);
}

int YaccParse(char *fileName)  
{
		
	//yydebug=atoi(argv[1][0]);
	//yydebug=argc-1;
	yyin=fopen(fileName,"r");
	
	do
	{	
		yyparse();
	}
	while(!feof(yyin));

	fclose(yyin);

	return 1;
}

	


 

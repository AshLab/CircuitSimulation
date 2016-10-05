%token INTEGER ELEMENT OP PLOT

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
	char runMode;
	float startVal, stopVal, stepVal;

	struct elementData *tempAddress=NULL;
	struct plotNode *tempplotAdd=NULL;

	
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

	 |program dc '\n' {	
				mode.modeType=runMode;
			     	mode.startValue=startVal;
				mode.stopValue=stopVal;
				mode.stepValue=stepVal;
				mode.element=element;
				mode.elementNumber=elementNumber;
			    }
	 |program plotvar '\n' {printf("\n\nParsed node : %d",plotInfo->nodeNo);}
				
		
	 |program '\n'
	 |
 	 ;

branch:  ELEMENT INTEGER INTEGER INTEGER INTEGER {element=$1; elementNumber=$2; node1=$3; node2=$4; elementValue=$5;};

dc: dc INTEGER INTEGER INTEGER ELEMENT INTEGER {startVal=$2;stopVal=$3;stepVal=$4; element=$5; elementNumber=$6;}	 
    |OP {runMode=$1;}
    ;

plotvar: plotvar INTEGER {plotInfo=(struct plotNode*)malloc(sizeof(struct plotNode));
			  plotInfo->nodeNo=$2;
			  plotInfo->link=tempplotAdd;
			  plotCount++;
			  tempplotAdd=plotInfo;}
	|PLOT
	; 





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

	


 

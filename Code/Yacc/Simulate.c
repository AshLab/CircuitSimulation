#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include"Simulate.h"


struct elementData *parsedNode=NULL;

void main(void)
{

	int YaccParse(char*);

	int parseResult;
	

	parseResult=YaccParse("cir.txt");
	
	while(parsedNode!=NULL)
	{
	printf("\n%d %d %d %d %c\n", parsedNode->node1,parsedNode->node2,parsedNode->elementNumber,parsedNode->elementValue,parsedNode->element);

		parsedNode=parsedNode->link;
	}


}

	
	
	

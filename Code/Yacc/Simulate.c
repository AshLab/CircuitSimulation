#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include"Simulate.h"


struct elementData *parsedNode=NULL;
struct voltageNode *vNode=NULL;
struct currentNode *cNode=NULL;


void main(void)
{
	struct elementData *tempNode;	
	struct voltageNode *tempvoltageNode;
	struct currentNode *tempcurNode;
	
	int YaccParse(char*);
	int ExCurrentNode();
	int ExVoltageNode();

	int parseResult;
	

	parseResult=YaccParse("cir.txt");
	
	tempNode=parsedNode;
	
	/*while(tempNode!=NULL)
	{
	printf("\n%d %d %d %d %c\n", tempNode->node1,tempNode->node2,tempNode->elementNumber,tempNode->elementValue,tempNode->element);

		tempNode=tempNode->link;
	}*/

	
	parseResult=ExVoltageNode();
	
	tempvoltageNode=vNode;

	while(tempvoltageNode!=NULL)
	{
		printf("\n%d", tempvoltageNode->nodeNo);
		tempvoltageNode=tempvoltageNode->link;
	}
	
	parseResult=ExCurrentNode();

	tempcurNode=cNode;

	while(tempcurNode!=NULL)
	{
		printf("\n%d", tempcurNode->elementName);
		tempcurNode=tempcurNode->link;
	}
}

	
	
	

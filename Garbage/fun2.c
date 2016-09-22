#include<stdio.h>
#include<stdlib.h>
#include"Simulate.h"

void modify()
{
	parsedNode=(struct elementData*)(malloc(sizeof(struct elementData)));
	
	parsedNode->node1=1;
	parsedNode->node2=5;
	parsedNode->elementNumber=10;
	parsedNode->elementValue=1000;
	parsedNode->element='R';
	parsedNode->link=parsedNode;

}



	

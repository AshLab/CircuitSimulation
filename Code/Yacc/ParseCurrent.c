#include<stdio.h>
#include<stdlib.h>
#include"Simulate.h"

int ExCurrentNode(void)
{

	struct elementData *tempNode;
	struct currentNode *tempcurNode;
	int i=0;
	
	tempNode=parsedNode;

	tempcurNode=NULL;

	while(tempNode!=NULL)
	{

			
		if(tempNode->element=='V')
		{
			cNode=(struct currentNode*) malloc(sizeof(struct currentNode));
			cNode->elementName=tempNode->elementNumber;
			cNode->link=tempcurNode;
			tempcurNode=cNode;
			i++;
		}

		tempNode=tempNode->link;
		
	}

	return i;

}	

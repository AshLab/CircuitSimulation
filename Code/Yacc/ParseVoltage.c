#include<stdio.h>
#include<stdlib.h>
#include"Simulate.h"

int ExVoltageNode(void)
{

	struct elementData *tempNode;
	struct voltageNode *headNode, *tempvoltageNode;
	int i=0, end1=1,end2=1;
	
	tempNode=parsedNode;

	vNode=(struct voltageNode*) malloc(sizeof(struct voltageNode));
	vNode->nodeNo=0;
	vNode->link=NULL;

	while(tempNode!=NULL)
	{
		tempvoltageNode=vNode;

		end1=1;
		end2=1;	
	
		while(tempvoltageNode!=NULL && (end1!=0 || end2!=0) )
		{

			
			if(tempNode->node1==tempvoltageNode->nodeNo && end1==1)
			{
				end1=0;
			}

			if(tempNode->node2==tempvoltageNode->nodeNo && end2==1)
			{
				end2=0;
			}

			tempvoltageNode=tempvoltageNode->link;
		}
		
		if(end1!=0)
		{
			tempvoltageNode=vNode;
			vNode=(struct voltageNode*) malloc(sizeof(struct voltageNode));
			vNode->nodeNo=tempNode->node1;
			vNode->link=tempvoltageNode;
			i++;
		}
			
		if(end2!=0)
		{
			tempvoltageNode=vNode;
			vNode=(struct voltageNode*) malloc(sizeof(struct voltageNode));
			vNode->nodeNo=tempNode->node2;
			vNode->link=tempvoltageNode;
			i++;
		}	

		tempNode=tempNode->link;
		
	}
	
	printf("\nVoltage : %d",i);

	return i;


}	

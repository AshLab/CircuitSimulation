#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include"Simulate.h"


struct elementData *parsedNode=NULL;
struct voltageNode *vNode=NULL;
struct currentNode *cNode=NULL;

int SearchNodes(int);
int SearchVoltageSource(int);

void main(void)
{
	struct elementData *tempNode;	
	struct voltageNode *tempvoltageNode;
	struct currentNode *tempcurNode;
	
	int YaccParse(char*);
	int ExCurrentNode();
	int ExVoltageNode();
	

	int totalNodes,totalVoltageSource,nodalElements,i=0,j=0,k=0,parseResult;
	float G=0;
	float **nodalMatrix; 
	int *nodalValues, *nodalVariables;
	

	parseResult=YaccParse("cir.txt");
	
	tempNode=parsedNode;
	
	/*while(tempNode!=NULL)
	{
	printf("\n%d %d %d %d %c\n", tempNode->node1,tempNode->node2,tempNode->elementNumber,tempNode->elementValue,tempNode->element);

		tempNode=tempNode->link;
	}*/

	
	totalNodes=ExVoltageNode();
	
	tempvoltageNode=vNode;

	while(tempvoltageNode!=NULL)
	{
		printf("\nV:%d", tempvoltageNode->nodeNo);
		tempvoltageNode=tempvoltageNode->link;
	}
	
	totalVoltageSource=ExCurrentNode();

	tempcurNode=cNode;

	while(tempcurNode!=NULL)
	{
		printf("\nC:%d", tempcurNode->elementName);
		tempcurNode=tempcurNode->link;
	}

	nodalElements=totalNodes+totalVoltageSource;
	printf("\nTotal :%d",nodalElements);

	nodalMatrix= (float **) malloc(nodalElements*sizeof(float*));
	
	for(i=0;i<nodalElements;i++)
	{
		nodalMatrix[i]=(float *) malloc(nodalElements*sizeof(float));	
	}

	nodalValues=(int *) malloc(nodalElements*sizeof(int));

	

	for(i=0;i<nodalElements;i++)
	{	
		nodalValues[i]=0;

		for(j=0;j<nodalElements;j++)
		{
			nodalMatrix[i][j]=0;
		}
	}
	
	tempNode=parsedNode;
	
	while(tempNode!=NULL)
	{
		if(tempNode->element=='R')
		{
			i=SearchNodes(tempNode->node1);
			j=SearchNodes(tempNode->node2);
			
			G=(float)1/tempNode->elementValue;
			
			if(i!=-1)
			{
				nodalMatrix[i][i]=G+nodalMatrix[i][i];
			}
	
			if(j!=-1)
			{
				nodalMatrix[j][j]=G+nodalMatrix[j][j];
			}

			if(i!=-1 && j!=-1)
			{
				nodalMatrix[i][j]=nodalMatrix[i][j]-G;
				nodalMatrix[j][i]=nodalMatrix[j][i]-G;
		
			}
		}

		if(tempNode->element=='V')
		{
			i=SearchNodes(tempNode->node1);
			j=SearchNodes(tempNode->node2);
			k=SearchVoltageSource(tempNode->elementNumber)+nodalElements-1;
			
			
			
			if(i!=-1)
			{
				nodalMatrix[i][k]=1;
				nodalMatrix[k][i]=1;
				
			}
	
			if(j!=-1)
			{
				nodalMatrix[j][k]=-1;
				nodalMatrix[k][j]=-1;
			}

			nodalValues[k]=tempNode->elementValue;
		}

	
	tempNode=tempNode->link;
	}


	for(i=0;i<nodalElements;i++)
	{	
		printf("\n");

		for(j=0;j<nodalElements;j++)
		{
			printf("%f\t",nodalMatrix[i][j]);
		}
	}

	printf("\n \n\n");

	for(j=0;j<nodalElements;j++)
	{
		printf("%d\t",nodalValues[j]);
	}
}

int SearchNodes(int node)
{
	struct voltageNode *tempvoltageNode;
	int end=1, count=-1;
	
	if(node!=0)
	{
		tempvoltageNode=vNode;
	
		while(tempvoltageNode!=NULL && end!=0)
		{
			count++;
			if(node==tempvoltageNode->nodeNo)
			{
				end=0;
			}
			
			tempvoltageNode=tempvoltageNode->link;
		
		}
	}
	
	return count;
}


int SearchVoltageSource(int node)
{
	struct currentNode *tempcurNode;
	int end=1, count=-1;
	
	if(node!=0)
	{
		tempcurNode=cNode;
	
		while(tempcurNode!=NULL && end!=0)
		{
			count++;

			if(node==tempcurNode->elementName)
			{
				end=0;
			}
			
			tempcurNode=tempcurNode->link;
		
		}
	}
	
	return count;
}

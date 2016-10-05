#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include"Simulate.h"


struct elementData *parsedNode=NULL;
struct voltageNode *vNode=NULL;
struct currentNode *cNode=NULL;
struct plotNode *plotInfo=NULL;
struct runMode mode;
int plotCount=0;

int SearchNodes(int);
int SearchVoltageSource(int);

void main(void)
{
	struct elementData *tempNode;	
	struct voltageNode *tempvoltageNode;
	struct currentNode *tempcurNode;
	struct plotNode *tempplotAdd;
	
	
	int YaccParse(char*);
	int ExCurrentNode();
	int ExVoltageNode();
	void FindSolution(float**,float*,float*,int);
	void FindSolutionDC(float**, float*, float*, int, int);
	

	int totalNodes,totalVoltageSource,nodalElements,i=0,j=0,k=0,parseResult;
	float G=0;
	float **nodalMatrix; 
	float *nodalValues, *solution; 
	int *nodalVariables;
	
	

	parseResult=YaccParse("cir.txt");
	
		
	tempNode=parsedNode;
	printf("\n\n----------------PARSED DATA--------------------------------------------------");
	printf("\n%c %f %f %f %c %d\n\n\n",mode.modeType,mode.startValue,mode.stopValue,mode.stepValue,mode.element,mode.elementNumber);
	
	while(tempNode!=NULL)
	{
	printf("\n%d %d %d %d %c\n", tempNode->node1,tempNode->node2,tempNode->elementNumber,tempNode->elementValue,tempNode->element);

		tempNode=tempNode->link;
	}
	printf("\n\n----------------PARSED DATA--------------------------------------------------");
	
	totalNodes=ExVoltageNode();
	
	tempvoltageNode=vNode;

	

	while(tempvoltageNode!=NULL)
	{
		printf("\nV:%d", tempvoltageNode->nodeNo);
		tempvoltageNode=tempvoltageNode->link;
	}
	
	totalVoltageSource=ExCurrentNode();

	nodalElements=totalNodes+totalVoltageSource;
	printf("\nTotal :%d",nodalElements);

	tempcurNode=cNode;

	while(tempcurNode!=NULL)
	{
		printf("\nC:%d", tempcurNode->elementName);
		tempcurNode=tempcurNode->link;
	}
	
	//Mapping the Plot Number
	printf("\n\n----------------PLOT NUMBER--------------------------------------------------");
	
	tempplotAdd=plotInfo;

	while(tempplotAdd!=NULL)
	{
		tempplotAdd->colNo=SearchNodes(tempplotAdd->nodeNo);

		printf("\n%d \t %d",tempplotAdd->nodeNo,tempplotAdd->colNo);

		tempplotAdd=tempplotAdd->link;

		
	}
		
	printf("\n\n----------------PLOT NUMBER--------------------------------------------------");

	//system(sleep(1));

	nodalMatrix= (float **) malloc(nodalElements*sizeof(float*));
	
	for(i=0;i<nodalElements;i++)
	{
		nodalMatrix[i]=(float *) malloc(nodalElements*sizeof(float));	
	}

	nodalValues=(float *) malloc(nodalElements*sizeof(float));
	solution=(float *) malloc(nodalElements*sizeof(float));

	

	for(i=0;i<nodalElements;i++)
	{	
		nodalValues[i]=0;
		solution[i]=0;

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
			k=SearchVoltageSource(tempNode->elementNumber)+totalNodes;
			
			
			
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

			nodalValues[k]=(float)tempNode->elementValue;
		}

		if(tempNode->element=='I')
		{
			i=SearchNodes(tempNode->node1);
			j=SearchNodes(tempNode->node2);
			
			if(i!=-1)
			{
				nodalValues[i]=	(float)tempNode->elementValue;
			}

			
			if(j!=-1)
			{
				nodalValues[j]=	-(float)tempNode->elementValue;
			}	

		}

	
	tempNode=tempNode->link;
	}

	printf("\n\n----------------NODAL MATRIX--------------------------------------------------");
	for(i=0;i<nodalElements;i++)
	{	
		printf("\n");

		for(j=0;j<nodalElements;j++)
		{
			printf("%f\t",nodalMatrix[i][j]);
		}
		printf("%f\t",nodalValues[i]);
	}
	printf("\n\n----------------NODAL MATRIX--------------------------------------------------");




	if(mode.modeType=='o')
	{	
		FindSolution(nodalMatrix,nodalValues,solution,nodalElements);

	
		tempvoltageNode=vNode;
		tempcurNode=cNode;
	
		printf("\n\n----------------SIMULATION RESULTS--------------------------------------------------");
		for(i=0;i<nodalElements;i++)
		{
			if(i<totalNodes)
			{		
				printf("\nV(%d): %fV\n",tempvoltageNode->nodeNo, solution[i]);
				tempvoltageNode=tempvoltageNode->link;
			}

			else
			{
				printf("\n\nI_%d: %fA\n",tempcurNode->elementName, solution[i]);
				tempcurNode=tempcurNode->link;
			}
		
					
		}

		printf("\n\n----------------SIMULATION RESULTS--------------------------------------------------");
	}

	if(mode.modeType=='d')
	{

		parseResult=SearchVoltageSource(mode.elementNumber)+totalNodes;
		printf("\n\nparse Result : %d\n\n",parseResult);
		FindSolutionDC(nodalMatrix,nodalValues,solution,nodalElements,parseResult);
	}

	free(cNode);
	free(vNode);
	free(parsedNode);
	free(nodalMatrix);
	free(nodalValues);
	free(solution);
	free(plotInfo);
	

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

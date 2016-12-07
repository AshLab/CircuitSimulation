#include<stdio.h>
#include<stdlib.h>
#include"y.tab.h"
#include"Simulate.h"


struct elementData *parsedNode=NULL;
struct voltageNode *vNode=NULL;
struct currentNode *cNode=NULL;
struct plotNode *plotInfo=NULL;
struct runMode mode;
struct nonLinear nonLinearData;


int plotCount=0;


int SearchNodes(int);
int SearchVoltageSource(int);

void main(int argc, char *argv[])
{
	struct elementData *tempNode;	
	struct voltageNode *tempvoltageNode;
	struct currentNode *tempcurNode;
	struct plotNode *tempplotAdd;
	
	
	int YaccParse(char*);
	int ExCurrentNode();
	int ExVoltageNode();
	int FindSolution(double**,double*,double*,int);
	void FindSolutionDC(double**, double*, double*, int, int);
	int FindSolutionNonLinear(double**, double*, double*, int, int**, int);
	void FindSolutionNonLinearDC(double**, double*, double*, int, int**, int,int);
	

	int totalNodes,totalVoltageSource,nodalElements,i=0,j=0,k=0,parseResult, exist;
	double G=0;
	double **nodalMatrix; 
	double *nodalValues, *solution; 
	int *nodalVariables;
	int **nonLinearIndex;
	int nonLinearCount=0;
	
	
	
	nonLinearData.nonLinear=0;

	parseResult=YaccParse(argv[1]);
	
		
	tempNode=parsedNode;
	printf("\n\n----------------PARSED DATA--------------------------------------------------");
	printf("\n%c %lf %lf %lf %c %d\n\n\n",mode.modeType,mode.startValue,mode.stopValue,mode.stepValue,mode.element,mode.elementNumber);
	
	while(tempNode!=NULL)
	{
	printf("\n%d %d %d %lf %c\n", tempNode->node1,tempNode->node2,tempNode->elementNumber,tempNode->elementValue,tempNode->element);

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

	nodalMatrix= (double **) malloc(nodalElements*sizeof(double*));
	
	for(i=0;i<nodalElements;i++)
	{
		nodalMatrix[i]=(double *) malloc(nodalElements*sizeof(double));	
	}

	nodalValues=(double *) malloc(nodalElements*sizeof(double));
	solution=(double *) malloc(nodalElements*sizeof(double));

	

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
	
	
	if(nonLinearData.nonLinear==0)
	{	
		while(tempNode!=NULL)
		{
			if(tempNode->element=='R')
			{
				i=SearchNodes(tempNode->node1);
				j=SearchNodes(tempNode->node2);
			
				G=(double)1/tempNode->elementValue;
			
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

				nodalValues[k]=(double)tempNode->elementValue;
			}

			if(tempNode->element=='I')
			{
				i=SearchNodes(tempNode->node1);
				j=SearchNodes(tempNode->node2);
			
				if(i!=-1)
				{
					nodalValues[i]=	(double)tempNode->elementValue;
				}

			
				if(j!=-1)
				{
					nodalValues[j]=	-(double)tempNode->elementValue;
				}	

			}

	
		tempNode=tempNode->link;
		}
	}	

	else
	{	

		nonLinearIndex= (int **) malloc(nodalElements*sizeof(int*));
	
		for(i=0;i<nonLinearData.count;i++)
		{
			nonLinearIndex[i]=(int *) malloc(2*sizeof(int));	
		}

		while(tempNode!=NULL)
		{
			if(tempNode->element=='R')
			{
				i=SearchNodes(tempNode->node1);
				j=SearchNodes(tempNode->node2);
			
				G=(double)1/tempNode->elementValue;
			
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

				nodalValues[k]=(double)tempNode->elementValue;
			}

			if(tempNode->element=='I')
			{
				i=SearchNodes(tempNode->node1);
				j=SearchNodes(tempNode->node2);
			
				if(i!=-1)
				{
					nodalValues[i]=	(double)tempNode->elementValue;
				}

			
				if(j!=-1)
				{
					nodalValues[j]=	-(double)tempNode->elementValue;
				}	

			}

			if(tempNode->element=='D')
			{
				i=SearchNodes(tempNode->node1);
				j=SearchNodes(tempNode->node2);
			
				//G=(double)1/tempNode->elementValue;
			
					nonLinearIndex[nonLinearCount][0]=i;
					nonLinearIndex[nonLinearCount][1]=j;
				nonLinearCount++;
			}

			

	
		tempNode=tempNode->link;
		}
		
		
	printf("\n\n----------------DIODE ELEMENTS--------------------------------------------------");
	for(i=0;i<nonLinearCount;i++)
	{	
		printf("\n");

		for(j=0;j<2;j++)
		{
			printf("%d\t",nonLinearIndex[i][j]);
		}

	}
	printf("\n\n----------------DIODE ELEMENTS--------------------------------------------------");


	
	}	



	printf("\n\n----------------NODAL MATRIX--------------------------------------------------");
	for(i=0;i<nodalElements;i++)
	{	
		printf("\n");

		for(j=0;j<nodalElements;j++)
		{
			printf("%lf\t",nodalMatrix[i][j]);
		}
		printf("%lf\t",nodalValues[i]);
	}
	printf("\n\n----------------NODAL MATRIX--------------------------------------------------");




	if(mode.modeType=='o')
	{	
		if(nonLinearData.nonLinear==0)
		{		
			exist=FindSolution(nodalMatrix,nodalValues,solution,nodalElements);
		}

		else
		{
		
			exist=FindSolutionNonLinear(nodalMatrix,nodalValues,solution,nodalElements,nonLinearIndex,nonLinearData.count);
		}

	
		tempvoltageNode=vNode;
		tempcurNode=cNode;
	
		printf("\n\n----------------SIMULATION RESULTS--------------------------------------------------");
		
		if(exist==0)
		{
			printf("\n\n\nNO SOLUTION \n\n\n");
		}

		else
		{
		
			for(i=0;i<nodalElements;i++)
			{
				if(i<totalNodes)
				{		
					printf("\nV(%d): %lfV\n",tempvoltageNode->nodeNo, solution[i]);
					tempvoltageNode=tempvoltageNode->link;
				}

				else
				{
					printf("\n\nI_%d: %lfA\n",tempcurNode->elementName, solution[i]);
					tempcurNode=tempcurNode->link;
				}
		
					
			}
		}

		printf("\n\n----------------SIMULATION RESULTS--------------------------------------------------");
	}

	if(mode.modeType=='d')
	{
		
		parseResult=SearchVoltageSource(mode.elementNumber)+totalNodes;
		printf("\n\nparse Result : %d\n\n",parseResult);

		if(nonLinearData.nonLinear==0)
		{
			FindSolutionDC(nodalMatrix,nodalValues,solution,nodalElements,parseResult);
		}

		else
		{
			FindSolutionNonLinearDC(nodalMatrix,nodalValues,solution,nodalElements,nonLinearIndex,nonLinearData.count, parseResult);
		}
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

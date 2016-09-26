#include<stdio.h>
#include<stdlib.h>
#include"Simulate.h"

void FindSolutionDC(float **x, float *y, float *sol, int dim, int vPointer)
{
	float a[dim][dim+3],D,m,n,temp,val;
	//float sol[3];
	int i,j,k,t,l;
	
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+1;j++)
		{

			if(j==dim)
			{			
				a[i][j]=y[i];
		
				if(i!=vPointer)
				{
					a[i][j+1]=y[i];
					a[i][j+2]=0;

				}
				
				else
				{
					a[i][j+1]=0;
					a[i][j+2]=1;

				}
				

			}
	
			else
			{
				a[i][j]=x[i][j];
			
			}
				
		}
		printf("\n");	

	}

	for(i=0;i<dim;i++)
	{
		for(j=i+1;j<dim;j++)
		{
			
			m=a[j][i];
			n=a[i][i];
			while(n== 0.0)
				{
					n=a[i+1][i];
	
					for(k=i;k<dim+3;k++)
					{
						a[j][k]=(a[i][k])+(a[j][k]);
						a[i][k]=(a[j][k])-(a[i][k]);
						//printf("\n%d", a[j][k]);
						//getchar();
				
					}
				}

			//if(n== 0.0)
			//n=a[i+1][i]
			//a[i][i]=1.0;
			if(m!= 0.0)
			{
				for(k=i;k<dim+3;k++)
				{

					a[j][k]=(m*a[i][k])-(n*a[j][k]);
					//printf("\n%d", a[j][k]);
					//getchar();

					/*if(k=>dim)
					{
						//a[j][k]=(m*a[i][k])-(n*a[j][k]);
						a[j][k+1]=(m*a[i][k+1])-(n*a[j][k+1]);
						
					}*/
							
				
				}
			}
		}
	}

	printf("\n\n------------------------GAUSSIAN MATRIX--------------------\n\n");
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+3;j++)
		{
			printf("%f\t",a[i][j]);

		}

		printf("\n");
	}
	printf("\n\n------------------------GAUSSIAN MATRIX--------------------");
	
	for(val=mode.startValue;val<mode.stopValue;val=val+mode.stepValue)
	{
		
		printf("\n\n\n");
		
		for(i=dim-1;i>=0;i--)
		{	
			D=0;
	
			//sol[i]=(a[i][t]-D)/(a[i][j]);
			for(j=dim-1,t=j+1;j>i;j--)
			{

				D=D+(a[i][j]*sol[j]);
			}
		
			//printf("\nD : %f",D);
			//printf("Sol \n: %f\n\n",a[i][j]);

			a[i][t]=(a[i][t+1])+(val*a[i][t+2]);
	
			sol[i]=(a[i][t]-D)/(a[i][j]);
			//printf("Sol \n: %f",sol[i]);
			//getchar();
		}

		//printf("\nThe Solutions are :\n");
	
		for(i=0;i<dim;i++)
		{
		
			printf("\n%f",sol[i]);
		}
	}

	
}
	


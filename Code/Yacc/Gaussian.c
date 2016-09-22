#include<stdio.h>
#include<stdlib.h>

void FindSolution(float **x, float *y, float *sol, int dim)
{
	float a[dim][dim+1],D,m,n;
	//float sol[3];
	int i,j,k,t,l;
	
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+1;j++)
		{

			if(j==dim)
			{			
				a[i][j]=y[i];
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
			for(k=i;k<dim+1;k++)
			{

				a[j][k]=(m*a[i][k])-(n*a[j][k]);
				//printf("\n%d", a[j][k]);
				//getchar();
				
			}
		}
	}

	/*for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+1;j++)
		{
			printf("%f\t",a[i][j]);

		}

		printf("\n");
	}*/

	for(i=dim-1;i>=0;i--)
	{	
		D=0;
		for(j=dim-1,t=j+1;j>i;j--)
		{

			D=D+(a[i][j]*sol[j]);
		}
		
		//printf("\nD : %f",D);
		sol[i]=(a[i][t]-D)/(a[i][j]);
		//printf("Sol \n: %f",sol[i]);
		//getchar();
	}

	//printf("\nThe Solutions are :\n");
	
	/*for(i=0;i<dim;i++)
	{
		
		printf("\n%f",sol[i]);
	}*/

	
}
	


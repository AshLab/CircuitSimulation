#include<stdio.h>
#include<stdlib.h>

int FindSolution(double **x, double *y, double *sol, int dim)
{
	double a[dim][dim+1],D,m,n;
	//double sol[3];
	int i,j,k,t,l,z;
	
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
			
			
			n=a[i][i];

			for(z=i;z<dim && n==0.0;z++)
			{
				n=a[i+1][i];
				for(k=i;k<dim+1;k++)
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

			if(n==0.0)
			{
				return 0;
			}
		

			m=a[j][i];
			if(m!= 0.0)
			{
				for(k=i;k<dim+1;k++)
				{

					a[j][k]=(m*a[i][k])-(n*a[j][k]);
					//printf("\n%d", a[j][k]);
					//getchar();
				
				}
			}
		}
	}


	if(a[dim-1][dim-1]==0.0)
	{

		return 0;
	}


	printf("\n\n------------------------GAUSSIAN MATRIX--------------------\n\n");

	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+1;j++)
		{
			printf("%lf\t",a[i][j]);

		}

		printf("\n");
	}
	printf("\n\n------------------------GAUSSIAN MATRIX--------------------\n\n");

	for(i=dim-1;i>=0;i--)
	{	
		D=0;
	
		//sol[i]=(a[i][t]-D)/(a[i][j]);
		for(j=dim-1,t=j+1;j>i;j--)
		{

			D=D+(a[i][j]*sol[j]);
		}
		
		//printf("\nD : %lf",D);
		//printf("Sol \n: %lf\n\n",a[i][j]);
		sol[i]=(a[i][t]-D)/(a[i][j]);
		//printf("Sol \n: %lf",sol[i]);
		//getchar();
	}

	//printf("\nThe Solutions are :\n");
	
	/*for(i=0;i<dim;i++)
	{
		
		printf("\n%lf",sol[i]);
	}*/

	return 1;
	
}
	


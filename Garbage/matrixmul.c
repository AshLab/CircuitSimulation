#include<stdio.h>
#include<stdlib.h>

void main(void)
{
	float c[3][3],a[3][4],b[3][3],sol[3],D;
	int i,j,k,t,l;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{

			//a[i][j]=(3*i)+j+1;
			scanf("%f",&a[i][j]);

			printf("\t");			
			//printf("%f",a[i][j]);
				
		}
		printf("\n");	

	}


	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{

			//a[i][j]=(3*i)+j+1;
			printf("%f",a[i][j]);

			printf("\t");			
			//printf("%f",a[i][j]);
				
		}
		printf("\n");	

	}

	for(i=0;i<3;i++)
	{
		for(j=i+1;j<3;j++)
		{
			for(k=i,t=i;k<4;k++)
			{

				a[j][k]=(a[j][t]*a[i][k])-(a[i][i]*a[j][k]);
				//printf("\n%d", a[j][k]);
				//getchar();
				
			}
		}
	}

	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%f\t",a[i][j]);

		}

		printf("\n");
	}

	for(i=2;i>=0;i--)
	{	
		D=0;
		for(j=2,t=j+1;j>i;j--)
		{

			D=D+(a[i][j]*sol[j]);
		}
		
		//printf("\nD : %f",D);
		sol[i]=(a[i][t]-D)/(a[i][j]);
		//printf("Sol \n: %f",sol[i]);
		//getchar();
	}

	printf("\nThe Solutions are :\n");
	
	for(i=0;i<3;i++)
	{

		printf("\n%f",sol[i]);
	}
}
	


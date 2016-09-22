#include<stdio.h>
#include<stdlib.h>

void main(void)
{
	float c[3][3],a[3][4],b[3][3],sol[3],D, m,n;
	int i,j,k,t,l;
	
	/*for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{

			//a[i][j]=(3*i)+j+1;
			scanf("%f",&a[i][j]);

			printf("\t");			
			//printf("%f",a[i][j]);
				
		}
		printf("\n");	

	}*/

	a[0][0]=1;
	a[0][1]=-1;
	a[0][2]=1;
	a[0][3]=0;

	a[1][0]=-1;
	a[1][1]=2;
	a[1][2]=0;
	a[1][3]=0;
	
	a[2][0]=1;
	a[2][1]=0;
	a[2][2]=0;
	a[2][3]=2;
	


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
			m=a[j][i];
			n=a[i][i];
			for(k=i;k<4;k++)
			{
				//printf("\n\n (%f * %f) - (%f * %f)\n",a[j][i],a[i][k],a[i][i],a[j][k]);
				a[j][k]=(m*a[i][k])-(n*a[j][k]);
				
				//printf("\n%f", a[j][k]);
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
	


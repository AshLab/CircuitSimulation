#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"Simulate.h"
#include"gnuplot_i.h"

void FindSolutionDC(double **x, double *y, double *sol, int dim, int vPointer)
{
	double a[dim][dim+3],D,m,n,temp,val;
	double *plotX, *plotY;
	//double sol[3];
	int i,j,k,t,l,pointCount=0,z;
	char title[]="Test",label1[5],label[5];
	
	gnuplot_ctrl *h1;
	
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
			
			
			n=a[i][i];
			for(z=i;z<dim && n==0.0;z++)
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

			if(n==0.0)
			{
				printf("\n\n\n NO SOLUTION \n\n\n");
				return;
			}
		
			
			 m=a[j][i];
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

	
	if(a[dim-1][dim-1]==0.0)
	{
		printf("\n\n\n NO SOLUTION \n\n\n");
		return;
	}


	printf("\n\n------------------------GAUSSIAN MATRIX--------------------\n\n");
	for(i=0;i<dim;i++)
	{
		for(j=0;j<dim+3;j++)
		{
			printf("%lf\t",a[i][j]);

		}

		printf("\n");
	}
	printf("\n\n------------------------GAUSSIAN MATRIX--------------------");

	pointCount=((double)mode.stopValue-mode.startValue)/((double)mode.stepValue);
	printf("Point COunt :%d\n\n", pointCount);
	plotX=(double*)malloc(pointCount*sizeof(double));
	plotY=(double*)malloc(pointCount*sizeof(double));
	
	for(k=0,val=mode.startValue;val<mode.stopValue;val=val+mode.stepValue,k++)
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
		
			//printf("\nD : %lf",D);
			//printf("Sol \n: %lf\n\n",a[i][j]);

			a[i][t]=(a[i][t+1])+(val*a[i][t+2]);
	
			sol[i]=(a[i][t]-D)/(a[i][j]);
			
			if(plotInfo->colNo==i)
			{
				plotY[k]=sol[i];
			}
			
			//printf("Sol \n: %lf",sol[i]);
			//getchar();
		}

		//printf("\nThe Solutions are :\n");

		plotX[k]=val;
	
		for(i=0;i<dim;i++)
		{
		
			printf("\n%lf",sol[i]);
		}

		printf("\nX: %lf \t Y: %lf\n", plotX[k],plotY[k]);

		
	}
	

	h1 = gnuplot_init();
	gnuplot_resetplot(h1);
	if ( h1 == NULL )
  	{
	    printf ( "\n" );
	    printf ( "EXAMPLE - Fatal error!\n" );
	    printf ( "  GNUPLOT is not available in your path.\n" );
	    //exit ( 1 );
  	}
	gnuplot_setstyle(h1, "lines");

	sprintf(label, "V_%d",mode.elementNumber);	

	gnuplot_set_xlabel (h1, label);
	
	sprintf(label1, "V_%d",plotInfo->nodeNo);	


	
	gnuplot_set_ylabel(h1,label1);
	gnuplot_plot1d_var2v(h1, plotX, plotY, k, "Test Plots");
	//gnuplot_plot_equation(h1, "sin(x)", "sin(x)");
	printf("\nLength : %d",k);

		
	scanf("%d",&k);

	free(plotX);
	free(plotY);
	

}
	


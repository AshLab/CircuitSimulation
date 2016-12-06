#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"Simulate.h"
#include"gnuplot_i.h"

void FindSolutionNonLinearDC(float **x, float *y, float *sol, int dim, int **nlIndex, int nlCount,int vPointer)
{
	float val;
	double *plotX, *plotY;
	//float sol[3];
	int i,j,k,t,l,pointCount=0, exist;
	char title[]="DC Sweep",label1[5],label[5];
	
	int FindSolutionNonLinear(float**, float*, float*, int, int**, int);
	
	
	gnuplot_ctrl *h1;
	
	

	pointCount=((float)mode.stopValue-mode.startValue)/((float)mode.stepValue);
	printf("Point Count :%d\n\n", pointCount);
	plotX=(double*)malloc(pointCount*sizeof(double));
	plotY=(double*)malloc(pointCount*sizeof(double));
	
	for(k=0,val=mode.startValue;val<mode.stopValue;val=val+mode.stepValue,k++)
	{
		

		
		y[vPointer]=val;
	
		exist=FindSolutionNonLinear(x,y,sol,dim,nlIndex,nlCount);
			
		if(exist==0)
		{
			printf("\n\n\n NO SOLUTION \n\n\n");
			return;
		}
			
		printf("\n\n\n");
		
			
			
				plotY[k]=sol[plotInfo->colNo];
						
			//printf("Sol \n: %f",sol[i]);
			//getchar();
		

		//printf("\nThe Solutions are :\n");

		plotX[k]=val;


		printf("\nX: %f \t Y: %f\n", plotX[k],plotY[k]);

		
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
	gnuplot_plot1d_var2v(h1, plotX, plotY, k, "Voltage Sweep");
	//gnuplot_plot_equation(h1, "sin(x)", "sin(x)");
	printf("\nLength : %d",k);

		
	scanf("%d",&k);

	free(plotX);
	free(plotY);
	

}
	


#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void FindSolutionNonLinear(float **x, float *y, float *sol, int dim, int **nlIndex, int nlCount)

{
	float a[dim][dim+1],D,m,n;
	float mJnl[dim][dim],**J, Inl[dim], Itot[dim];
	float konst,gm,id,temp,Vt;

	//float sol[3];
	int i,j,k,t,l,Iteration,itNo;


	void FindSolution(float**,float*,float*,int);

	Vt=2*25.3*pow(10,-3);
	konst=pow(10,-6);

	J= (float **) malloc(dim*sizeof(float*));
	
	for(i=0;i<dim;i++)
	{
		J[i]=(float *) malloc(dim*sizeof(float));	
	}


	//Setting up Intial Values for sol, hoping that the solution will converge

	for(i=0;i<dim;i++)
	{
		sol[i]=1;
	}

	Iteration=10;	

	for(itNo=0;itNo<Iteration;itNo++)
	{
	
	//Clearing up Matrices

		for(i=0;i<dim;i++)
		{
	
			Inl[i]=0;
			Itot[i]=y[i];
			
			for(j=0;j<dim;j++)
			{
				mJnl[i][j]=0;
				J[i][j]=x[i][j];
			}		
			
		}

	


		//Filling up Negative Jacobian Matrix and Non Linear Current
		for(i=0;i<nlCount;i++)
		{
			t=nlIndex[i][0];
			l=nlIndex[i][1];

			gm=(konst/(Vt))*(expf((sol[t]-sol[l])/(Vt)));
		
			mJnl[t][t]=gm+mJnl[t][t];
			J[t][t]=x[t][t]+mJnl[t][t];

			mJnl[l][l]=gm+mJnl[l][l];
			J[l][l]=x[l][l]+mJnl[l][l];
		
			mJnl[t][l]=-gm+mJnl[t][l];
			J[t][l]=x[t][l]+mJnl[t][l];

			mJnl[l][t]=-gm+mJnl[l][t];
			J[l][t]=x[l][t]+mJnl[l][t];

			id=konst*((expf((sol[t]-sol[l])/(Vt)))-1);
			Inl[t]=-id+Inl[t];
			Itot[t]=y[t]+Inl[t];

			Inl[l]=id+Inl[l];
			Itot[l]=y[l]+Inl[l];
		}

	
		printf("\n\n\n-----------------J---------------------\n");

		for(i=0;i<dim;i++)
		{
			
		
			for(j=0;j<dim;j++)
			{
				printf("\t%f",J[i][j]);
			}
		
			printf("\n");
		}



		printf("\n\n\n-----------------mJnl ---------------------\n");

		for(i=0;i<dim;i++)
		{
			
		
			for(j=0;j<dim;j++)
			{
				printf("\t%f",mJnl[i][j]);
			}
		
			printf("\n");
		}

		

		printf("\n\n\n-----------------Inl ---------------------");

		for(i=0;i<dim;i++)
		{
	
			
			printf("\n%f",Inl[i]);
			
	
		}			


		printf("\n\n\n-----------------I Total ---------------------");

		for(i=0;i<dim;i++)
		{
	
			
			printf("\n%f",Itot[i]);
			
	
		}	


		//Calculating RHS - equivalent current

		for(i=0;i<dim;i++)
		{
			temp=0;
		
			for(j=0;j<dim;j++)
			{
				temp=(mJnl[i][j]*sol[j])+temp;
			}
		
			Itot[i]=Itot[i]+temp;
		}

	//printing for Debugging

		printf("\n\n\n--------------------RHS ---------------------");

		for(i=0;i<dim;i++)
		{
	
			
			printf("\n%f",Itot[i]);
			
	
		}	

			
		FindSolution(J,Itot,sol,dim);

		
		printf("\n\n\n--------------------SOLUTION ---------------------");

		for(i=0;i<dim;i++)
		{
	
			
			printf("\n%f",sol[i]);
			
	
		}	

	
	}
		
}
	


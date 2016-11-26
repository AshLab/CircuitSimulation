#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void FindSolutionNonLinear(float **x, float *y, float *sol, int dim, int **nlIndex, int nlCount)

{
	float a[dim][dim+1],D,m,n,V1,V2;
	float mJnl[dim][dim],**J, Inl[dim], Itot[dim],sol_pre[dim];
	float konst,gm,id,temp,Vt, convergenceValue=0.001;

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
		sol_pre[i]=0;
	}

	Iteration=100;	

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
			
			V1=0;
			V2=0;
		
			t=nlIndex[i][0];
			l=nlIndex[i][1];
		
			if(t!=-1)
			{
				V1=sol[t];
			}

			if(l!=-1)
			{
				V2=sol[l];
			}
					

			gm=(konst/(Vt))*(expf((V1-V2)/(Vt)));
			id=konst*((expf((V1-V2)/(Vt)))-1);
		
			if(t!=-1)
			{			
				mJnl[t][t]=gm+mJnl[t][t];
				J[t][t]=x[t][t]+mJnl[t][t];
			
				Inl[t]=-id+Inl[t];
				Itot[t]=y[t]+Inl[t];

			}

			if(l!=-1)
			{

				mJnl[l][l]=gm+mJnl[l][l];
				J[l][l]=x[l][l]+mJnl[l][l];

				Inl[l]=id+Inl[l];
				Itot[l]=y[l]+Inl[l];
			}

			if(t!=-1&&l!=-1)
			{
		
				mJnl[t][l]=-gm+mJnl[t][l];
				J[t][l]=x[t][l]+mJnl[t][l];

				mJnl[l][t]=-gm+mJnl[l][t];
				J[l][t]=x[l][t]+mJnl[l][t];
			}

			
			
			
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

		temp=0;

		for(i=0;i<dim;i++)
		{
	
			temp=pow((sol_pre[i]-sol[i]),2)+temp;
			printf("\n%f",sol[i]);
			
	
		}

		temp=pow(temp,0.5);
		
		printf("\n\n Convergence Value:%f\n\n", temp);

		if(temp<convergenceValue)
		{
			printf("\n\n Solution Converged at %dth iteration\n\n",itNo);
			break;
		}

				

		printf("\n\n\n--------------------SOLUTION ---------------------");

		for(i=0;i<dim;i++)
		{
	
			sol_pre[i]=sol[i];
			printf("\n%f",sol[i]);
			
	
		}	

		

	
	}

	if(itNo>=Iteration)
	{
			printf("\n\n\nSOLUTION FAILED TO CONVERGE\n\n\n");
	}
		
}
	


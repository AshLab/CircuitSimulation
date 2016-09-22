#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void main(void)
{

int **nodalMatrix,i;

nodalMatrix=(int **) malloc(2*sizeof(int*));
for(i=0;i<2;i++)
{
	nodalMatrix[i]= (int *) malloc(2*sizeof(int));
}

nodalMatrix[1][1]=56;

printf("%d", nodalMatrix[1][1]);

}

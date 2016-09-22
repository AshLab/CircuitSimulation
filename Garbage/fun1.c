#include<stdio.h>
#include"Simulate.h"


struct elementData *parsedNode;
void modify(void);

void main(void)
{
	modify();
	printf("\n%d %d %d",parsedNode->node1,parsedNode->node2,parsedNode->elementNumber);;
	
}

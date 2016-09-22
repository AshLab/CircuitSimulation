struct elementData 
{
	int node1, node2, elementNumber;
        int elementValue;
	char element;
	struct elementData *link;
};

extern struct elementData *parsedNode;

struct voltageNode
{
	int nodeNo;
	struct voltageNode *link;
};

extern struct voltageNode *vNode;

struct currentNode
{
	int elementName;
	struct currentNode *link;
};

extern struct currentNode *cNode;

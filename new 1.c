int insert_bin(TLDList *tld, char *hostname, Date *d, TLDNode *node)
{    
    if(compareResult != 0){
		if(compareResult <0){
			if(node->leftChild != NULL)
				insert_bin(tld,hostname,d,node->leftChild);
			else{
				TLDNode *newNode = (TLDNode *)malloc(sizeof(TLDNode));
				newNode->parrent = node;
				
				NodeEntry *entry = (NodeEntry *)malloc(sizeof(NodeEntry));
				entry->tldString = hostname;
				entry->tldCount = 1;
				
				newNode->nodeEntry = entry;
				newNode->leftChild = NULL;
				newNode->rightChild = NULL;
				
				node->leftChild = newNode;
				tld->listSize +=1;
				tld->success_add +=1;
			}
		}else{
			if(node->rightChild	 != NULL)
				insert_bin(tld,hostname,d,node->rightChild);
			else{
				TLDNode *newNode = (TLDNode *)malloc(sizeof(TLDNode));
				newNode->parrent = node;
				
				NodeEntry *entry = (NodeEntry *)malloc(sizeof(NodeEntry));
				entry->tldString = hostname;
				entry->tldCount = 1;
				
				newNode->nodeEntry = entry;
				newNode->leftChild = NULL;
				newNode->rightChild = NULL;
				
				node->rightChild = newNode;
				tld->listSize +=1;
				tld->success_add +=1;
			}
		}   		
    else{
    	node->nodeEntry->tldCount += 1;
    	tld->success_add +=1;
		return 1;    		
    }

}
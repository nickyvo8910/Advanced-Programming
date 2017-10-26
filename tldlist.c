#include "date.h"
#include <string.h>
#define MAX_TLD_STRINGLENGTH 30

typedef struct tldNodeEntry
{
    char *tldString;
    long tldCount;
} NodeEntry;

typedef struct tldnode
{
    struct tldnode *parrent;
    NodeEntry *nodeEntry;
    struct tldnode *leftChild;
    struct tldnode *rightChild;
} TLDNode;

typedef struct tldlist
{
    Date *beginDate;
    Date *endDate;
    TLDNode *root;
    long listSize;
    long success_add;
} TLDList;

typedef struct tlditerator
{
    TLDNode *nodes; //list of Nodes
    unsigned long i;
    unsigned long next;
    unsigned long sizeOfArray;
} TLDIterator;

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end)
{
    TLDList *t = (TLDList *)malloc(sizeof(TLDList));

    t->beginDate = begin;
    t->endDate = end;
    t->root = NULL;
    t->listSize =0;
    t->success_add=0;

    return t;
}

/*
 * tldlist_destroy destroys the list structure in `tld'
 *
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld)
{
    free(tld->beginDate);
    free(tld->endDate);
    free(tld->root);
    free(tld);
}


int insert_bin(TLDList *tld, char *hostname, Date *d, TLDNode *node)
{
    /*no need to check date
    compare string with the ROOTNODE
    key = Node->entry->tldString
    if string != Node->entry->tldString
    	if string < KEY
    		if ROOTNODE has left
    		insert to left
    	else
    		ROOTNODE -> left = NEWNODE
    		LIST size ++;
    		LIST add ++;
    	if string >KEY
    		if ROOT has right
    			insert right
    		else
    			ROOTNODE -> right = NEWNODE
    			LIST size ++;
    			LIST add ++;
    	 Node -> entry ->count ++;
		LIST add ++;
		*/
    char keyStr[MAX_TLD_STRINGLENGTH];
    strcpy(keyStr, node->nodeEntry->tldString);

    int compareResult = strcmp(keyStr, hostname);
    
    if(compareResult != 0){
    	//if string < KEY
		if(compareResult <0){
			if(node->leftChild != NULL)
				insert_bin(tld,hostname,d,node->leftChild);
			else{
				TLDNode *newNode = (TLDNode *)malloc(sizeof(TLDNode));
				newNode->parrent = node;
				
				NodeEntry *entry = (NodeEntry *)malloc(sizeof(NodeEntry));
			//	entry->tldString = (char *)malloc(sizeof(MAX_TLD_STRINGLENGTH));
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
	}	
	else{
			node->nodeEntry->tldCount += 1;
    	tld->success_add +=1;
		return 1;  
		}
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d)
{
    //check the date
    int dateChk = date_compare(tld->beginDate,d)*date_compare(tld->endDate,d);
    if(dateChk <0 || dateChk ==0) // if date is in range
    {
		//refine hostname
		char *newHost = strrchr(hostname,'.');  //last occurrence 
		
		if(newHost !=NULL){						// valid hostname
			newHost +=1; 						// move forwards
			
			//use *newHost instead of hostname from now on
			if (tld->listSize == 0 )   // insert first node
			{

				TLDNode *newNode = (TLDNode *) malloc(sizeof(TLDNode));
				newNode->parrent = NULL;

				NodeEntry *entry = (NodeEntry *)malloc(sizeof(NodeEntry));
				entry->tldString = newHost;
				entry->tldCount =1;

				newNode->nodeEntry = entry;
				newNode->leftChild =NULL;
				newNode->rightChild =NULL;
				tld->root = newNode;
				tld->listSize = 1;
				tld->success_add =1;
				return 1;
			}
			else return insert_bin(tld, newHost,d,tld->root);   // insert leaf node
		}else return 0; // invalid hostname
	}
    else return 0; // out of date range
}


/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld)
{
    return (tld->success_add);
}


void travese(TLDNode *node,TLDIterator *it){
	if(node != NULL){
		it->nodes[it->i++] = *node;
		printf("\n");
		printf("Crr Node: %s",node->nodeEntry->tldString);
		printf("\n");
		if(node->leftChild !=NULL){
			travese(node->leftChild, it);
		}
		if(node->rightChild	 !=NULL){
			travese(node->rightChild, it);
		}
	}
	
	return;
}
/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){
	
	TLDIterator *it = malloc(sizeof(TLDIterator));

	if (it != NULL && tld != NULL) {
		it->sizeOfArray = tld->listSize;
		it->next = 0;
		it->i =0;		
		it->nodes = malloc(sizeof(TLDNode)*(tld->listSize));
		travese(tld->root, it);
	}else{
		it =NULL;
	}
	return it;
}

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){
	TLDNode *crrNode;
	if(iter->next < iter->sizeOfArray){
		crrNode = &(iter->nodes[iter->next ++]);
		return crrNode;
	}else return NULL;
}

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
	free(iter->nodes);
	free(iter);
}

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node)
{
	//Look for node
    return (node->nodeEntry->tldString);
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node)
{
	//Look for node
    return (node->nodeEntry->tldCount);
}
/*
void main(int argc, char *argv[]){
	Date *fromDate = NULL;
 	fromDate = date_create("20/10/2017");
 	
	Date *toDate = NULL;
 	toDate = date_create("25/10/2017");
 	
 	//test Listcreate
 	printf("\n***Test listCreate ***\n");
	TLDList *t = tldlist_create(fromDate,toDate);
	printf("Begin Date: ");
	printf(date_to_string(t->beginDate));
	printf("\n");
	printf("End Date: ");
	printf(date_to_string(t->endDate));
	printf("\n");
	printf("Root is NULL: %d", ((t->root == NULL)? 1 :0));
	printf("\n");
  	printf("List Size: %d",t->listSize);
  	printf("\n");
  	printf("List Added: %d",t->success_add);	
  	printf("\n");
  	
  	

  	//test ListDestroy
  	printf("\n***Test listDestroy ***\n");
	tldlist_destroy(t);
	printf("Begin Date: ");
	printf(date_to_string(t->beginDate));
	printf("\n");
	printf("End Date: ");
	printf(date_to_string(t->endDate));
	printf("\n");
	printf("Root is NOT NULL: %d", ((t->root != NULL)? 1 :0));
	printf("\n");
  	printf("List Size: %d",t->listSize);
  	printf("\n");
  	printf("List Added: %d",t->success_add);	
  	printf("\n");
  	
  	//test listAdd
  	printf("\n***Test listAdd ***\n");
  	
	tldlist_add(t,"www.sdfsdf.edu",date_create("22/10/2017"));
	tldlist_add(t,"www.asdasf.gm",date_create("22/10/2017"));
	tldlist_add(t,"www.fsafas.la",date_create("22/10/2017"));
	tldlist_add(t,"qq.aa.asd.pn",date_create("22/10/2017"));
	tldlist_add(t,"www.sadasd.uk",date_create("22/10/2017"));
	tldlist_add(t,"www.asfas.uk",date_create("22/10/2017"));	
	tldlist_add(t,"www.dsfsd.uk",date_create("22/10/2017"));
	tldlist_add(t,"www.wweq.uk",date_create("22/10/2017"));
	tldlist_add(t,"www.asd.uk",date_create("22/10/2017"));

	
	
	printf("Begin Date: ");
	printf(date_to_string(t->beginDate));
	printf("\n");
	printf("End Date: ");
	printf(date_to_string(t->endDate));
	printf("\n");
	printf("Root is NULL: %d", ((t->root != NULL)? 1 :0));
	printf("\n");
  	printf("List Size: %d",t->listSize);
  	printf("\n");
  	printf("List Added: %d",t->success_add);	
  	printf("\n");
  	
  	//test listCount
  	printf("\n***Test listCount ***\n");
  	printf("List Count: %d",tldlist_count(t));
  	printf("\n");
  	
  	//test Iter Create
  	printf("\n***Test Iter Create ***\n");
  	TLDIterator *it = tldlist_iter_create(t);
  	printf("Iter is not NULL: %d", ((it != NULL)? 1 :0));
  	printf("\n");
	printf("Crr Index: %d",it->i);
  	printf("\n");
  	printf("Crr Next: %d",it->next);	
  	printf("\n");
  	printf("Size: %d",it->sizeOfArray);
  	printf("\n");
  	printf("Last Entry: %s", it->nodes->nodeEntry->tldString);
  	printf("\n");
  	
  	//test Iter Next
  	printf("\n***Test Iter Next ***\n");
  	TLDNode *nextNode = tldlist_iter_next(it);
  	printf("Iter is not NULL: %d", ((it != NULL)? 1 :0));
  	printf("\n");
	printf("Crr Index: %d",it->i);
  	printf("\n");
  	printf("Crr Next: %d",it->next);	
  	printf("\n");
  	printf("Size: %d",it->sizeOfArray);
  	printf("\n");
  	printf("Next Node: %s",nextNode->nodeEntry->tldString);
  	printf("\n");
  	
  	//test Iter Next
  	printf("\n***Test Iter Next ***\n");
  	TLDNode *next2Node = tldlist_iter_next(it);
  	printf("Iter is not NULL: %d", ((it != NULL)? 1 :0));
  	printf("\n");
	printf("Crr Index: %d",it->i);
  	printf("\n");
  	printf("Crr Next: %d",it->next);	
  	printf("\n");
  	printf("Size: %d",it->sizeOfArray);
  	printf("\n");
	printf("Next 2 Node: %s",nextNode->nodeEntry->tldString);
  	printf("\n");
  	

}*/
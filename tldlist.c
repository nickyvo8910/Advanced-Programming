#include "date.h"
#define MAX_TLD_STRINGLENGTH = 30

typedef struct tldNodeEntry{
	char *tldString;
	long tldCount;
}NodeEntry;

typedef struct tldnode{
	struct tldnode *parrent;
	NodeEntry *nodeEntry;
	struct tldnode *leftChild;
	struct tldnode *rightChild;
}TLDNode;

typedef struct tldlist {
	Date *beginDate;
	Date *endDate;
	TLDNode *root;
	long listSize;
	long success_add;	
}TLDList;

typedef struct tlditerator {
	TLDNode *node;
	int i;
	int next;
	int sizeOfArray;
}TLDIterator;

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */
TLDList *tldlist_create(Date *begin, Date *end){
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
void tldlist_destroy(TLDList *tld){
	free(tld->beginDate);
	free(tld->endDate);
	free(tld->root);
	free(tld);
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d){
	//check d
	//add to tree
	int dateChk = date_compare(tld->beginDate,d)*date_compare(tld->endDate,d);
	if(!dateChk >0){// if date is in range
		if (tld->listSize == 0 ) { // insert first node
		
			TLDNode *newNode = (TLDNode *) malloc(sizeof(TLDNode));
			newNode->parrent =NULL;
			
			NodeEntry *entry = (NodeEntry *)malloc(sizeof(NodeEntry));
			entry->tldString =hostname;
			entry->tldCount =1;
			
			newNode->nodeEntry = entry;
			newNode->leftChild =NULL;
			newNode->rightChild =NULL;
			tld->root = newNode;
			tld->listSize = 1;
			tld->success_add =1;
	return 1;
		} else return insert_bin(tld, hostname,d,tld->root); // insert leaf node
	}else{
		return 0; // out of date range
	}
	
}

int insert_bin(TLDList *tld, char *hostname, Date *d, TLDNode *node){
	//no need to check date
	//compare string with the ROOTNODE
		//key = Node->entry->tldString 
		//if string != Node->entry->tldString
			//if string < KEY
				//if ROOTNODE has left
					//insert to left
				//else
					//ROOTNODE -> left = NEWNODE
					//LIST size ++;
					//LIST add ++;
			//if string >KEY
				//if ROOT has right
					//insert right
				//else
					//ROOTNODE -> right = NEWNODE
					//LIST size ++;
					//LIST add ++;
		// Node -> entry ->count ++; 
						////LIST add ++;
	char *keyString = (char*)malloc(sizeof(MAX_TLD_STRINGLENGTH));
	keyString = node->nodeEntry->tldString;
	
	int compareResult = strcmp(hostname, keyString);
	
}

/*
 * tldlist_count returns the number of successful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
	return (tld->success_add);
}

/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld);

/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter);

/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter);

/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node){
	//Look for Node
	//return (node->nodeEntry->tldString);
}

/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node){
	//Look for Node
	//return (node->nodeEntry->tldCount);
}


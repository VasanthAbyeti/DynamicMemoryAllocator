#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct freeNode
{
	int addrs;
	int size;

	struct freeNode* leftAddrChild;
	struct freeNode* rightAddrChild;

	struct freeNode* leftSizeChild;
	struct freeNode* rightSizeChild;
};

static struct freeNode* root;
static int insertSuccessfull = 0;
static int firstEntry = 0;

void insert(int, int);

void deleteChild(struct freeNode* node, char side[])
{
	struct freeNode* delNode;
	struct freeNode* placeFinder;

	if (side == "Left")
	{
		delNode = node->leftAddrChild;
	}
	else
	{
		delNode = node->rightAddrChild;
	}

	if (delNode->leftAddrChild == 0 || delNode->rightAddrChild == 0)
	{
		if (delNode->leftAddrChild == 0)
		{
			if (side == "Left")
				node->leftAddrChild = delNode->rightAddrChild;
			else
				node->rightAddrChild = delNode->rightAddrChild;
		}
		else
		{
			if (side == "Left")
				node->leftAddrChild = delNode->leftAddrChild;
			else
				node->rightAddrChild = delNode->leftAddrChild;
		}
	}
	else
	{
		struct freeNode* temp = delNode->leftAddrChild;

		if (side == "Left")
		{
			node->leftAddrChild = delNode->rightAddrChild;
			placeFinder = node->leftAddrChild;
		}
		else
		{
			node->rightAddrChild = delNode->rightAddrChild;
			placeFinder = node->rightAddrChild;
		}


		while (placeFinder->leftAddrChild != 0)
			placeFinder = placeFinder->leftAddrChild;

		placeFinder->leftAddrChild = temp;
	}

	struct freeNode* sizeDelNode = root->rightSizeChild;
	struct freeNode* sizeParentNode = root;

	int i = 0;
	while (sizeDelNode->addrs != delNode->addrs)
	{
		i++;
		if (sizeDelNode->size>delNode->size)
		{
			sizeParentNode = sizeDelNode;
			sizeDelNode = sizeDelNode->leftSizeChild;
			side = "Left";
		}
		else
		{
			sizeParentNode = sizeDelNode;
			sizeDelNode = sizeDelNode->rightSizeChild;
			side = "Right";
		}
	}

	if (i == 0)
		side = "Right";

	if (side == "Left")
	{
		delNode = node->leftSizeChild;
	}
	else
	{
		delNode = node->rightSizeChild;
	}


	if (sizeDelNode->leftSizeChild == 0 || sizeDelNode->rightSizeChild == 0)
	{
		if (sizeDelNode->leftSizeChild == 0)
		{
			if (side == "Left")
				sizeParentNode->leftSizeChild = sizeDelNode->rightSizeChild;
			else
				sizeParentNode->rightSizeChild = sizeDelNode->rightSizeChild;
		}
		else
		{
			if (side == "Left")
				sizeParentNode->leftSizeChild = sizeDelNode->leftSizeChild;
			else
				sizeParentNode->rightSizeChild = sizeDelNode->leftSizeChild;
		}
	}
	else
	{
		struct freeNode* sTemp = sizeDelNode->leftSizeChild;

		if (side == "Left")
		{
			sizeParentNode->leftSizeChild = sizeDelNode->rightSizeChild;
			placeFinder = sizeParentNode->leftSizeChild;
		}
		else
		{
			sizeParentNode->rightSizeChild = sizeDelNode->rightSizeChild;
			placeFinder = sizeParentNode->rightSizeChild;
		}

		while (placeFinder->leftSizeChild != 0)
			placeFinder = placeFinder->leftSizeChild;

		placeFinder->leftSizeChild = sTemp;
	}


}

void deleteAddrsChild(struct freeNode* node, char side[])
{
		struct freeNode* delNode;
	struct freeNode* placeFinder;

	if (side == "Left")
	{
		delNode = node->leftAddrChild;
	}
	else
	{
		delNode = node->rightAddrChild;
	}

	if (delNode->leftAddrChild == 0 || delNode->rightAddrChild == 0)
	{
		if (delNode->leftAddrChild == 0)
		{
			if (side == "Left")
				node->leftAddrChild = delNode->rightAddrChild;
			else
				node->rightAddrChild = delNode->rightAddrChild;
		}
		else
		{
			if (side == "Left")
				node->leftAddrChild = delNode->leftAddrChild;
			else
				node->rightAddrChild = delNode->leftAddrChild;
		}
	}
	else
	{
		struct freeNode* temp = delNode->leftAddrChild;

		if (side == "Left")
		{
			node->leftAddrChild = delNode->rightAddrChild;
			placeFinder = node->leftAddrChild;
		}
		else
		{
			node->rightAddrChild = delNode->rightAddrChild;
			placeFinder = node->rightAddrChild;
		}


		while (placeFinder->leftAddrChild != 0)
			placeFinder = placeFinder->leftAddrChild;

		placeFinder->leftAddrChild = temp;
	}

}

void deleteWithAddrs(struct freeNode* rootNode,int delAddrs)
{
    if(rootNode->addrs!=0000)
    {
	if(delAddrs<rootNode->addrs)
	{if(rootNode->leftAddrChild!=0)
		{
		if(rootNode->leftAddrChild->addrs==delAddrs)
			deleteAddrsChild(rootNode,"Left");
		else
			deleteWithAddrs(rootNode->leftAddrChild,delAddrs);
		}
	}
	else
	{ if(rootNode->rightAddrChild!=0)
		{
		if(rootNode->rightAddrChild->addrs==delAddrs)
			deleteAddrsChild(rootNode,"Right");
		else
			deleteWithAddrs(rootNode->rightAddrChild,delAddrs);
		}
	}
    }
    else
    {
        if(rootNode->leftAddrChild->addrs==delAddrs)
        {
         deleteAddrsChild(rootNode,"Left");   
        }
        else
        {
         deleteWithAddrs(rootNode->leftAddrChild,delAddrs);
        }
    }
			
}

void deleteSizeChild(struct freeNode* node, char side[])
{
	if(strcmp(side,"Right")==0)
	{
		struct freeNode* delNode = node->rightSizeChild;
		node->rightSizeChild=delNode->rightSizeChild;
		if(delNode->leftSizeChild!=0)
		{
			struct freeNode* temp = delNode->leftSizeChild;
			struct freeNode* placeFinder = node->rightSizeChild;
			
			if(placeFinder!=0)
			{
			while(placeFinder->leftSizeChild!=0)
				placeFinder=placeFinder->leftSizeChild;
			
			placeFinder->leftSizeChild=temp;
			}
			else
			{
			  node->rightSizeChild=temp;	
			}
		}
	}
	else
	{
		struct freeNode* delNode = node->leftSizeChild;
		node->leftSizeChild=delNode->rightSizeChild;
		if(delNode->leftSizeChild!=0)
		{
			struct freeNode* temp = delNode->leftSizeChild;
			struct freeNode* placeFinder = node->rightSizeChild;
			while(placeFinder->leftSizeChild!=0)
				placeFinder=placeFinder->leftSizeChild;
			
			placeFinder->leftSizeChild=temp;
		}
	}
}

void updateMetaData(int returnAddrs, int newSize)
{
	    int* returnMetaData = ((void *)(intptr_t)returnAddrs)-2;
	    returnMetaData[0]= newSize;
	    returnMetaData[1]=0;
}

int splitDeleteInsert(struct freeNode* Node, char side[], int demSize)
{
    int returnAddrs=0;
	if(strcmp(side,"Right")==0)
	{		
	    int estimate = (int)((float) Node->rightSizeChild->size/2.0);
	    
	    if(estimate>demSize)
	    {
	       struct freeNode* newNode =(void*)(intptr_t)brk(sizeof(struct freeNode));
	       if((int)((float)Node->rightSizeChild->size/4.0)>demSize)
	       {
	         newNode->size = (int) (((float)Node->rightSizeChild->size)*3.0/4.0);
	         
	         newNode->addrs= (int)(Node->rightSizeChild->addrs+ (int)((float)Node->rightSizeChild->size/4.0));
			 updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
	         returnAddrs = Node->rightSizeChild->addrs;
	       }
	       else
	       {
	         	newNode->size = (int) ((float)Node->rightSizeChild->size/2.0);
	         	newNode->addrs=Node->rightSizeChild->addrs+ (int) ((float)Node->rightSizeChild->size/2.0);
			
			 returnAddrs = Node->rightSizeChild->addrs;
			 updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
	       }
	       	 deleteWithAddrs(root,Node->rightSizeChild->addrs);
			 deleteSizeChild(Node,"Right");
			 insert(newNode->addrs,(newNode->size-8));
			
			 //updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
			 return returnAddrs;
	    }
	    else
	    {
	        struct freeNode* newNode = (void*)(intptr_t)brk(sizeof(struct freeNode));
	        int estimate1 = (int)(((float)Node->rightSizeChild->size) * (3.0/4.0));

	        if(estimate1>demSize)
	       {
		     returnAddrs = Node->rightSizeChild->addrs;
	         newNode->size = (int) (((float)Node->rightSizeChild->size)/4.0);
	         newNode->addrs=Node->rightSizeChild->addrs+ (int) (((float)Node->rightSizeChild->size/4.0)*3.0);
	         deleteWithAddrs(root,Node->rightSizeChild->addrs);
			 deleteSizeChild(Node,"Right");
			 insert(newNode->addrs,(newNode->size-8));  
			 updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
			 
			 return returnAddrs;
	       }
	       else
	       {
	         int returnAddrs = Node->rightSizeChild->addrs;
	         deleteWithAddrs(root,Node->rightSizeChild->addrs);
			 deleteSizeChild(Node,"Right");

			 return returnAddrs;
	       }
	        
	    }
	}
	else
	{
	    struct freeNode* newNode = (void*)(intptr_t)brk(sizeof(struct freeNode));
	    int estimate = (int) ((float)Node->leftSizeChild->size/2.0);
	    if(estimate>demSize)
	    {
	       if((int)((float)Node->leftSizeChild->size/4.0)>demSize)
	       {
	         newNode->size = (int)((float)Node->leftSizeChild->size/4.0)*3.0;
	         newNode->addrs=Node->leftSizeChild->addrs+(int)((float)Node->rightSizeChild->size/4.0);
		
	         returnAddrs = Node->leftSizeChild->addrs; 
             updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
	       }
	       else
	       {
		 returnAddrs = Node->leftSizeChild->addrs;
	         newNode->size = (int)((float)Node->leftSizeChild->size/2.0);
	         newNode->addrs=Node->leftSizeChild->addrs+(int)((float)Node->leftSizeChild->size/2.0);
                 updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));

	       }
	       	 deleteWithAddrs(root,Node->leftSizeChild->addrs);
			 deleteSizeChild(Node,"Left");
			 insert(newNode->addrs,(newNode->size-8));
		
			
			 return returnAddrs;
	    }
	    else
	    {
	        int estimate1 = (int) ((float)Node->leftSizeChild->size)*(3.0/4.0);
	        if(estimate1>demSize)
	       {
	        returnAddrs = Node->leftSizeChild->addrs;
		     newNode->size = (int) (((float) Node->leftSizeChild->size)/4.0);
	         newNode->addrs=Node->leftSizeChild->addrs+(int) (((float)Node->leftSizeChild->size/4.0)*3.0);
	         deleteWithAddrs(root,Node->leftSizeChild->addrs);
			 deleteSizeChild(Node,"Left");
			 insert(newNode->addrs,(newNode->size-8));
		
		    updateMetaData(returnAddrs,(newNode->addrs-returnAddrs));
			return returnAddrs;
	       }
	       else
	       {
	         returnAddrs = Node->leftSizeChild->addrs;
	         deleteWithAddrs(root,Node->leftSizeChild->addrs);
			 deleteSizeChild(Node,"Left");
		
			 return returnAddrs;
	       }
	    }
	}
}


int findAndFreeMemory(struct freeNode* rootNode, int demandSize)
{
	if(demandSize>rootNode->size)
	{
	   
		if(rootNode->rightSizeChild!=0)
		{
			if(rootNode->rightSizeChild->size==demandSize)
			{
				int deliveryAddress = rootNode->rightSizeChild->addrs;
				deleteWithAddrs(root,rootNode->rightSizeChild->addrs);
				deleteSizeChild(rootNode,"Right");
				return deliveryAddress;
			}
			else
			{
				int x=9;
				if(rootNode->rightSizeChild!=0)
				x=findAndFreeMemory(rootNode->rightSizeChild,demandSize);

				if(x==9)
				{
				 x = 9;
				}
				if(x==0)
				{
				 x = splitDeleteInsert(rootNode,"Right",demandSize);
				}
				return x;
			}
		}
		else
		{
			return 9;
		}
	}
	else
	{
		if(rootNode->leftSizeChild!=0)
		{
			if(rootNode->leftSizeChild->size==demandSize)
			{
				int deliveryAddress = rootNode->leftSizeChild->addrs;
				deleteWithAddrs(root,rootNode->leftSizeChild->addrs);
				deleteSizeChild(rootNode,"Left");
				return deliveryAddress;
			}
			else 
			{
				int x = findAndFreeMemory(rootNode->leftSizeChild,demandSize);
				
				if(x==9)
				{
				 return 0;
				}
				
				if(x==0)
				{
				    if(demandSize<rootNode->size)
				    return 0;
				    else
				    {x = splitDeleteInsert(rootNode,"Right",demandSize);}
				}
				return x;
			}
		}
		else
		{
			return 0;
		}
	}
}




void insertSize(struct freeNode* rootNode, struct freeNode* newNode)
{
        if (rootNode->size > newNode->size)
        {
                if (rootNode->leftSizeChild == 0)
                {
                        rootNode->leftSizeChild = newNode;
                }
                else
                {
                        insertSize(rootNode->leftSizeChild, newNode);
                }
        }
        else
        {
                if (rootNode->rightSizeChild == 0)
                {
                        rootNode->rightSizeChild = newNode;
                }
                else
                {
                        insertSize(rootNode->rightSizeChild, newNode);
                }
        }
}



int checkSizeBST(struct freeNode* parentNode, int block_addrs)
{   char s[]="Left";
    int found =0;
    struct freeNode* mainNode; 
    int search = 0;
    if(parentNode->leftSizeChild!=0)
    {
        if(parentNode->leftSizeChild->addrs==block_addrs)
        {
         found++;
         strcpy(s, "Left");
         mainNode=parentNode->leftSizeChild;
        }
	else
	{
	  search = checkSizeBST(parentNode->leftSizeChild,block_addrs);
	  if(search!=0)
		found==0;
	}
    }
    
    if(parentNode->rightSizeChild!=0 && found==0 )
    {
        if(parentNode->rightSizeChild->addrs==block_addrs)
        {
         found++;
         strcpy(s, "Right");
         mainNode=parentNode->rightSizeChild;
        }
	else
	{
	 search = checkSizeBST(parentNode->rightSizeChild,block_addrs);
	}
    }
    
    if(found!=0)
    {
    if(mainNode->rightSizeChild!=0)
    {
        if(mainNode->size>mainNode->rightSizeChild->size)
        {
            if(strcmp(s,"Left")==0)
            {
                parentNode->leftSizeChild=mainNode->rightSizeChild;
                struct freeNode* temp = mainNode->leftSizeChild;
                struct freeNode* placeFinder = parentNode->leftSizeChild;
		
                while(placeFinder->leftSizeChild!=0)
                    placeFinder=placeFinder->leftSizeChild;
                
                placeFinder->leftSizeChild=temp;
                mainNode->leftSizeChild=0;
                mainNode->rightSizeChild=0;

		insertSize(root->rightSizeChild, mainNode);
            }
            else
            {
                parentNode->rightSizeChild=mainNode->rightSizeChild;
                struct freeNode* temp = mainNode->leftSizeChild;
                struct freeNode* placeFinder = parentNode->rightSizeChild;

                while(placeFinder->leftSizeChild!=0)
                    placeFinder=placeFinder->leftSizeChild;

                placeFinder->leftSizeChild=temp;
                mainNode->leftSizeChild=0;
                mainNode->rightSizeChild=0;

                insertSize(root->rightSizeChild, mainNode);
            }
        }
    }
    }
	return found;
}


void findMatchMerge(struct freeNode* mainNode, struct freeNode* checkParent)
{
	if (checkParent->leftAddrChild != 0)
	{
		if (checkParent->leftAddrChild->addrs + checkParent->leftAddrChild->size == mainNode->addrs)
		{
			mainNode->addrs = checkParent->leftAddrChild->addrs;
			mainNode->size = mainNode->size + checkParent->leftAddrChild->size;
			deleteChild(checkParent, "Left");
		}
		else if (mainNode->addrs + mainNode->size == checkParent->leftAddrChild->addrs)
		{
			mainNode->size = mainNode->size + checkParent->leftAddrChild->size;
			deleteChild(checkParent, "Left");
		}
		else
		{
			findMatchMerge(mainNode, checkParent->leftAddrChild);
		}
	}

	if (checkParent->rightAddrChild != 0)
	{
		if (checkParent->rightAddrChild->addrs + checkParent->rightAddrChild->size == mainNode->addrs)
		{
			mainNode->addrs = checkParent->rightAddrChild->addrs;
			mainNode->size = mainNode->size + checkParent->rightAddrChild->size;
			deleteChild(checkParent, "Right");
		}
		else if (mainNode->addrs + mainNode->size == checkParent->rightAddrChild->addrs)
		{
			mainNode->size = mainNode->size + checkParent->rightAddrChild->size;
			deleteChild(checkParent, "Right");
		}
		else
		{
			findMatchMerge(mainNode, checkParent->rightAddrChild);
		}

	}
}



int insertAddr(struct freeNode* rootNode, struct freeNode* newNode)
{
	int isAnyChange = 0;
	if (rootNode->addrs>newNode->addrs)
	{
		if (newNode->addrs + newNode->size == rootNode->addrs)
		{
			rootNode->addrs = newNode->addrs;
			rootNode->size = rootNode->size + newNode->size;
			isAnyChange++;
			findMatchMerge(rootNode, rootNode);
		}
		else
		{
			if (rootNode->leftAddrChild == 0)
			{
				rootNode->leftAddrChild = newNode;
				insertSuccessfull = 1;
			}
			else
			{
				int change = insertAddr(rootNode->leftAddrChild, newNode);

				if (change != 0)
				{
					isAnyChange = change+1;
					if (rootNode->leftAddrChild->addrs + rootNode->leftAddrChild->size == rootNode->addrs)
					{
						rootNode->addrs = rootNode->leftAddrChild->addrs;
						rootNode->size = rootNode->size + rootNode->leftAddrChild->size;
						deleteChild(rootNode, "Left");
					}
				}
				if(change==1)
				{
				    checkSizeBST(root,rootNode->leftAddrChild->addrs);
				}
			}
		}
	}
	else
	{
		if (rootNode->addrs + rootNode->size == newNode->addrs)
		{
			isAnyChange++;
			rootNode->size = rootNode->size + newNode->size;
			checkSizeBST(root,rootNode->addrs);
			findMatchMerge(rootNode, rootNode);
		}
		else
		{
			if (rootNode->rightAddrChild == 0)
			{
				rootNode->rightAddrChild = newNode;
				insertSuccessfull = 1;
			}
			else
			{
				int change;
				change = insertAddr(rootNode->rightAddrChild, newNode);
				if (change != 0)
				{
					isAnyChange = change+1;
					if (rootNode->addrs + rootNode->size == rootNode->rightAddrChild->addrs)
					{
						rootNode->size = rootNode->size + rootNode->rightAddrChild->size;
						deleteChild(rootNode, "Right");
					}
				}
				
				if(change==1)
				{
				    checkSizeBST(root,rootNode->rightAddrChild->addrs);
				}
			}
		}
	}

	return isAnyChange;
}

void insertToTree(struct freeNode* newNode)
{
	insertSuccessfull = 0;
	if (root->leftAddrChild == 0)
	{
		root->leftAddrChild = newNode;
		insertSuccessfull++;
	}
	else
	{
		int chg;
		chg = insertAddr(root->leftAddrChild, newNode);
		
		if(chg==1)
		checkSizeBST(root,root->leftAddrChild->addrs);
	}

	if (insertSuccessfull == 1)
	{
		if (root->rightSizeChild == 0)
		{
			root->rightSizeChild = newNode;
		}
		else
		{
			insertSize(root->rightSizeChild, newNode);
		}
	}
}

void insert(int block_addrs, int block_size)
{
	struct freeNode* newNode = (void*)(intptr_t)brk(sizeof(struct freeNode));
	newNode->addrs = block_addrs;
	newNode->size = block_size;

	newNode->leftAddrChild = 0;
	newNode->rightAddrChild = 0;

	newNode->leftSizeChild = 0;
	newNode->rightSizeChild = 0;

	insertToTree(newNode);
}

void printAddr(struct freeNode* node)
{
	if (node->leftAddrChild != 0)
	{
		printAddr(node->leftAddrChild);
	}

	if (node->rightAddrChild != 0)
	{
		printAddr(node->rightAddrChild);
	}
}


void printSize(struct freeNode* node)
{
	if (node->leftSizeChild != 0)
	{
		printSize(node->leftSizeChild);
	}

	if (node->rightSizeChild != 0)
	{
		printSize(node->rightSizeChild);
	}
}

int getMemory(int size)
{
    if(root->rightSizeChild!=0)
    {
    int addrs = findAndFreeMemory(root->rightSizeChild,size);
    return addrs;
    }
    else
    {
	return 9;
    }
}





void init_Root()
{
        root = (void*)(intptr_t)brk(sizeof(struct freeNode));
        root->addrs = 0;
        root->size = 0;

        root->leftAddrChild = 0;
        root->rightAddrChild = 0;

        root->leftSizeChild = 0;
        root->rightSizeChild = 0;
}


void addMetaData(int addrs,int size)
{
	int* metaData = (void *) (intptr_t) addrs;
	metaData[0]=size;
	metaData[1]=0;
}



void* malloc(int size)
{  
     if(firstEntry==0)
       {
         init_Root();
         firstEntry++;
        }


    if(size%8!=0)
    {
        int cut = size%8;
        size=(size-cut)+(cut+(8-cut));
    }
		int addrs =0;
	
	addrs=getMemory(size+8);
	int returnAddrs;
	if(addrs==9 || addrs==0)
	{
		addrs = brk(size+8);
	    returnAddrs = addrs+8;
	}
	else
	{
	    returnAddrs = addrs+8;
	}
	
	addMetaData(addrs,size);
	return (void *) (intptr_t)returnAddrs;
}


void* calloc(int elems, int elemSize)
{ 
         if(firstEntry==0)
        {
         init_Root();
         firstEntry++;
        }

 
    int size = elems*elemSize;
    if(size%8!=0)
    {
        int cut = size%8;
        size=(size-cut)+(cut+(8-cut));
    }
		int addrs =0;
	
	addrs=getMemory(size+8);
	int returnAddrs;
	if(addrs==9 || addrs==0)
	{
		addrs = (int)brk(size+8);
	    returnAddrs = addrs+8;
	}
	else
	{
	    returnAddrs = addrs+8;
	}
	
	addMetaData(addrs,size);
	memset((int *)(intptr_t)returnAddrs,0,elems);
	
	return (void *) (intptr_t)returnAddrs;
}

void* realloc(void* inAddrs, int expandSize)
{
     if(firstEntry==0) 
        {
         init_Root();
         firstEntry++;
        }


    int size = expandSize;
    if(size%8!=0)
    {
        int cut = size%8;
        size=(size-cut)+(cut+(8-cut));
    }
		int addrs =0;
	
	addrs=getMemory(size+8);
	int returnAddrs;
	if(addrs==9 || addrs==0)
	{
		addrs = brk(size+8);
	    returnAddrs = addrs+8;
	}
	else
	{
	    returnAddrs = addrs+8;
	}
	
	addMetaData(addrs,size);
	
	int* block_size= ((int*)inAddrs)-2;
	memcpy((void *) (intptr_t)returnAddrs,inAddrs,block_size[0]);
	
	return (void *) (intptr_t)returnAddrs;
    
}

void free(void* addrs)
{
     if(firstEntry==0)
        {
	 init_Root();
	 firstEntry++;
	}
    int* a = addrs;
    int* m = a-2;
    insert((intptr_t)addrs,m[0]+8);   
}



#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"


/* Statiska hjalpfunktioner anvands av andra funktioner i tradet och ska inte ligga i interfacet (anvandaren behover inte kanna till dessa) */


/* Skapar en tradnod med det givna datat genom att allokera minne for noden. Glom inte att initiera pekarna*/
static struct treeNode* createNode(int data)
{
	struct treeNode *tempNode = malloc(sizeof(struct treeNode));

	if (tempNode != NULL)
	{
		tempNode->data = data;
		tempNode->left = NULL;
		tempNode->right = NULL;
		return tempNode;
	}
}

static int fillArray(BSTree tree, int *numbers)
{
	if (tree->left != NULL)
	{
		fillArray(tree->left, numbers);
	}

}

/* Returnerar en dynamiskt allokerad array som innehaller tradets data sorterat */
static int* writeSortedToArray(const BSTree tree)
{
	int* numbers = malloc(sizeof(int) * numberOfNodes(tree));
	numbers = fillArray(tree, numbers);
	return numbers;

		//Skriv datat frŒn tradet sorterat till arrayen (minsta till storsta)
		//- till detta kanske du behover en hjalpfunktion
    
}

/* Bygger upp ett sorterat, balanserat trad fran en sorterad array */
static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)
{
    /* Bygg rekursivt fran mitten.
       Mittenelementet i en delarray skapar rot i deltradet
       Vanster delarray bygger vanster deltrad
       Hoger delarray bygger hoger deltrad*/
}


/* Implementation av tradet, funktionerna i interfacet */

/* Skapar ett tomt trad - denna funktion ar fardig */
BSTree emptyTree(void)
{
	return NULL;
}

/* Returnerar 1 ifall tradet ar tomt, 0 annars */
int isEmpty(const BSTree tree)
{
	if (tree == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* Satter in 'data' sorterat i *tree
 Post-condition: data finns i tradet*/
void insertSorted(BSTree* tree, int data)
{
	if (*tree == NULL)
	{
		*tree = createNode(data);
	}
	else if (data > (*tree)->data)
	{
		insertSorted(&((*tree)->right), data);
	}
	else if (data < (*tree)->data)
	{
		insertSorted(&((*tree)->left), data);
	}

	/*Tank pa att tradet kan vara tomt vid insattning
      Post-condition kan verifieras med hjalp av find(...)*/
}

/* Utskriftsfunktioner
   Vid anrop: anvand stdio som andra argument for att skriva ut pŒ skarmen
   Det racker att ni implementerar LR ordningarna*/
void printPreorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
	{
		return;
	}
	
	printf("%i", tree->data);
	printPreorder(tree->left, stdout);
	printPreorder(tree->right, stdout);
}

void printInorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
	{
		return;
	}
	printPreorder(tree->left, stdout);
	printf("%i", tree->data);
	printPreorder(tree->right, stdout);
}

void printPostorder(const BSTree tree, FILE *textfile)
{
	if (tree == NULL)
	{
		return;
	}
	printPreorder(tree->left, stdout);
	printPreorder(tree->right, stdout);
	printf("%i", tree->data);
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
	if (tree == NULL)
	{
		return 0;
	}
	else if (data == tree->data)
	{
		return 1;
	}
	else if (data > tree->data)
	{
		return find(tree->right, data);
	}
	else if (data < tree->data)
	{
		return find(tree->left, data);
	}
}

/* Tar bort 'data' fran tradet om det finns */
void removeElement(BSTree* tree, int data)
{
	if (*tree == NULL)
	{
		return;
	}
	else if (data < (*tree)->data)
	{ 
		removeElement(&(*tree)->left, data);
	}
	else if (data > (*tree)->data)
	{
		removeElement(&(*tree)->right, data);
	}
	else
	{
		if ((*tree)->left == NULL && (*tree)->right == NULL)
		{
			free(*tree);
			*tree = NULL;
		}
		else if ((*tree)->left == NULL)
		{
			BSTree tempPtr = *tree;
			*tree = (*tree)->right;
			free(tempPtr);
		}
		else if ((*tree)->right == NULL)
		{
			BSTree tempPtr = *tree;
			*tree = (*tree)->left;
			free(tempPtr);
		}
		else
		{
			BSTree tempPtr = (*tree)->right;
			while (tempPtr->left != NULL)
			{
				tempPtr = tempPtr->left;
			}
			(*tree)->data = tempPtr->data;
			removeElement(&(*tree)->right, tempPtr->data);
		}
	}
}

/* Returnerar hur manga noder som totalt finns i tradet */
int numberOfNodes(const BSTree tree)
{
	int nodeAmount = 0;
	
	if (tree == NULL)
	{
		return 0;
	}
	else
	{
		nodeAmount++;
		nodeAmount += numberOfNodes(tree->left);
		nodeAmount += numberOfNodes(tree->right);
		return nodeAmount;
	}
}
/* Returnerar hur djupt tradet ar */
int depth(const BSTree tree)
{
	int leftDepth = 0;
	int rightDepth = 0;
	int maxDepth = 0;
	
	// If the tree is empty immediately returns 0
	if (tree == NULL)
		return 0;
	
	else
	{
		leftDepth = depth(tree->left);
		rightDepth = depth(tree->right);
		if (leftDepth > rightDepth)
			return maxDepth = leftDepth+1;
		else
			return maxDepth = rightDepth+1;
	}
}

/* Returnerar minimidjupet for tradet
   Se math.h for anvandbara funktioner*/
int minDepth(const BSTree tree)
{
	int nodeAmount = numberOfNodes(tree);
	int depth = log2(nodeAmount - 1) + 1;
	return depth;
}

/* Balansera tradet sa att depth(tree) == minDepth(tree) */
void balanceTree(BSTree* tree)
{
	int sortedNumbers = writeSortedToArray(*tree);
	/* Forslag pa algoritm:
	   - overfor tradet till en dynamiskt allokerad array med writeSortedToArray()
	   - tom tradet med freeTree()
	   - bygg upp tradet rekursivt fran arrayen med buildTreeSortedFromArray()
	   - frigor minne for den dynamiskt allokerade arrayen


	   Post-conditions:
	   - tree har lika manga noder som tidigare
	   - djupet for tradet ar samma som minimumdjupet for tradet */
}

/* Tom tradet och frigor minnet for de olika noderna */
void freeTree(BSTree* tree)
{
	// Post-condition: tradet ar tomt
}



/************************************************************************
BinarySearchTree.h

Purpose:
    Define constants used in the project.
    Struct definitions for a general Binary Search Tree.
    Define function prototypes used by general Binary Search Trees.
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>



//#define constant values
#define TRUE 1
#define FALSE 0


//typedef for the Element struct which constains a c string to store a URL in the BrowserList
typedef struct
{
    int accountNumber;
    double accountBalance;
} Element;
//Link list node struct with element for account data and pointer node for next node
typedef struct NodeLL
{
    Element element;
    struct NodeLL *next;
} NodeLL;
//Linked list implementation struct with node pointer to the head of list
typedef struct
{
    NodeLL *head;
}LinkedListImp;

typedef LinkedListImp *LinkedList;

//Typedef for a node in the doubly linked list (has next and previous pointers).
typedef struct NodeT
{
    Element element;
    struct NodeT *left;
    struct NodeT *right;
} NodeT;

//Typedef for a binary search tree implementation.  
//Contains a pointer to the root node of the tree.
typedef struct
{
    NodeT *root;
} BinarySearchTreeImp;

typedef BinarySearchTreeImp *BinarySearchTree;


/*****Prototypes*******/

//Malloc a new BinarySearchTreeImp and return it's address.
BinarySearchTree newBinarySearchTree();

//Malloc a new LinkedListImplementation and returns the address
LinkedList newLinkedList();


//Free the BinarySearchTree and any nodes that still exist in the tree.
void freeBinarySearchTree(BinarySearchTree tree);


//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeT *allocateNode(Element value);

//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeLL *allocateNodeLL(Element value);

//Recursive algorithm for searching for a node with key value equal to searchValue.  Return a pointer to the node if you find it or return NULL if it does not exist.
NodeT *search(NodeT *p, int searchValue);

//recursive call to find a current account
NodeLL *searchLL(NodeLL *h, int n);

//Create a node to store the given Element and add it as a leaf in the BinarySearchTre e.  Do not worry about balancing the tree for this project.
//Return true if the insert worked successfully, and return false if the node already existed in the tree.
int insert(NodeT **pp, Element value);

//inserts NodeLL into linked list
NodeLL *insertLL(NodeLL *h, Element value);

//Recursivly print the key values of all nodes in the subtree rooted at p in increasing order.
void printInOrder(NodeT *p);

//Recursivly print the key values of all nodes in the subtree rooted at p according to a preorder traversal.
void printPreOrder(NodeT *p);
//recursively prints LinkedList data
void printLL(NodeLL *h);
//free nodes in BST
int freeNodes(NodeT *p);
//frees linked list and its nodes
void freeLL(LinkedList l);


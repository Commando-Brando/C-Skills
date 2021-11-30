#include "BinarySearchTree.h"

/******
 * In this file, provide all of the definitions of the queue functions as described in BinarySearchTree.h.
 * 
 * ****/
//Malloc a new BinarySearchTreeImp and return it's address.
BinarySearchTree newBinarySearchTree(){
    BinarySearchTreeImp *t = (BinarySearchTreeImp*) malloc(sizeof(BinarySearchTreeImp));
    t->root = NULL;
    return t;
}
//Malloc a new LinkedListImplementation and returns the address
LinkedList newLinkedList(){
    LinkedListImp *l = (LinkedListImp*) malloc(sizeof(LinkedListImp));
    l->head = NULL;
    return l;
}
//Free the BinarySearchTree and any nodes that still exist in the tree.
void freeBinarySearchTree(BinarySearchTree tree){
    freeNodes(tree->root);
    free(tree);
}
//free nodes in BST
int freeNodes(NodeT *p){
    if(p == NULL){
        return 0;
    }
    freeNodes(p->left);
    freeNodes(p->right);
    free(p);
}
//Allocate a new node and store "value" as the Element in the node.  Return the address of the node.
NodeT *allocateNode(Element value){
    NodeT *n = (NodeT*) malloc(sizeof(NodeT));
    n->left = NULL;
    n->right = NULL;
    n->element = value;
    return n;
}
NodeLL *allocateNodeLL(Element value){
    NodeLL *n = (NodeLL*) malloc(sizeof(NodeLL));
    n->next = NULL;
    n->element = value;
    return n;
}
//Recursive algorithm for searching for a node with key value equal to searchValue.  Return a pointer to the node if you find it or return NULL if it does not exist.
NodeT *search(NodeT *p, int searchValue){
    
    if(p == NULL){
        printf("Node does not exist\n");
        printf("%d\n", searchValue);
        return NULL;
    }
    if(p->element.accountNumber == searchValue){
        return p;
    }
    if(p->element.accountNumber < searchValue){
        return search(p->right, searchValue);
    }
    if(p->element.accountNumber > searchValue){
        return search(p->left, searchValue);
    }
}
//Searches Linkedlist to find NodeLL matching the current account number
NodeLL *searchLL(NodeLL *h, int n){
    if(h == NULL){
        return NULL;
    }
    else if(h->element.accountNumber == n){
        return h;
    }
    else{
        searchLL(h->next, n);
    }
}
//Create a node to store the given Element and add it as a leaf in the BinarySearchTre e.  Do not worry about balancing the tree for this project.
//Return true if the insert worked successfully, and return false if the node already existed in the tree.
int insert(NodeT **pp, Element value){
    if(*pp == NULL){ 
        *pp = allocateNode(value);
        return TRUE;
    }
    if(value.accountNumber == (*pp)->element.accountNumber){
        return FALSE;
    }
    if(value.accountNumber < (*pp)->element.accountNumber){
        return insert((&(*pp)->left), value);
    }
    else{
        return insert((&(*pp)->right), value);
    }
}
//allocates a new node and inserts it into the Linked List
NodeLL *insertLL(NodeLL *h, Element value){
    NodeLL *c;
    if(h == NULL || h->element.accountNumber <= value.accountNumber){
        c = allocateNodeLL(value);
        c->next = h;
        h = c;
        return h;
    }
    else{
        c = h;
        while(c->next != NULL && c->next->element.accountNumber >= value.accountNumber){
            c = c->next;
        }
        if(c->element.accountNumber == value.accountNumber)
            return h;
        NodeLL *r = allocateNodeLL(value);
        r->next = c->next;
        c->next = r;
    }
    
    return h;
}
//Recursivly print the key values of all nodes in the subtree rooted at p in increasing order.
void printInOrder(NodeT *p){
    if(p == NULL){
        return;
    }
    printInOrder(p->left);
    printf("%d %.2lf\n", p->element.accountNumber, p->element.accountBalance);
    printInOrder(p->right);
}
//Recursivly print the key values of all nodes in the subtree rooted at p according to a preorder traversal.
void printPreOrder(NodeT *p){
    if(p == NULL){
        return;
    }
    printf("%d %.2lf\n", p->element.accountNumber, p->element.accountBalance);
    printInOrder(p->left);
    printInOrder(p->right);
}
//recursively prints LinkedList data
void printLL(NodeLL *h){
    if(h == NULL){
        return;
    }
    else{
        printf("%d %.2lf\n", h->element.accountNumber, h->element.accountBalance);
        return printLL(h->next);
    }
}
//frees linked list and its nodes
void freeLL(LinkedList l){
    if(l->head == NULL){ //edge case check to see if linked list is empty
        return;
    }
    NodeLL *c = l->head;
    while(c != NULL){ //traverses and frees the linked list
        NodeLL *temp = c;
        c = c->next;
        free(temp);
    }
    free(l); //finally free the linked list
}

#include "Queue.h"

/******
 * In this file, provide all of the definitions of the queue functions as described in Queue.h.
 *
 * ****/
Queue newQueue(){
    QueueImp *q = (QueueImp*) malloc(sizeof(QueueImp));
    if(q == NULL){
        printf("error q did not malloc correctly");
        exit(0);
    }
    q->head = NULL;
    q->foot = NULL;
    return q;
}
//frees nodes in an array 
void freeNode(NodeLL *p){
    if (p == NULL)
    {
        return;
    }
    freeNode(p->next);
    free(p);
}
void freeQueue(Queue q){
    if(q->head != NULL){
        freeNode(q->head);
    }
    free(q);
}
NodeLL *allocateNode(Element value){
    NodeLL *n = (NodeLL*) malloc(sizeof(NodeLL));
    n->element = value;
    n->next = NULL;
    return n;
}
void enqueue(Queue q, Element value){
    NodeLL *n = allocateNode(value);
    if(q->foot == NULL){
        q->foot = n;
        q->head = n;
    }
    else{
        q->foot->next = n;
        q->foot = n;
    }
}
int dequeue(Queue q, Element *e){
    NodeLL *temp;
    if(q->head == NULL){
        return FALSE;
    }
    else{
        *e = q->head->element;
        temp = q->head;
        q->head = q->head->next;
        if(q->head == NULL){
            q->foot = NULL;
        }
        free(temp);
        return TRUE;
    }
}
int frontElement(Queue q, Element *e){
    if(q->head == NULL){
        return FALSE;
    }
    else{
        *e = q->foot->element;
        return TRUE;
    }
}
int isEmptyQueue(Queue q){
    if(q->head == NULL){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
//prints out the contents of a queue
void printQueue(Queue q){
    if(q->head == NULL){
        printf("Q is empty");
    }
    else{
        NodeLL *p;
        for(p = q->head; p != NULL; p = p->next){
            //printf("ID: %d Items: %d\t", p->element.shopperID, p->element.numberOfItems);
        }
        
    }
}


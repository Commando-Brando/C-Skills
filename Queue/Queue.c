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
void freeQueues(Queue *qs, int size){
    int i;
    for(i = 0; i < size; i++){
        freeQueue(qs[i]);
    }
    free(qs);
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
int isEmpty(Queue q){
    if(q->head == NULL){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
//populates a queue array
Queue * populateQueue(int size){
    Queue *qs = (Queue*) malloc(size * sizeof(Queue));
    if(qs == NULL){
        printf("error q array did not malloc correctly");
        exit(0);
    }
    int i;
    for(i = 0; i < size; i++){
        qs[i] = newQueue();
    }
    return qs;
}
//prints out the contents of a queue 
void printQueues(Queue *qs, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("\n Q%d\n", i);
        printQueue(qs[i]);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------------------\n");
}
//prints out the contents of a queue
void printQueue(Queue q){
    if(q->head == NULL){
        printf("Q is empty");
    }
    else{
        NodeLL *p;
        for(p = q->head; p != NULL; p = p->next){
            printf("ID: %d Items: %d\t", p->element.shopperID, p->element.numberOfItems);
        }
        
    }
}
//calculates the queue with the shortest wait time
int shortestTime(Queue *qs, int size){
    int i;
    NodeLL *p;
    int shortest;
    int shortQueue = 0;
    int arr[size];
    for(i = 0; i < size; i++){
        arr[i] = 0;
    }
    for(i = 0; i < size; i++){
        if(qs[i]->head != NULL){
            for(p = qs[i]->head; p != NULL; p = p->next){ //p->next MIGHT BE WRONG FOR MIDDLE ARGUMENT 
                arr[i] += p->element.numberOfItems;
            }
        }
    }
    shortest = arr[0];
    for(i = 1; i < size; i++){
        if(arr[i] < shortest){
            shortest = arr[i];
            shortQueue = i;
        }
    }
    return shortQueue;
}
//flushes nodes out of a queue array
void emptyQueues(Queue *qs, int size, int time){
    NodeLL *p;
    time = time + 1;
    int i;
    //time = time + 1;
    Element eTemp;
    while(remainItems(qs, size)){
        //printQueues(qs, size);
        for(i = 0; i < size; i++){
            if(!isEmpty(qs[i])){
                qs[i]->head->element.numberOfItems--;
                if(qs[i]->head->element.numberOfItems == 0){
                    eTemp = qs[i]->head->element;
                    dequeue(qs[i], &eTemp);
                    //printf("Current time: %d", time);
                    printf("Shopper %d finished checking out of Line %d at time %d\n", eTemp.shopperID, i, (time));
                }
            }
        }
        time++;
    }
    
}
//checks to see if a queue array is empty by calling isEmpty on each queue
int remainItems(Queue *qs, int size){
    int i;
    for(i = 0; i < size; i++){
        if(!isEmpty(qs[i])){
            return TRUE;
        }
    }
    return FALSE;
}





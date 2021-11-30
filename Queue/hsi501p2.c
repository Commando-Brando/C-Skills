#include "Queue.h"

int main()
{
    FILE *f;
    f = fopen("p2Input.txt", "r");
    if(f == NULL){
        perror("Error: Could not open file"); //opening and checking if file opens and works
        return -1;
    }
    //Variables needs to complete main
    int size = 3;
    Queue *qs = populateQueue(size);
    char fLine[50];
    int newTime;
    int previousTime = 0;
    int timeChange = 0;
    int i;
    Element eTemp;
    Element dTemp;
    NodeLL *p;
    int empty = FALSE;
    int shortestQueue;
    int remaining = 0;
    //While loop that reads in file lines and parses data
    while(fgets(fLine, 50, f)){
        sscanf(fLine, "%d %d %d", &newTime, &(eTemp.shopperID), &(eTemp.numberOfItems));
        NodeLL *n = allocateNode(eTemp);
        for(i = 0; i < size; i++){ //for loop completes necessary time change and item deductions
            timeChange = newTime - previousTime;
            
            if(qs[i]->head != NULL){
                while(timeChange > 0){
                    p = qs[i]->head;
                    if(p->element.numberOfItems > timeChange){
                        p->element.numberOfItems = p->element.numberOfItems - timeChange;
                        timeChange = 0;
                    }
                    else if(p->element.numberOfItems <= timeChange){
                        dTemp = p->element;
                        timeChange = timeChange - p->element.numberOfItems;
                        remaining = dTemp.numberOfItems;
                        if(dequeue(qs[i], &dTemp) == TRUE){ //Dequeue here and print right after
                            printf("Shopper %d finished checking out of Line %d at time %d\n", dTemp.shopperID, i, (remaining + previousTime)); 
                        }
                    }
                }
            }
        }
        
        for(i = 0; i < size; i++){  //Checks to see if any empty queues for enqueue
            if(isEmpty(qs[i])){
                eTemp.numberOfItems = eTemp.numberOfItems - 1;
                enqueue(qs[i], eTemp);
                empty = TRUE;
                break;
            }
        }
        if(empty == FALSE){ //if no queues are empty than we enqueue here
            shortestQueue = shortestTime(qs, size);
            enqueue(qs[shortestQueue], eTemp);
        }
        empty = FALSE; //reset empty queue int checker
        previousTime = newTime; //reset time variable

    }
    emptyQueues(qs, size, previousTime); //function empties all nodes remaining in the queues and prints them the right time
    freeQueues(qs, size); //frees queues
    fclose(f); //closes file
    printf("Extra credit:  minimum of 9 lanes needed to keep lines under 25.");
    return 0;
}

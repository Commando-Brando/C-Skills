#include "BinarySearchTree.h"
/*
 * BST Project main file we read in the file here and add file data to the BST via the creation and insertion of nodes structs that store the file data. We store nodes in the BST based on
 * the account numbers and then later update those account nodes with account balance data based on the "SALES" lines in the file. 
*/
int main()
{
    LinkedList l = newLinkedList();
    BinarySearchTree t = newBinarySearchTree(); //create out BST implementation and right below we check if it was created successfully
    if(t == NULL){
        printf("Error in dynamically allocating BST\n");
        return -1;
    }
    FILE *f; //create the file variable, open it below, and then check success
    f = fopen("largeInput.txt", "r");
    if(f == NULL){
        printf("Error could not open file\n");
        return -1;
    }
    //below are all our temp variables that we use to store in the file data and send into our BST via nodes
    char buff[50];
    char command[10];
    char cType[10];
    int num;
    double bal;
    Element temp;
    clock_t start, end, totalBSTS, totalLLS, totalBSTT, totalLLT;
    start = clock();
    //just below is main while loop that traverses the file and reads in data inserting into the BST, updated account balances of accounts, and printing the BST 
    while(fgets(buff, 50, f)){
        bal = 0;
        if(buff[0] == 'C'){ //if the first word is "CREATE" we create a new account node and add it to the tree unless it already exists
            sscanf(buff, "%s %d", command, &num);
            temp.accountNumber = num;
            if(insert(&(t->root), temp) != TRUE){
                printf("Error account has already been added\n");
            }
        }
        else if(buff[0] == 'S'){ //if the first string is "SALE" then we update the corresponding account with the correspond account balance double
            sscanf(buff, "%s %d %lf", command, &num, &bal);
            NodeT *nTemp = search(t->root, num);
            if(nTemp != NULL){
                nTemp->element.accountBalance += bal;
            }
        }
        else if(buff[0] == 'P'){ //if the first string is "PRINT" then we call a print function based on the type following, INORDER or PREORDEr
            sscanf(buff, "%s %s", command, cType);
            if(cType[0] == 'P'){
                printPreOrder(t->root);
            }
            else if(cType[0] == 'I'){
                printInOrder(t->root);
            }
            else{
                printf("Error print statement input invalid\n");
            }
        }
        else{
            printf("Error no input match found\n"); //Check for error input in the file
        }
    }
    end = clock();
    totalBSTT = (double)(end - start);
    totalBSTS = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    freeBinarySearchTree(t); //free the nodes and the tree itself
    rewind(f); //rewinds file to run through again
    start = clock(); //start system clock
    while(fgets(buff, 50, f)){
        bal = 0;
        if(buff[0] == 'C'){ //if the first word is "CREATE" we create a new account node and add it to the linked list unless it already exists
            sscanf(buff, "%s %d", command, &num);
            temp.accountNumber = num;
            l->head = insertLL(l->head, temp);
        }
        else if(buff[0] == 'S'){ //if the first string is "SALE" then we update the corresponding account with the correspond account balance double
            sscanf(buff, "%s %d %lf", command, &num, &bal);
            NodeLL *nTemp = searchLL(l->head, num);
            if(nTemp != NULL){
                nTemp->element.accountBalance += bal;
            }
            else{
                printf("Sale error: account not found\n");
            }
        }
        else if(buff[0] == 'P'){ //if the first string is "PRINT" then we call a print function for the Linked List
            sscanf(buff, "%s %s", command, cType);
            printLL(l->head);
        }
        else{
            printf("Error no input match found\n"); //Check for error input in the file
        }
    }
    end = clock();
    //below calculates and prints the time each data structure took to complete the tasks
    totalLLT = (double)(end - start);
    totalLLS = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("BST took %lf seconds or %lf CPU ticks\n", (double)totalBSTS, (double)(totalBSTT));
    printf("Linked List time: %lf seconds or %lf CPU ticks\n", (double)totalLLS, (double)(totalLLT));
    if((double)(totalBSTT) <  (double)(totalLLT)){
        printf("BST is faster by %lf seconds and %lf CPU ticks\n", (double)(totalLLS - totalBSTS), (double)(totalLLT - totalBSTT));
    }
    else if((double)(totalBSTT) >  (double)(totalLLT)){
        printf("Linked List is faster by %lf seconds and %lf CPU ticks\n", (double)(totalBSTS - totalLLS), (double)(totalBSTT - totalLLT));
    }
    else{
        printf("They took the same amount of time to complete\n");
    }
    freeLL(l); //frees the link list
    fclose(f); //close file
    return 0;
}

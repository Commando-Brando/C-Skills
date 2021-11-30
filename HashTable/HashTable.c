#include "HashTable.h"

/******
 * In this file, provide all of the definitions of the hash table functions as described in HashTable.h.
 *
 * ****/
//Malloc a new HashTableImp, malloc the hashTable to be an array of HashTableEntrys of size n, 
//initialize each iChainIndex to be -2 (indicating that the spot is empty), 
//and return a pointer to the HashTableImp.
HashTable newHashTable(int n){
    HashTable t = (HashTable) malloc(sizeof(HashTable));
    t->n = n;
    t->hashTable = (HashTableEntry*) malloc(n * sizeof(HashTableEntry));
    int i;
    for(i = 0; i < n; i++){
        t->hashTable[i].chainIndex = -2;
    }
    return t;
}
//Free the HashTable h.
void freeHashTable(HashTable h){
    free(h->hashTable);
    free(h);
}
//Given a string, convert it into an integer to be used in either
//the division method or the midsquare method.
int stringToInt(char *stringToConvert){
    int i, sum;
    sum = 0;
    for(i = 0; i < strlen(stringToConvert); i++){
        sum += stringToConvert[i];
    }
    return sum;
}
//Given a key value, use the division method to find a 
//valid index for hashTable.
int divisionMethod(int key, int n){
    return key % n;
}
//Given a key value, use the midsquare method to find a 
//valid index for hashTable.
int midsquareMethod(int key, int n){
    key = key * key;
    key = (key / 1000) % n;
    return key;
}
//Insert e into our HashTable h by using stringToInt to convert the team name
//into an integer and then passing that integer to one of the division or 
//midsquare method functions.  If this entry is not occupied, insert it there
//and change the corresponding iChainIndex to be -1.  If there is a collision,
//use open chaining to find an open location for e, and update the iChainIndex
//values accordingly.
void put(HashTable h, Element e){
    int index = divisionMethod(stringToInt(e.teamName), h->n);
    if(h->hashTable[index].chainIndex == -2){
        h->hashTable[index].key = e;
        h->hashTable[index].chainIndex = -1;
    }
    else{
        int k = 7;
        int end = index;
        while(h->hashTable[end].chainIndex != -1)
            end = h->hashTable[end].chainIndex;
        int newIndex = (end + k) % h->n;
        while(h->hashTable[newIndex].chainIndex != -2){
            newIndex = (newIndex + k) % h->n;
        }
        h->hashTable[end].chainIndex = newIndex;
        h->hashTable[newIndex].key = e;
        h->hashTable[newIndex].chainIndex = -1;
    }
    //printf("End of Put Function\n");
}
//Return the struct stored in HashTable h from the
//team name stored in teamName using e that is passed
//by reference.  Functionally return TRUE if it exists
//or FALSE if it does not exist.
Element* get(HashTable h, char *teamName){
    Element *e;
    int index = divisionMethod(stringToInt(teamName), h->n);
    while(strcmp(h->hashTable[index].key.teamName, teamName) != 0 && h->hashTable[index].chainIndex != -1)
            index = h->hashTable[index].chainIndex;
    if(strcmp(h->hashTable[index].key.teamName, teamName) == 0){
        e = &h->hashTable[index].key;
        //printf("found the team %s\n", e->teamName);
        return e;
    }
    else
        return NULL;
}

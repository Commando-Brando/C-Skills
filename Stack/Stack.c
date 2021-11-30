#include "Stack.h"
/******
 * In this file, provide all of the definitions of the stack functions as described in stack.h.
 *
 * ****/

Stack newStack(int maximumStackSize)
{
    StackImp* myStack = (Stack) malloc(maximumStackSize * sizeof(Stack));
    myStack->count = 0;
    myStack->maxSize = maximumStackSize;
    myStack->stackElements = (Element*) malloc(maximumStackSize * sizeof(Element));
    return myStack;
}

void freeStack(Stack s)
{
    free(s->stackElements);
    free(s);
}
        
 void push(Stack s, Element e)
 {
     if(s->count == s->maxSize){
         printf("Error: stack is full\n");
     }
     s->stackElements[s->count] = e;
     s->count++;
 }
Element pop(Stack s){
    s->count--;
    return s->stackElements[s->count];
}
int isEmpty(Stack s){
    if(s->count == 0){
        return 1;
    }
    else{
        return 2;
    }
}
Element topElement(Stack s){
    return s->stackElements[s->count - 1];
}

int precedence(char operator){
    if(operator == '/' || operator == '*'){
        return 2;
    }
    else if(operator == '-' || operator == '+'){
        return 1;
    }
}


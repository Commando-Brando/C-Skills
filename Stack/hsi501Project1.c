#include "Stack.h"

#define MAX_LINE_LENGTH 50


int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);


int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);

		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("\nPostfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString){
    //printS(infixString);
    int i = 0;
    int pCounter = 0;
    Element pushE;
    Stack s = newStack(MAX_LINE_LENGTH);
    int leftPCheck = 0;
    int rightPCheck = 0;
    int doubleOperator = 0;
    int doubleOperand = 0;
    while(infixString[i] != '\0'){
        if(infixString[i] > 47 && infixString[i] < 58){ //if character send to post
            doubleOperand++;
            postfixString[pCounter] = infixString[i];
            pCounter++;
        }
        else if(infixString[i] > 41 && infixString[i] < 48 || infixString[i] == '('){ 
            if(infixString[i] != '('){
                doubleOperator++;
            }
            pushE.operation = infixString[i];
            if(isEmpty(s) == 1 || topElement(s).operation == '(' || infixString[i] == '('){
                if(infixString[i] == '('){
                    leftPCheck++;
                }
                push(s, pushE);
            }
            else if(precedence(infixString[i]) <= precedence(topElement(s).operation)){
                while(s->count != 0 && topElement(s).operation != '('){
                    postfixString[pCounter] = pop(s).operation;
                    pCounter++;
                }
                push(s, pushE);
            }
            else if(precedence(infixString[i]) > precedence(topElement(s).operation)){
                push(s, pushE);
            }
        }
        else if(infixString[i] == ')'){
            rightPCheck++;
            while(s->count != 0 && topElement(s).operation != '('){
                    postfixString[pCounter] = pop(s).operation;
                    pCounter++;
                    }
            pop(s);
        }
        else if(infixString[i] == ' '){
        }
        i++;
    }
    if(leftPCheck < rightPCheck){
        return 1;
    }
    if(leftPCheck > rightPCheck){
        return 2;
    }
    if(doubleOperator > (doubleOperand - 1)){
        return 4;
    }
    if(doubleOperator < (doubleOperand - 1)){
        return 3;
    }
    while(s->count != 0){
        postfixString[pCounter] = pop(s).operation;
        pCounter++;
    }
    postfixString[pCounter] = '\0';
    freeStack(s);
    return 0;
}



/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString){
    Stack s = newStack(MAX_LINE_LENGTH);
    int i = 0;
    Element temp;
    int pop1;
    int pop2;
    Element result;
    while(postfixString[i] != '\0'){
        if(postfixString[i] > 47 && postfixString[i] < 58){ 
            temp.operand = postfixString[i] - '0';
            push(s, temp);
        }
        else if(postfixString[i] > 39 && postfixString[i] < 48){
            pop2 = pop(s).operand;
            pop1 = pop(s).operand;
            switch(postfixString[i])
		{
			case '/': 
				result.operand = pop1 / pop2;
				break;
			case '*':  
                                result.operand = pop1 * pop2;
				break;
			case '+': 
				result.operand = pop1 + pop2;
				break;
			case '-': 
				result.operand = pop1 - pop2;
				break;
		}
            push(s, result);
            
        }
        i++;
    }
    freeStack(s);
    return s->stackElements[0].operand;
}

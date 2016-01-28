#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct stack{
	char ch;
	struct stack *next;
}Stack;

Stack *top = NULL;
Stack *head = NULL;
Stack *tail = NULL;

void append(char);
void push(char);
char pop();
char topStack();
int isEmty();
void compare(char);
void pushOrCompare(char);
void check(char);
void input();
void output();
void beforeOutput();
void destroy();

int main(int argc, const char* argv[]){
	char chk;
	printf("\t<<<<<<<<<< Welcome to Infix to Postfix Program >>>>>>>>>>\n");
	do{
		printf("\n\tInfix\t: ");
		input();
		printf("\t------------------------------------------------------------");
		beforeOutput();
		printf("\n\tPostfix\t: ");
		output();
		printf("\n\t------------------------------------------------------------");
		destroy();
		printf("\n\n");
		do{
			printf("\tDo you want to change Infix to Post (y/n)? : ");
			fflush(stdin);
			scanf("%c", &chk);
		}while(!(tolower(chk) == 'y' || tolower(chk) == 'n'));
		
	}while(tolower(chk) != 'n');
	
	printf("\n\n\t<<<<<<<<<<<<<<<<<<<<<<<< Good Bye >>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	return 0;
}

void input(){
	char ch;
	do{
		fflush(stdin);
		scanf("%c", &ch);
		if(ch == '\n')
			printf("\tInfix\t: ");
	}while(ch == '\n');
	
	while(ch != '\n'){
		check(ch);
		scanf("%c", &ch);
	}
}

void output(){
	Stack *travel = head;
	while(travel != NULL){
		printf("%c", travel->ch);
		travel = travel->next;
	}
}

void destroy(){
	Stack *travel = head;
	Stack *del;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
	head = NULL;
	
	travel = top;
	while(travel != NULL){
		del = travel;
		travel = travel->next;
		free(del);
	}
}

void beforeOutput(){
	Stack *travel = top;
	while(travel != NULL){
		travel = travel->next;
		append(pop());
	}
}

void append(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	if(head == NULL){
		head = n;
	}else{
		tail->next = n;
	}
	tail = n;
	tail->ch = ch;
	tail->next = NULL;
}

void push(char ch){
	Stack *n = (Stack *)malloc(sizeof(Stack));
	n->next = top;
	top = n;
	n->ch = ch;
}

char pop(){
	Stack *backup = top;
	char ch = top->ch;
	top = top->next;
	free(backup);
	return ch;
}

char topStack(){
	return (isEmty())? NULL : top->ch;
}

int isEmty(){
	return (top == NULL)? 1 : 0;
}

void compare(char ch){
	char stackTop = topStack();

	if(stackTop == '(' || ch == '(')
		push(ch);
	else if(ch == ')'){
		Stack *travel = top;
		while(travel->ch != '('){
			travel = travel->next;
			append(pop());
		}
		pop();
	}
	else if(ch == '^'){
		if(stackTop == ch){
			append(pop());
			pushOrCompare(ch);
		}else{
			push(ch);
		}
	}else if(ch == '*' || ch == '/'){
		if(stackTop == '^' || stackTop == '*' || stackTop == '/'){
			append(pop());
			pushOrCompare(ch);
		}else{
			push(ch);
		}
	}
	else{
		append(pop());
		pushOrCompare(ch);
	}
}

void pushOrCompare(char ch){
	if(isEmty())	
		push(ch);
	else
		compare(ch);
}

void check(char ch){
	if(isalpha(ch)){
		append(ch);
	}else{
		pushOrCompare(ch);
	}
}

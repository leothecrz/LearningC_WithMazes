
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int isEmpty( struct Stack *stk ){
	
	int length = (stk->length);
	
	if ( (length) > 0 ){
		return 0;
	} else {
		return 1;
	}
}

void push( struct Stack *stk, struct Cell *cell ){

	struct Node *newNode;
	newNode = (struct Node*) malloc(sizeof(struct Node));

	(*newNode).next = ((*stk).top);
	(*newNode).data = cell;

	(*stk).top = newNode;
	(*stk).length += 1;

}

struct Cell* pop(struct Stack *stk){

	if (!isEmpty(stk)){
		struct Node *node = (stk)->top;
		(*stk).length -= 1;
		(*stk).top = (*node).next;

		struct Cell *cell = (*node).data;
		return cell;
	}
}
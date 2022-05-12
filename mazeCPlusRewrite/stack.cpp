#include "stack.h"
#include <stdlib.h>

Stack::Stack(){
    this->count = 0;
    this->top = 0;
}

int Stack::isEmpty(void){

    return (!( (this->count)>0) ) ;

}

void Stack::push(struct Cell* cell){

    struct Node* p_node;
    p_node = (struct Node *) malloc(sizeof(struct Node));

    (*p_node).next = this->top;
    (*p_node).data = cell;

    this->top = p_node;
    this->count++;

}

struct Cell* Stack::pop(void){
    if(!(this->isEmpty())){
        struct Node* active = this->top;
        this->count--;
        this->top = active->next;

        return active->data;

    } else{
        exit(1);
    }

}
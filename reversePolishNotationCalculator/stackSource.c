#include "stackHeader.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
void StackInit(Stack *Stack_ptr){
    Stack_ptr->top_ptr = NULL;
    Stack_ptr->bottom_ptr = NULL;
    Stack_ptr->height = 0;
}

long pop(Stack *stack_ptr){
    assert(stack_ptr->height > 0);
    Token *token_ptr;
    if(stack_ptr->height == 1){
        token_ptr = stack_ptr->top_ptr;
        StackInit(stack_ptr);
    }
    else if(stack_ptr->height > 1){
        token_ptr = stack_ptr->top_ptr;
        stack_ptr->top_ptr = token_ptr->below_ptr;
        stack_ptr->height--;
    }
    int val = token_ptr->val;
    free(token_ptr);
    return val;
}

void push(Stack *stack_ptr, long val){
    Token *t_ptr = malloc(sizeof(Token));
    t_ptr->val = val;
    t_ptr->below_ptr = stack_ptr->top_ptr;
    stack_ptr->top_ptr = t_ptr;
    stack_ptr->height++;
}

void printStack(Stack *stack_ptr){
    printf("|-----TOP\n");
    Token *curr_ptr = stack_ptr->top_ptr;
    while(curr_ptr != NULL){
        printf("  %ld\n",curr_ptr->val);
        curr_ptr = curr_ptr->below_ptr;
    }
    printf("|-----BOTTOM\n");
}

void freeStack(Stack *stack_ptr){
    if(stack_ptr->height == 0){ return; }
    while(stack_ptr->height > 0){
        pop(stack_ptr);
    }
}

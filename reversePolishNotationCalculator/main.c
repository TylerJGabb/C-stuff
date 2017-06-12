#include "stackHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


float longToFloat(long x){
    int y = x;
    float z = y;
    return z;
}

int main(){
    char E[] = "SYNTAX ERROR";
	Stack S;
    char *line_ptr = NULL;
    size_t line_max = 0;
    ssize_t line_len;
    char *delim = " ";
    char *token;
    char *string_part;
    long ret;
    long val1,val2;
    int Eflag; 

    while((line_len = getline(&line_ptr,&line_max,stdin)) > 1){
        StackInit(&S);
        Eflag = 0;
        //printf("line_ptr = \'%s\'\n",line_ptr);
        token = strtok(line_ptr,delim);
        while(token != NULL){
            //printf("TOKEN %s\n",token);
            if(strcmp(token,"*\n") == 0 || strcmp(token,"*") == 0){
                if(S.height < 2){
                    Eflag = 1;
                    break;
                }
                val2 = pop(&S);
                val1 = pop(&S);
                push(&S,val1*val2);
            }
            else if(strcmp(token,"+\n") == 0 || strcmp(token,"+") == 0){
                if(S.height < 2){
                    Eflag = 1;
                    break;
                }
                val2 = pop(&S);
                val1 = pop(&S);
                push(&S,val1+val2);
            }
            else if(strcmp(token,"-\n") == 0 || strcmp(token,"-") == 0){
                if(S.height < 2){
                    Eflag = 1;
                    break;
                }
                val2 = pop(&S);
                val1 = pop(&S);
                push(&S,val1-val2);
            }

            else if(strcmp(token,"/\n") == 0 || strcmp(token,"/") == 0){
                if(S.height < 2){
                    Eflag = 1;
                    break;
                }
                if((val2 = pop(&S)) == 0){
                    printf("DIVZERO ERROR\n");
                    Eflag = 1;
                    break;
                }
                val1 = pop(&S);
                push(&S,val1/val2);
            }
            else{

                ret = strtol(token,&string_part,10);/////////////////////////////

                if(ret == 0 && !(strcmp(string_part,"") == 0 || strcmp(string_part,"\n") == 0)){
                    Eflag = 1;
                    break;
                }
                push(&S,ret);  
            }
            token = strtok(NULL,delim);
        }
        if(S.height != 1 || Eflag == 1){
            printf("6%s\n",E);
            freeStack(&S);
            continue;
        }
        printf(" = %ld\n",S.top_ptr->val);
        pop(&S);    
    }
    free(line_ptr);
	return 0;
}

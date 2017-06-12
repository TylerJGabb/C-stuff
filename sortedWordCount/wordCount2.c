#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "LinkedList.h"
#define printLoc(x) printf("LOCATION: %p\n",&x);

LL DB;

void DBinit(LL *newLL){
	newLL->head_ptr = NULL;
	newLL->tail_ptr = NULL;
	newLL->length = 0;
}


//adds a node to the end of the LL.
void printTopLL(LL *LL_ptr, int top){
    int iter = 0;
	Node *curr = LL_ptr->head_ptr;
	printf("WORD : COUNT\n");
	while(curr != NULL){
		printf("%s:%d\n",curr->word,curr->count);
		curr = (*curr).next_ptr; //same as curr->next_ptr but this notation helps me for now;
        iter++;
        if (iter == top){break;}
	}
	printf("---------------------------------------------------------\n");
}

//The adress of the variable read into append() is always the same,
//sp we have to pass in an adress to get around this.
//has to do with append's stack vs main's stack. 
void append(LL *DB, Node *node_ptr){
	//printLoc(node_ptr);
	if(DB->length == 0){
		DB->head_ptr = node_ptr;
		DB->tail_ptr = node_ptr;
		node_ptr->next_ptr = NULL;;
		DB->length++;
	}
	else{
	DB->tail_ptr->next_ptr = node_ptr;
	DB->tail_ptr = node_ptr;
	node_ptr->next_ptr = NULL;;
	DB->length++;
	}

}

int DBcontains(char *word){
	Node *curr = DB.head_ptr;
	while(curr != NULL){
		if(strcmp(curr->word,word) == 0){
			return 1;
		}
		curr = curr->next_ptr;
	}
	return 0;
}

void addToDB(char *word){
	if(!DBcontains(word)){
		Node *node_ptr = (Node *)malloc(sizeof(Node));
		node_ptr->word = strdup(word);
        node_ptr->count = 1;
		append(&DB,node_ptr);
        //free(word);
	}
	else{//word is in DB
		Node *curr = DB.head_ptr;
		while (curr != NULL){
			if (strcmp(curr->word,word) == 0){
				curr->count++;
				break;
			} 
			curr = curr->next_ptr;
		}

	}
}

void rmFromHD(LL *someLL_ptr){
    assert(someLL_ptr->length > 0);
	someLL_ptr->head_ptr = someLL_ptr->head_ptr->next_ptr;
	someLL_ptr->length--;
}

void insertAfter(LL *LL_ptr, Node *node_ptr, Node *TBI_node_ptr){
	assert(!DBcontains(node_ptr->word));
    Node *curr_ptr = LL_ptr->head_ptr;
    while (curr_ptr->word != node_ptr->word){
        curr_ptr = curr_ptr->next_ptr;
    }
    Node *temp_node_ptr = curr_ptr;
    Node *next_ptr = curr_ptr->next_ptr;
    temp_node_ptr->next_ptr = TBI_node_ptr;
    TBI_node_ptr->next_ptr = next_ptr;
    LL_ptr->length++;
}

//careful, don't add a node that is already in the list....
//some undefined behavior as of yet. 
void addToFront(LL *LL_ptr, Node *TBAdd_ptr){
    TBAdd_ptr->next_ptr = LL_ptr->head_ptr;
    LL_ptr->head_ptr = TBAdd_ptr;
    LL_ptr->length++;
}


//insertion sort method on LinkedList.
LL sortDB(){
	LL SORTED;
	DBinit(&SORTED);
	while(DB.length > 0){
		Node *TBI_ptr = DB.head_ptr;
		rmFromHD(&DB);
		if(SORTED.length == 0){ append(&SORTED,TBI_ptr); }
		else if (SORTED.length == 1){
			if(TBI_ptr->count < SORTED.head_ptr->count) { append(&SORTED,TBI_ptr); }
            else  { addToFront(&SORTED,TBI_ptr); }
		}
        else{//we need to move through the list and find the first position where, curr.count <= TBI.count < next.count
             //or    curr.count < TBI.count && curr->next_ptr == NULL;
            if (TBI_ptr->count >= SORTED.head_ptr->count) {
                addToFront(&SORTED,TBI_ptr);
                continue;
            }
            Node *curr_ptr = SORTED.head_ptr;
            Node *next_ptr = curr_ptr->next_ptr;
            //RECALL TBI_ptr is ptr to node to be inserted!
            while(1){//DANGEROUS TYLER! BAD TYLER!~~~!~!~~!!~~!~!~!~!!~!~~!
                if (next_ptr == NULL){
                    append(&SORTED,TBI_ptr);
                    break;
                }
                if(curr_ptr->count >= TBI_ptr->count && TBI_ptr->count > next_ptr->count){
                    insertAfter(&SORTED,curr_ptr,TBI_ptr);
                    break;
                }
                curr_ptr = next_ptr;
                next_ptr = next_ptr->next_ptr;
            }
        }
	}
    return SORTED;
}




//tests if a characyer is alphabetic 
int isalphac(char c){
    return (c <= 122 && c >= 97) || (c <= 90 && c >= 65);
}

//tests if a string is alphabetic
int isalphas(char *s){
    char *ptr;
    for(ptr = s; *ptr != '\0'; ptr++){
        if(!isalphac(*ptr)){
            return 0;}
    }
    return 1;
}

//strips the leading nonalphabetical characters by moving the pointer to the first place
//where an alphabetica character is, and returning that moved pointer
char *stripLeading(char *S){
    if(*S == '\0'){return S;}
    while(!isalphac(*S) && *S != '\0'){
        //printf("Removed %c\n",*S);
            S++;}
    return S;
    
}

//strips the trailing nonalphabetical characters of a string by moving back from the end
//and placing a null at the last encountered nonalphabetical character
//does not return anything, just mutates that string.
char *stripTrailing(char *S){
    if(*S == '\0') { return S;}
    char *ptr = S + strlen(S) - 1;
    while(!isalphac(*ptr)){ptr--;}
    ptr+=1;
    *ptr = '\0';
    return S;
}

//calms the text down, by moving through the string, and changing any capital alphabetical
//letters to lowercase
//returns the same String that was given, but this is not necessary, since this function
//changes the contents of the memory occupied by the string. 
char *calmDown(char *S){
    char *ptr = S;
    while(*ptr != '\0'){
        *ptr = tolower(*ptr);
        ptr++;
    }
    return S;
}

void freedom(LL *LL_ptr){
    //printf("ASDUFHSDFIOHJSDFIOHJ");
    Node *curr_ptr = LL_ptr->head_ptr;
    while (curr_ptr != NULL){
        Node *next_ptr = curr_ptr->next_ptr;
        //printf("Freeing locationL: %p\n",curr_ptr);
        free(curr_ptr->word);
        free(curr_ptr);
        curr_ptr = next_ptr;
    }
}

//cleans the word by calling all three cleaning functions, and returning it. 
char *cleanWord(char *word){ 
    word = stripLeading(word);
    stripTrailing(word);
    calmDown(word);
    return word;
}

int main(int argc, char *argv[]){


	DBinit(&DB);
      
	char buffer[1024];
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        printf("CAN NOT OPEN FILE\n");
        exit(1);
    }
    while(fscanf(fp,"%s",buffer) > 0){
        //printf("INCOMING: %s\n",buffer);
        char *ptr = buffer;
        ptr = cleanWord(ptr);
        //printf("CLEANED: \'%s\'\n",ptr);
        if(strcmp(ptr,"") == 0){
            //printf("IGNORING EMPTY STRING\n");
            continue;
        }
        addToDB(ptr);
    }
    
    


    //addToDB(strdup("H"));
    //printTopLL(&DB,10);
    LL SORTED;
    SORTED = sortDB();
    printf("~~~~~~~~~~~\n");
    printTopLL(&SORTED,strlen(argv[2]));
    printf("~!~!~!~!~!~!\n");
    freedom(&SORTED);
    printf("^^!^^!^^!^^!^^!^^!\n");
    return 0;





}
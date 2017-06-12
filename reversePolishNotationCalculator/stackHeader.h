/*
 *Header for stack datastructure
 */
#define p(S) printf("top = %p, bottom = %p, height = %d\n",S.top_ptr,S.bottom_ptr,S.height)

typedef struct Token{
    long val;
    struct Token *below_ptr;
} Token;

typedef struct Stack{
    struct Token *bottom_ptr;
    struct Token *top_ptr;
    int height;
} Stack;


  

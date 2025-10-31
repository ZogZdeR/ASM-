#ifndef STACK_FUNCTIONS
#define STACK_FUNCTIONS

#include <assert.h>  
#include <cstdlib>
#include <stdio.h>

#include "colour.hpp"

typedef int type;

static const int cannary_contraception = (int)0xDEADBABE;

enum Error
{
    ok = 0,
    struct_nullptr = 1,
    stack_nullptr = 2,
    bigger_size = 3,
    cannary_spoiled_beg = 4,
    cannary_spoiled_end = 5,
    pop_size_null = 6
};

struct Stack_stucture
{
    size_t size;
    size_t capacity;
    type *Stack;
};

Error stack_initialiser (size_t capacity, Stack_stucture *structure);
Error verify (Stack_stucture *structure);
void Push (Stack_stucture *structure, type a);
type Pop (Stack_stucture *structure);
Stack_stucture* destructor (Stack_stucture *structure);
void Dump (Stack_stucture *structure, Error err);
void print_error (Error err);
void Stack_print (Stack_stucture *structure);

void Add (Stack_stucture *structure);
void Sub (Stack_stucture *structure);
void Mul (Stack_stucture *structure);
void Div (Stack_stucture *structure);
void Out (Stack_stucture *structure);


#endif // STACK_FUNCTIONS




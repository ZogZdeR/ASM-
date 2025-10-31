#include "stack_functions.hpp"

Error stack_initialiser (size_t capacity, Stack_stucture *structure)
{
    if (structure == NULL) return struct_nullptr;
    structure->capacity = capacity;
    structure->size = 0;
    structure->Stack = (type*)calloc (capacity + 2, sizeof (size_t));
    if (structure->Stack == NULL) return stack_nullptr;
    structure->Stack[0] = cannary_contraception;
    structure->Stack[capacity + 1] = cannary_contraception;
    return ok;
}

Error verify (Stack_stucture *structure)
{ 
    if (structure == NULL)
    {
        printf (red "Structure pointer is nullptr" normal "\n");
        return struct_nullptr;
    }
    if (structure->capacity < structure->size) 
    {
        printf (red "Error : capacity < size" normal "\n");
        return bigger_size;
    }
    if (structure->Stack == NULL)
    {
        printf (red "Stack ptr is nullptr" normal "\n");
        return stack_nullptr;
    }
    if (structure->Stack[0] != cannary_contraception)
    {
        printf (red "Cannary shield's first ellement has been changed" normal "\n");
        return cannary_spoiled_beg;
    }
    if (structure->Stack[structure->capacity + 1] != cannary_contraception)
    {
        printf (red "Cannary shield's last ellement has been changed" normal "\n");
        return cannary_spoiled_end;
    }
    


    return ok;
}

void Push (Stack_stucture *structure, type a)
{
    Error err = verify (structure);
    if (err == ok)
    {
        if (structure->size < structure->capacity)
        {
            structure->size ++;
            structure->Stack[structure->size] = a;
        }
        else 
        {
            fprintf (stderr, "%lu%lu\n", structure->capacity, structure->size);
            structure->capacity = structure->capacity*2 + 2;
            fprintf (stderr, "%lu%lu\n", structure->capacity, structure->size);
            structure->Stack = (type *)realloc (structure->Stack, structure->capacity);
            fprintf (stderr, "%lu%lu\n", structure->capacity, structure->size);
            structure->size ++;
            structure->Stack[structure->size] = a;
        }
        err = verify (structure);
    }
    if (err != ok) 
    {
        print_error (err);
    }
}


type Pop (Stack_stucture *structure)
{
    Error err = verify (structure);
    if (structure->size == 0)
    {
        printf (red "Stack size = 0" normal "\n");
        err = pop_size_null;
    }
    if (err == ok)
    {
        structure->size --;
        err = verify (structure);
    }
    if (err != ok) 
    {
        print_error (err);
        return (type)0xDEADDEAD;
    }
    return structure->Stack[structure->size + 1];
}

Stack_stucture* destructor (Stack_stucture *structure)
{
    free(structure->Stack);
    structure->Stack = NULL;
    return NULL;
}
void Dump (Stack_stucture *structure, Error err)
{
    print_error (err);
    printf (blue "Capacity = %lu" normal "\n", structure->capacity);
    printf (blue "Size = %lu" normal "\n", structure->size);
    printf (blue "StackPtr = %p" normal "\n", structure->Stack);
    Stack_print (structure);
}

void print_error (Error err)
{
    printf (red "Error code is %lu" normal "\n"
        cyan "Error codes :" normal "\n"
        magenta "struct_nullptr = 1" normal "\n"
        magenta "stack_nullptr = 2" normal "\n"
        magenta "bigger_size = 3" normal "\n"
        magenta "cannary_spoiled_beg = 4" normal "\n"
        magenta "cannary_spoiled_end = 5" normal "\n"
        magenta  "pop_size_null = 6\n", (size_t)err);
}

//FIXME - StackPrint
void Stack_print (Stack_stucture *structure)
{
    for (size_t i = 1; i <= structure->size; i++)
    {
        printf ("%d ", structure->Stack[i]);
    }
}

void Add (Stack_stucture *structure)
{
    Error err = verify(structure);
    if (err == ok && structure -> size >= 2)
    {
    type a = 0;
    a = Pop (structure);
    a += Pop (structure);
    Push (structure, a);
    err = verify(structure);
    }
    if (err != ok) print_error (err);
}
void Sub (Stack_stucture *structure)
{
    Error err = verify(structure);
    if (err == ok && structure -> size >= 2)
    {
    type a = 0;
    a = Pop (structure) * (-1);
    a += Pop (structure);
    Push (structure, a);
    err = verify(structure);
    }
    if (err != ok) print_error (err);
}
void Mul (Stack_stucture *structure)
{
    Error err = verify(structure);
    if (err == ok && structure -> size >= 2)
    {
    type a = 0;
    a = Pop (structure);
    a *= Pop (structure);
    Push (structure, a);
    err = verify(structure);
    }
    if (err != ok) print_error (err);
}
void Div (Stack_stucture *structure)
{
    Error err = verify(structure);
    if (err == ok && structure -> size >= 2)
    {
    type a = 0;
    a = 1 / Pop (structure);
    a *= Pop (structure);
    Push (structure, a);
    err = verify(structure);
    }
    if (err != ok) print_error (err);
}
void Out (Stack_stucture *structure)
{
    Error err = verify(structure);
    if (err == ok && structure -> size > 0)
    {
    printf ("%d ", Pop(structure));
    err = verify(structure);
    }
    if (err != ok) print_error (err);
}


#include "processor_func.hpp"


size_t file_length (FILE *stream) 
{
    assert (stream != NULL);

    struct stat statbuf;
    fstat (fileno (stream), &statbuf); 
    return (size_t)statbuf.st_size;
}

processor_error processor_verify (processor_tools *Tools)
{
    processor_error error = OK;
    if (Tools == NULL) return NULL_PTR_STRUCTURE;
    if (Tools->Stack.Stack == NULL) error = (processor_error)(error | NULL_PTR_STACK);
    if (Tools->returning_Stack.Stack == NULL) error = (processor_error)(error | NULL_PTR_RETURNING_STACK);
    if (Tools->byte_code == NULL) error = (processor_error)(error | NULL_PTR_BYTE_CODE);
    if (verify (&Tools->Stack) != ok) error = (processor_error)(error | STACK_STRUCTURE_TROUBLE);
    if (verify (&Tools->returning_Stack) != ok) error = (processor_error)(error | RETURNING_STACK_STRUCTURE_TROUBLE);
    return error;
}

type *byte_code_initialiser (FILE *byte_code_stream)
{
    size_t byte_code_length = file_length (byte_code_stream) / sizeof(type);
    type *byte_code = (type *)calloc (byte_code_length, sizeof(type));
    if (byte_code == NULL)
    {
        fprintf (stderr, red "NULL allocation" normal "\n");
        return NULL;
    }
    if (fread (byte_code, sizeof (type), byte_code_length, byte_code_stream) != byte_code_length)
    {
        fprintf (stderr, red "Not every value in byte code is read" normal "\n");
        return NULL;
    }
    return byte_code;
}

processor_error constructor (processor_tools *Tools, Stack_stucture *Stack, Stack_stucture *Ret_stack, FILE *byte_code_stream)
{
    assert (Stack != NULL);
    assert (Ret_stack != NULL);
    Tools->Stack = *Stack;
    Tools->returning_Stack = *Ret_stack;
    Tools->IC = 0;
    type *byte_code = byte_code_initialiser (byte_code_stream);
    if (byte_code == NULL) return NULL_PTR_BYTE_CODE;
    Tools->byte_code = byte_code; 
    return OK;
}

void processor_destructor (processor_tools *Tools)
{
    free (Tools->byte_code);
    destructor (&Tools->Stack);
    destructor (&Tools->returning_Stack);
}

void processor_dump (processor_error error)
{
    printf (magenta "Programm errors\n" normal);
    if (error & NULL_PTR_STRUCTURE) printf (cyan "Processor's structure is nullpointer\n" normal);
    if (error & NULL_PTR_RETURNING_STACK) printf (cyan "Stack's structure is nullpointer\n" normal);
    if (error & STACK_STRUCTURE_TROUBLE) printf (cyan "Problem based on operating with stack\n" normal);
    if (error & RETURNING_STACK_STRUCTURE_TROUBLE) printf (cyan "Problem based on operating with ret-stack\n" normal);
    if (error & EXECUTE_ERROR) printf (cyan "Problem based on executing command\n" normal);
}

processor_error processor_run (processor_tools *Tools)
{
    processor_error error = OK;
    processor_verify (Tools);
    while (Tools->byte_code[Tools->IC] != HALT)
    {
        execute_command (Tools);
        processor_verify (Tools);
    }
    return error;
    
}

/*void byte_code_reader (processor_tools *Tools, type *byte_code, bool *flag)
{   
    processor_error error = OK;
    switch (byte_code[Tools->IC]){
        case 0: 
            my_halt(flag);
            break;
        case 1: 
            my_push (Tools, byte_code[++Tools->IC]);
            break;
        case 2: 
            my_add (Tools);
            break;
        case 3: 
            my_sub (Tools);
            break;
        case 4: 
            my_mul (Tools);
            break;
        case 5: 
            my_div (Tools);
            break;
        case 6: 
            my_out (Tools);
            break;
        case 7: 
            my_pushr (Tools);
            break;
        case 8: 
        my_popr (Tools);
        break;
        case 10: 
            my_jmp (Tools);
            break;
        case 11: 
            my_jb (Tools);
            break;
        case 12: 
            my_jbe (Tools);
            break;
        case 13: 
            my_ja (Tools);
            break;
        case 14: 
            my_jae (Tools);
            break;
        case 15: 
            my_je (Tools);
            break;
        case 16: 
            my_jne (Tools);
            break;
        case 21: 
            my_call (Tools);
            break;  
        case 22: 
            my_ret (Tools);
            break;
        case 31:
            my_pushm (Tools);
            break;
        case 32:
            my_popm (Tools);
            break;
        default:
            assert (0);
    }
}*/

void my_halt (bool *flag)
{
    *flag = false;
}
void my_push (processor_tools *Tools, type element)
{
    Push (&Tools->Stack, element);
    Tools->IC += 2;
}
void my_add (processor_tools *Tools)
{
    Add (&Tools->Stack);
    Tools->IC ++;
}
void my_sub (processor_tools *Tools)
{
    Sub (&Tools->Stack);
    Tools->IC ++;
}
void my_mul (processor_tools *Tools)
{
    Mul (&Tools->Stack);
    Tools->IC ++;
}
void my_div (processor_tools *Tools)
{
    Div (&Tools->Stack);
    Tools->IC ++;
}
void my_out (processor_tools *Tools)
{
    Out (&Tools->Stack);
    Tools->IC ++;
}
void my_pushr (processor_tools *Tools)
{
    Tools->IC++;
    Push (&Tools->Stack, Tools->REGS[Tools->byte_code[Tools->IC]]);
    Tools->IC++;
}
void my_popr (processor_tools *Tools)
{
    Tools->IC ++;
    Tools->REGS[Tools->byte_code[Tools->IC]] = Pop(&Tools->Stack);
    Tools->IC++;
}
void my_jmp (processor_tools *Tools)
{
    Tools->IC++;
    Tools->IC = (size_t)Tools->byte_code[Tools->IC];
}
void my_jb (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num < second_num) 
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void my_jbe (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num <= second_num) 
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void my_ja (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num > second_num) 
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void my_jae (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num >= second_num) 
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void my_je (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num == second_num)
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void my_jne (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num != second_num) 
    {
        Tools->IC++;
        Tools->IC = (size_t)Tools->byte_code[Tools->IC];
    }
    else Tools->IC+=2;
}
void returning_stack_push (processor_tools *Tools, type element)
{
    Push (&Tools->returning_Stack, element);
}
type returning_stack_pop (processor_tools *Tools)
{
    return Pop (&Tools->returning_Stack);
}
void my_call (processor_tools *Tools)
{
    returning_stack_push (Tools, (type)Tools->IC + 2);
    my_jmp (Tools);
}
void my_ret (processor_tools *Tools)
{
    Tools->IC = (size_t)returning_stack_pop (Tools);
}
void my_pushm (processor_tools *Tools)
{
    my_push (Tools, Tools->Mem[Tools->REGS[Tools->byte_code[++Tools->IC]]]);
    Tools->IC++;
}
void my_popm (processor_tools *Tools)
{
    Tools->Mem[Tools->REGS[Tools->byte_code[++Tools->IC]]] = Pop (&Tools->Stack);
    Tools->IC ++;
}

processor_error execute_command (processor_tools *Tools)
{
    switch (Tools->byte_code[Tools->IC])
    {
        case PUSH:
            my_push (Tools, Tools->byte_code[Tools->IC + 1]);
            return OK;
        case ADD:
            my_add(Tools);
            return OK;
        case SUB:
            my_sub (Tools);
            return OK;
        case MUL:
            my_mul (Tools);
            return OK;
        case DIV:
            my_div(Tools);
            return OK;
        case OUT:
            my_out (Tools);
            return OK;
        case PUSHR:
            my_pushr (Tools);
            return OK;
        case POPR:
            my_popr (Tools);
            return OK;
        case JMP:
            my_jmp (Tools);
            return OK;
        case JB:
            my_jmp (Tools);
            return OK;
        case JBE:
            my_jbe (Tools);
            return OK;
        case JA:
            my_ja (Tools);
            return OK;
        case JAE: 
            my_jae (Tools);
            return OK;
        case JE:
            my_je (Tools);
            return OK;
        case JNE:
            my_jne (Tools);
            return OK;
        case CALL:
            my_call (Tools);
            break;
        case RET:
            my_ret (Tools);
            return OK;
        case PUSHM:
            my_pushm (Tools);
            return OK;
        case POPM:
            my_popm (Tools);
            return OK;
        default:
            return EXECUTE_ERROR;
    }
    return EXECUTE_ERROR;
}


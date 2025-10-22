#include "processor_func.hpp"
// FIXME - assert
size_t int_counter (char *buffer)
{
    assert (buffer != NULL);
    size_t counter = 0;
    while (buffer[counter] != '\0')
    {
        if (buffer[counter] == ' ') counter ++;
    }
   return counter + 1;
}

type new_atoi (const char *Source)
{
    type resoult = 0;
    type deg = 1;
    type iterator = 0;
    while (Source[iterator] != '\0' && Source[iterator] != ' ')
    {
        resoult += deg * (Source[iterator] - '0');
        iterator++;
        deg *= 10;
    }
    return resoult;
}

void DisASM (type *byte_code, char *buffer)
{
    char const *every_int = (char const *)buffer;
    size_t iterator = 0;
    while (my_strchr(every_int, ' ') != NULL)
    {
        byte_code[iterator] = new_atoi (every_int);
        every_int = my_strchr (every_int , ' ') + 1;
    }
    byte_code[iterator] = new_atoi (every_int);
}

int byte_code_reader (processor_tools *Tools, type *byte_code, bool *flag)
{   
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

}

void my_halt (bool *flag)
{
    *flag = false;
}
void my_push (processor_tools *Tools, type element)
{
    Push (&Tools->Stack, element);
}
void my_add (processor_tools *Tools)
{
    Add (&Tools->Stack);
}
void my_sub (processor_tools *Tools)
{
    Add (&Tools->Stack);
}
void my_mul (processor_tools *Tools)
{
    Mul (&Tools->Stack);
}
void my_div (processor_tools *Tools)
{
    Div (&Tools->Stack);
}
void my_sub (processor_tools *Tools)
{
    Add (&Tools->Stack);
}
void my_out (processor_tools *Tools)
{
    Out (&Tools->Stack);
}
void my_pushr (processor_tools *Tools)
{
    Push (&Tools->Stack, Tools->REGS[++Tools->IC]);
    Tools->IC++;
}
void my_popr (processor_tools *Tools)
{
    Tools->REGS[++Tools->IC] = Pop(&Tools->Stack);
    Tools->IC++;
}
void my_popr (processor_tools *Tools)
{
    Tools->REGS[++Tools->IC] = Pop(&Tools->Stack);
    Tools->IC++;
}
void my_jmp (processor_tools *Tools)
{
    Tools->IC = Tools->byte_code[++Tools->IC];
}
void my_jb (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num < second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC++;
}
void my_jbe (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num <= second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC++;
}
void my_ja (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num > second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC++;
}
void my_jae (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num >= second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC++;
}
void my_je (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num == second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC++;
}
void my_jne (processor_tools *Tools)
{
    type first_num = 0;
    type second_num = 0;
    second_num = Pop (&Tools->Stack);
    first_num = Pop (&Tools->Stack);
    if (first_num != second_num) Tools->IC = Tools->byte_code[++Tools->IC];
    else Tools->IC;
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
    returning_stack_push (Tools, Tools->IC + 2);
    my_jmp (Tools);
}
void my_ret (processor_tools *Tools)
{
    Tools->IC = returning_stack_pop (Tools);
}
void my_pushm (processor_tools *Tools)
{
    my_push (Tools, Tools->REGS[Tools->byte_code[++Tools->IC]]);
    Tools->IC++;
}
void my_popm (processor_tools *Tools)
{
    Tools->REGS[Tools->byte_code[++Tools->IC]] = Pop (&Tools->Stack);
}




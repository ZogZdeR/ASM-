#ifndef PROCESSOR_FUNC
#define PROCESSOR_FUNC

#include "string_functions.hpp"
#include "stack_functions.hpp"
#include "common_list.hpp"

#include <sys/stat.h>
#include <stdio.h>
#include <limits.h>

#define Mem_size_x 10
#define REGS_num 4

enum processor_error
{
    OK = 0,
    NULL_PTR_STRUCTURE = 1,
    NULL_PTR_STACK = 2,
    NULL_PTR_RETURNING_STACK = 4,
    NULL_PTR_BYTE_CODE = 8,  
    STACK_STRUCTURE_TROUBLE = 16,
    RETURNING_STACK_STRUCTURE_TROUBLE = 32,
    EXECUTE_ERROR = 64,
    ALL_ERRORS = INT_MAX
};

struct processor_tools
{
    Stack_stucture Stack;
    Stack_stucture returning_Stack;
    type *byte_code;
    size_t IC;
    type REGS[REGS_num] = {-1, -1, -1, -1}; // RA = 1, RB = 2, RC = 3, RD = 4
    type Mem [Mem_size_x*Mem_size_x];
};


size_t file_length (FILE *stream);
type *byte_code_initialiser (FILE *byte_code_stream);
processor_error processor_verify (processor_tools *Tools);
processor_error constructor (processor_tools *Tools, Stack_stucture *Stack, Stack_stucture *Ret_stack, FILE *byte_code_stream);
processor_error execute_command (processor_tools *Tools);
void processor_destructor (processor_tools *Tools);
void processor_dump (processor_error error);
processor_error processor_run (processor_tools *Tools);
void byte_code_reader (processor_tools *Tools, type *byte_code, bool *flag);
void my_halt (bool *flag);
void my_push (processor_tools *Tools, type element);
void my_add (processor_tools *Tools);
void my_sub (processor_tools *Tools);
void my_mul (processor_tools *Tools);
void my_div (processor_tools *Tools);
void my_out (processor_tools *Tools);
void my_pushr (processor_tools *Tools);
void my_popr (processor_tools *Tools);
void my_jmp (processor_tools *Tools);
void my_jb (processor_tools *Tools);
void my_jbe (processor_tools *Tools);
void my_ja (processor_tools *Tools);
void my_jae (processor_tools *Tools);
void my_je (processor_tools *Tools);
void my_jne (processor_tools *Tools);
void returning_stack_push (processor_tools *Tools, type element);
type returning_stack_pop (processor_tools *Tools);
void my_call (processor_tools *Tools);
void my_ret (processor_tools *Tools);
void my_pushm (processor_tools *Tools);
void my_popm (processor_tools *Tools);



#endif // PROCESSOR_FUNC
#ifndef PROCESSOR_FUNC
#define PROCESSOR_FUNC

#include "string_functions.hpp"
#include "stack_functions.hpp"
#include "ASM_func.hpp"

#include <stdio.h>

struct processor_tools
{
    Stack_stucture Stack;
    type *byte_code;
    size_t IC;
    type REGS[11] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // RA = 1, RB = 2, RC = 3, RD = 4, Rback = 5, RM = 6
};

size_t int_counter (char *buffer);
type new_atoi (const char *Source);
void DisASM (type *byte_code, char *buffer);


#endif // PROCESSOR_FUNC
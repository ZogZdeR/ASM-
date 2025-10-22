#ifndef ASM_FUNC
#define ASM_FUNC


#include "stack_functions.hpp"
#include "string_functions.hpp"

#include <sys/stat.h>
#include <stdio.h>
#include <cstdlib>

enum command
{
    HALT = 0,
    PUSH = 1,
    ADD = 2,
    SUB = 3,
    MUL = 4,
    DIV = 5,
    OUT = 6,
    PUSHR = 7,
    POPR = 8,
    JMP = 10,
    JB = 11,
    JBE = 12,
    JA = 13,
    JAE = 14,
    JE = 15,
    JNE = 16,
    CALL = 21,
    RET = 22,
    PUSHM = 31,
    POPM = 32,
    LABLE = -1,
    ERROR = -2
};

size_t file_length (FILE *stream);
int file_to_buffer (FILE *stream, char *buffer);
void ptr_array_maker (char **ptr_array, char *buffer, FILE *stream);
size_t str_counter (char *buffer);
size_t int_counter (char *buffer);
void byte_code_maker (char **ptr_array, int *byte_code, size_t quantity, type *lable);
type ASM_R (char *string);
type paste_value (char *string);
type ASM_JMP (char *exect_string, int *lable_array);
int new_strcmp (const char *First, const char *Second);
command command_determination (char *string);
void add_command (int *byte_code, command given_command, size_t j);
void set_lable (int *lable_array, char *lable_string, size_t j);

#endif // ASM_FUNC
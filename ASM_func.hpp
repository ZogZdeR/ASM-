#ifndef ASM_FUNC
#define ASM_FUNC

#include "common_list.hpp"
#include "stack_functions.hpp"
#include "string_functions.hpp"

#include <sys/stat.h>
#include <stdio.h>
#include <cstdlib>

typedef int type;

char const square_scobe = '[';
char const square_scobe_back = ']';
char const colon = ':';
static char const *RX_names[] = {"RA", "RB", "RC", "RD"};
int const R_quantity = 4;

// КОНСТАНТЫ КОМАНД
static char const *c_HALT = "HALT";
static char const *c_PUSH = "PUSH";
static char const *c_ADD = "ADD";
static char const *c_SUB = "SUB";
static char const *c_MUL = "MUL";
static char const *c_DIV = "DIV";
static char const *c_OUT = "OUT";
static char const *c_PUSHR = "PUSHR";
static char const *c_POPR = "POPR"; 
static char const *c_JMP = "JMP";
static char const *c_JB = "JB";
static char const *c_JBE = "JBE";
static char const *c_JA = "JA";
static char const *c_JAE = "JAE";
static char const *c_JE = "JE";
static char const *c_JNE = "JNE";
static char const *c_CALL = "CALL";
static char const *c_RET = "RET";
static char const *c_PUSHM = "PUSHM";
static char const *c_POPM = "POPM";


size_t file_length (FILE *stream);
int file_to_buffer (FILE *stream, char *buffer);
void ptr_array_maker (char **ptr_array, char *buffer, FILE *stream);
size_t str_counter (char *buffer);
size_t int_counter (char *buffer);
void byte_code_maker (char **ptr_array, int *byte_code, size_t quantity, type *lable);
type ASM_R (char const *string);
type paste_value (char *string);
type ASM_JMP (char *exect_string, int *lable_array);
int new_strcmp (const char *First, const char *Second);
command command_determination (char *string);
void add_command (int *byte_code, command given_command, size_t j);
void set_lable (int *lable_array, char *lable_string, size_t j);
int new_strlen (const char * Arr);
int new_atoi (const char *Source);
type ASM_M (char *exect_string);

#endif // ASM_FUNC
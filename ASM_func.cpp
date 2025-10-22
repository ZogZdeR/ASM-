#include "ASM_func.hpp"

size_t file_length (FILE *stream) 
{
    assert (stream != NULL);

    struct stat statbuf;
    fstat (fileno (stream), &statbuf); // FIXME: ИСправить с теста на онегина
    return (size_t)statbuf.st_size;
}

int file_to_buffer (FILE *stream, char *buffer)
{
    assert (stream != NULL);
    assert (buffer != NULL);

    size_t length = file_length (stream);
    size_t check = fread (buffer, sizeof (char), length,  stream);
    if (check == length) 
    {
        buffer [length] = '\0';
        return 1;
    }
    return 0;
}

void ptr_array_maker (char **ptr_array, char *buffer, FILE *stream)
{
    assert (ptr_array != NULL);
    assert (buffer != NULL);
    assert (stream != NULL);

    size_t str_num = 0;
    size_t max_l = file_length (stream) + 1; 
    ptr_array[str_num] = buffer;

    for (size_t i = 1; i < max_l; i++)
    {       
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            if (i != max_l - 1)
            {
                str_num++;
                ptr_array[str_num] = &buffer[i+1];
            }  
        }
    }
}

size_t str_counter (char *buffer)
{
    assert (buffer != NULL);

    size_t endl_quantity = 0;
    int c = '\\';
    int i = 0;
    while (c != '\0')
    {
        c = buffer [i];
        if (c == '\n') endl_quantity ++;
        i++;
    }
    return endl_quantity +  1;
}

size_t int_counter (char *buffer)
{
    assert (buffer != NULL);
    size_t counter = 0;
    while (buffer[counter] != '\0')
    {
        if (buffer[counter] == ' ' || buffer[counter == '\n']) counter ++;
    }
   return counter + 1;
}

void byte_code_maker (char **ptr_array, int *byte_code, size_t quantity, type *lable_array)
{   
    size_t j = 0;
    for (size_t i = 0; i < quantity; i++)
    {
        command given_command = command_determination(ptr_array[i]);
        if (given_command == LABLE) set_lable (lable_array, ptr_array[i], j);
        else if (given_command == PUSH || given_command == PUSHR || given_command == POPR || 
            (given_command >= 10 && given_command <= 16) || given_command == CALL || given_command == PUSHM ||
            // FIXME - 10 and 16 to const and function for checking if command needs argument
            given_command == POPM) j+= 2;
        else j++;
    }

    j = 0;

    for (size_t i = 0; i < quantity; i++)
    {
        command given_command = command_determination (ptr_array[i]);
        if (given_command == ERROR) // Remove before publish
        {
            fprintf (stderr, "command determination func fault\n");
            assert (0);
        }
        if (given_command != LABLE)
        {
            add_command (byte_code, given_command, j);
            j++;
            fprintf(stderr, "\n");
        }
        else set_lable (lable_array, ptr_array[i], j);
        
        // FIXME - switch
        if (given_command == PUSH)
        {
            byte_code[j] = paste_value (ptr_array[i]);
            j++;
        }
        else if (given_command == PUSHR || given_command == POPR)
        {
            byte_code[j] = ASM_R (ptr_array[i]);
            j++;
        }
        else if ((given_command >= 10 && given_command <= 16) || given_command == CALL)
        {// FIXME - 10 and 16
            byte_code[j] = ASM_JMP (ptr_array[i], lable_array);
            j++;
        }
    }
} 



type paste_value (char *exect_string)
{
    return my_atoi(my_strchr(exect_string, ' ') + 1);
}

type ASM_R (char *exect_string)
{
    char const *value_ptr = my_strchr(exect_string, ' ') + 1;
    // FIXME - array of names of registers and return index of register in this array
    if (new_strcmp (value_ptr, "RA")) return 1;
    if (new_strcmp (value_ptr, "RB")) return 2;
    if (new_strcmp (value_ptr, "RC")) return 3;
    if (new_strcmp (value_ptr, "RD")) return 4;
    assert (0);
}

type ASM_JMP (char *exect_string, int *lable_array)
{// FIXME - ':' to const
    if (my_strchr(exect_string, ' ')[1] == ':') return lable_array[my_atoi(my_strchr(exect_string, ' ') + 2)];
    else return my_atoi(my_strchr(exect_string, ' ') + 1);
}


int new_strcmp (const char *First, const char *Second)
{
    assert (First != NULL);
    assert (Second != NULL);

    int i = 0; 
    while ((First[i] != ' ' && Second [i] != ' ') || (First[i] != '\0' && Second [i] != '\0'))
    {  
        if (First[i] != Second[i]) return 0; 
        if (Second[i] == '\0') return 1;
        i++;
    }
    if (Second[i] == '\0' && First[i] == ' ') return 1;
    return 0;
} 

 command command_determination (char *string)
 {; // FIXME - command to const
    if (new_strcmp (string, "PUSH")) {
        fprintf(stderr, "PUSH");
        return PUSH;
    }
    if (new_strcmp (string, "ADD"))  {
        fprintf(stderr, "ADD");
        return ADD;
    }
    if (new_strcmp (string, "SUB"))  {
        fprintf(stderr, "SUB");
        return SUB;
    }
    if (new_strcmp (string, "MUL"))  {
        fprintf(stderr, "MUL");
        return MUL;
    }
    if (new_strcmp (string, "DIV"))  {
        fprintf(stderr, "DIV");
        return DIV;
    }
    if (new_strcmp (string, "OUT"))  {
        fprintf(stderr, "OUT");
        return OUT;
    }
    if (new_strcmp (string, "HALT"))  {
        fprintf(stderr, "HALT");
        return HALT;
    }
    if (new_strcmp (string, "PUSHR"))  {
        fprintf(stderr, "PUSHR");
        return PUSHR;
    }
    if (new_strcmp (string, "POPR"))  {
        fprintf(stderr, "POPR");
        return POPR;
    }
    if (new_strcmp (string, "JMP"))  {
        fprintf(stderr, "JMP");
        return JMP;
    }
    if (new_strcmp (string, "JB"))  {
        fprintf(stderr, "JB");
        return JB;
    }
    if (new_strcmp (string, "JBE"))  {
        fprintf(stderr, "JBE");
        return JBE;
    }
    if (new_strcmp (string, "JA"))  {
        fprintf(stderr, "JA");
        return JA;
    }
    if (new_strcmp (string, "JAE"))  {
        fprintf(stderr, "JAE");
        return JAE;
    }
    if (new_strcmp (string, "JE"))  {
        fprintf(stderr, "JE");
        return JE;
    }
    if (new_strcmp (string, "JNE"))  {
        fprintf(stderr, "JNE");
        return JNE;
    }
    if (new_strcmp (string, "CALL"))  {
        fprintf(stderr, "CALL");
        return CALL;
    }
    if (new_strcmp (string, "RET"))  {
        fprintf(stderr, "RET");
        return RET;
    }
    if(string[0] == ':') // LABLE
    {
        return LABLE;
    }
    return ERROR;
 }

void add_command (int *byte_code, command given_command, size_t j)
{
    // FIXME - byte_code[j] = given_command;
    switch (given_command)
    {
        case HALT: 
            byte_code[j] = 0;
            break;
        case PUSH: 
            byte_code[j] = 1;
            break;
        case ADD: 
            byte_code[j] = 2;
            break;
        case SUB: 
            byte_code[j] = 3;
            break;
        case MUL: 
            byte_code[j] = 4;
            break;
        case DIV: 
            byte_code[j] = 5;
            break;
        case OUT: 
            byte_code[j] = 6;
            break;
        case PUSHR: 
            byte_code[j] = 7;
            break;
        case POPR: 
            byte_code[j] = 8;
            break;
        case JMP: 
            byte_code[j] = 10;
            break;
        case JB: 
            byte_code[j] = 11;
            break;
        case JBE: 
            byte_code[j] = 12;
            break;
        case JA: 
            byte_code[j] = 13;
            break;
        case JAE: 
            byte_code[j] = 14;
            break;
        case JE: 
            byte_code[j] = 15;
            break;
        case JNE: 
            byte_code[j] = 16;
            break;
        case CALL: 
            byte_code[j] = 21;
            break;
        case RET: 
            byte_code[j] = 22;
            break;
        case PUSHM: 
            byte_code[j] = 31;
            break;
        case POPM: 
            byte_code[j] = 32;
            break;
        default:
            assert (0);
            break;
    } 
}

void set_lable (int *lable_array, char *lable_string, size_t j)
{
    lable_array[my_atoi(&lable_string[1])] = (int)j;
}
 
    

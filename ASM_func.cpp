#include "ASM_func.hpp"

size_t file_length (FILE *stream) 
{
    assert (stream != NULL);

    struct stat statbuf;
    fstat (fileno (stream), &statbuf); 
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
            (given_command >= JMP && given_command <= JNE) || given_command == CALL || given_command == PUSHM ||
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
        
        switch ((int)given_command)
        {
            case PUSH:
                byte_code[j] = paste_value (ptr_array[i]);
                j++;
                break;
            case PUSHR:
            case POPR:
                byte_code[j] = ASM_R (ptr_array[i]);
                j++;
                break;
            case JA:
            case JAE:
            case JB:
            case JBE:
            case JMP:
            case JE:
            case JNE:
            case CALL:
                byte_code[j] = ASM_JMP (ptr_array[i], lable_array);
                j++;
                break;
            case PUSHM:
            case POPM:
                byte_code[j] = ASM_R (ptr_array[i]);
                j++;
                break;
            default:
                break;
        }
    }
} 



type paste_value (char *exect_string)
{
    return my_atoi(my_strchr(exect_string, ' ') + 1);
}

type ASM_R (const char *exect_string)
{
    char const *value_ptr = my_strchr(exect_string, ' ') + 1;
    for (int i = 0; i < R_quantity; i++)
    {
        if (new_strcmp (value_ptr, RX_names[i])) return i;
    }
    assert (0);
}

type ASM_JMP (char *exect_string, int *lable_array)
{
    if (my_strchr(exect_string, ' ')[1] == colon) return lable_array[my_atoi(my_strchr(exect_string, ' ') + 2)];
    else return my_atoi(my_strchr(exect_string, ' ') + 1);
}

/*type ASM_M (char *exect_string)
{
    int i = 0;
    while (exect_string[i] != '\0')
    {
        if (exect_string[i] == square_scobe_back)
        {
            exect_string[i] = '\0';
            break;
        }
        i++; 
    }
    if (my_strchr(exect_string, ' ')[1] == square_scobe) return ASM_R(my_strchr(exect_string, ' ') + 2);
}*/

int new_strlen (const char * Arr)
{
    int size = 0;
    while (Arr[size] != '\0')
    {
        size++;
    }
    return size;
}

int new_atoi (const char *Source)
{
    int resoult = 0;
    int len = new_strlen(Source);
    int deg = 1;
    for (int i = len - 1; i >= 0; i--)
    {
        if (Source[i] != square_scobe_back && Source[i] != square_scobe)
        {
            resoult += deg * (Source[i] - '0');
            deg *= 10;
        } 
    }
    return resoult;
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
 {; 
    if (new_strcmp (string, c_PUSH)) {
        fprintf(stderr, "%s", c_PUSH);
        return PUSH;
    }
    if (new_strcmp (string, c_ADD))  {
        fprintf(stderr, "%s", c_ADD);
        return ADD;
    }
    if (new_strcmp (string, c_SUB))  {
        fprintf(stderr, "%s", c_SUB);
        return SUB;
    }
    if (new_strcmp (string, c_MUL))  {
        fprintf(stderr, "%s", c_MUL);
        return MUL;
    }
    if (new_strcmp (string, c_DIV))  {
        fprintf(stderr, "%s", c_DIV);
        return DIV;
    }
    if (new_strcmp (string, c_OUT))  {
        fprintf(stderr, "%s", c_OUT);
        return OUT;
    }
    if (new_strcmp (string, c_HALT))  {
        fprintf(stderr, "%s", c_HALT);
        return HALT;
    }
    if (new_strcmp (string, c_PUSHR))  {
        fprintf(stderr, "%s", c_PUSHR);
        return PUSHR;
    }
    if (new_strcmp (string, c_POPR))  {
        fprintf(stderr, "%s", c_POPR);
        return POPR;
    }
    if (new_strcmp (string, c_JMP))  {
        fprintf(stderr, "%s", c_JMP);
        return JMP;
    }
    if (new_strcmp (string, c_JB))  {
        fprintf(stderr, "%s", c_JB);
        return JB;
    }
    if (new_strcmp (string, c_JBE))  {
        fprintf(stderr, "%s", c_JBE);
        return JBE;
    }
    if (new_strcmp (string, c_JA))  {
        fprintf(stderr, "%s", c_JA);
        return JA;
    }
    if (new_strcmp (string, c_JAE))  {
        fprintf(stderr, "%s", c_JAE);
        return JAE;
    }
    if (new_strcmp (string, c_JE))  {
        fprintf(stderr, "%s", c_JE);
        return JE;
    }
    if (new_strcmp (string, c_JNE))  {
        fprintf(stderr, "%s", c_JNE);
        return JNE;
    }
    if (new_strcmp (string, c_CALL))  {
        fprintf(stderr, "%s", c_CALL);
        return CALL;
    }
    if (new_strcmp (string, c_RET))  {
        fprintf(stderr, "%s", c_RET);
        return RET;
    }
    if (new_strcmp (string, c_PUSHM))  {
        fprintf(stderr, "%s", c_PUSHM);
        return PUSHM;
    }
    if (new_strcmp (string, c_POPM))  {
        fprintf(stderr, "%s", c_POPM);
        return POPM;
    }
    if(string[0] == colon) // LABLE
    {
        return LABLE;
    }
    return ERROR;
 }

void add_command (int *byte_code, command given_command, size_t j)
{
    byte_code[j] = given_command; 
}

void set_lable (int *lable_array, char *lable_string, size_t j)
{
    lable_array[my_atoi(&lable_string[1])] = (int)j;
}
 
    

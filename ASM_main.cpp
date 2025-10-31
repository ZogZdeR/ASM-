#include "stack_functions.hpp"
#include "ASM_func.hpp"
#include "colour.hpp"

#include <stdio.h>
#include <cstdlib>

int main ()
{
    FILE *stream = fopen ("command.txt", "r");
    char *buffer = (char *)calloc (file_length (stream) + 1, sizeof(char)); // FIXME - null

    if (file_to_buffer (stream, buffer) == 0) 
    {
        printf (red "Something's gone wrong" normal "\n");
        printf (magenta "Programm is shutting down. You were glad to seen" normal "\n");
        return 0;
    }

    size_t quantity = str_counter(buffer);
    char **ptr_array = (char **)calloc (quantity , sizeof(char*));
    ptr_array_maker (ptr_array, buffer, stream);
    
    FILE *byte_code_stream = fopen ("byte_code.bin", "wb");
    int *byte_code = (int *)calloc (file_length (stream) / 3, sizeof(int));

    type lable_array[10] =  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // FIXME - const

    byte_code_maker (ptr_array, byte_code, quantity, lable_array);

    fwrite (byte_code, sizeof (int), file_length (stream) / 3, byte_code_stream);
    size_t element = 0;
    while  (byte_code[element] != 0 || byte_code[element + 1] != 0)
    {
        fprintf (stderr, "%d ", byte_code[element]);
        element ++; 
    }
    fprintf (stderr, "\n");

    free (byte_code);
    free (ptr_array);
    free (buffer);

    fclose (byte_code_stream);
    fclose (stream);

    return 0;   
}
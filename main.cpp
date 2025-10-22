#include <stdio.h>
#include <cstdlib>

#include "string_functions.hpp"
#include "colour.hpp"
#include "stack_functions.hpp"
#include "processor_func.hpp"

int main ()
{
    FILE *byte_code_stream = fopen ("byte_code.bin", "rb");
    assert (byte_code_stream != NULL);
    processor_tools Tools;
    stack_initialiser (100, &(Tools.Stack));
    Tools.IC = 0;
    size_t length = file_length (byte_code_stream) / sizeof(type);
    Tools.byte_code = (type *)calloc (length, sizeof(type)); // FIXME - null
    if (fread (Tools.byte_code, sizeof (type), length, byte_code_stream) != length)
    {
        fprintf (stderr, red "Not every value in byte code is read" normal "\n");
        return 0;
    }

    bool flag = true;
    while (flag)
    {


    }
    return 0;
}
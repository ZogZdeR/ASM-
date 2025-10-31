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
    Stack_stucture Stack = {};
    Stack_stucture Returning_Stack = {};
    Error serr = stack_initialiser(100, &Stack);
    if (serr != ok)
    {
        Dump(&Stack, serr);
        return 0;
    }
    Error rserr = stack_initialiser(10, &Returning_Stack);
    if (rserr != ok)
    {
        Dump(&Returning_Stack, rserr);
        return 0;
    }

    processor_tools Tools = {};
    processor_error state = constructor (&Tools, &Stack, &Returning_Stack, byte_code_stream);
    if (state != OK)
    {
        processor_dump (state);
        return 0;
    }
    state = processor_run (&Tools);
    if (state != OK) processor_dump (state);
    
    processor_destructor(&Tools);
    return 0;
}
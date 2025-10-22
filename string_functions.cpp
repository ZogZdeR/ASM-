#include "string_functions.hpp"


void my_getline (char *Source)
{
    int i = -1;
    do
    {
       i++;
      Source [i] = (char)getchar ();
    }
    while (Source[i] != EOF and Source[i] != '\n');
    Source [i] = '\0';
}

void my_puts (const char Arr[])
{
    for (int i = 0; Arr[i] != '\0'; i++)
    {
        putchar (Arr[i]);
    }
    putchar ('\n');
}

// FIXME const char*
const char * my_strchr (const char *Arr, char c)
{
    assert (Arr != NULL);
    assert (c != '\0');

    int i = 0;
    while (Arr[i] != '\0')
    {
        if (Arr[i] == c) return &(Arr[i]);
        i++;
    }
    return NULL;
}

int my_strlen (const char * Arr)
{
    int size = 0;
    while (Arr[size] != '\0')
    {
        size++;
    }
    return size;
}

void my_strcpy (const char *Original, char *Parody)
{
    assert (Original != NULL);
    assert (Parody != NULL);

    int i = 0;
    do
    {
        Parody[i] = Original[i];
        i++;
    }
    while (Original[i] != '\0');
    Parody [i] = '\0';
    
}

char *my_strcat (char *destination, const char *to_paste)
{
    int l = my_strlen (destination);  // номер эллемента массива, с когорого начнется to_paste
    int i = 0;
    while (i < my_strlen (to_paste))
    {
        destination[i + l] = to_paste[i];
        i++;
    }
    destination [i + l] = '\0';
    return destination;
}

int my_strcmp (const char *First, const char *Second)
{
    assert (First != NULL);
    assert (Second != NULL);

    int m = min (my_strlen (First), my_strlen (Second));
    int i = 0; 
    while (i < m)
    {
        if (First[i] > Second[i]) return 1;
        else if (First[i] < Second[i]) return -1;
        i++;
    }
    if (First[i] == '\0' and Second[i] == 0) return 0;
    else if (Second[i] == '\0') return 1;
    else return -1;
}

char *my_strdup (const char *Orig)
{
    assert (Orig != NULL);

    char *Copy = (char*) calloc((size_t)(my_strlen(Orig) + 1), sizeof(char));
    my_strcpy (Orig, Copy);
    return Copy; 
}

int min (int a, int b)
{
    if (a < b) return a;
    else return b;
}

void my_strncpy (const char *Original, char *Parody, int n)
{
    assert (Original != NULL);
    assert (Parody != NULL);
    assert (n >= 0);

    int i = 0;
    while (Original[i] != '\0' && i < n)
    {
        Parody[i] = Original[i];
        i++;
    }
    Parody [i] = '\0';    
}

char *my_strncat (char *destination, const char *to_paste, int n)
{
    int l = my_strlen (destination);  // номер эллемента массива, с когорого начнется to_paste
    int i = 0;
    while (i < my_strlen (to_paste) && i < n)
    {
        destination[i + l] = to_paste[i];
        i++;
    }
    destination [i + l] = '\0';
    return destination;
}

int my_atoi (const char *Source)
{
    int resoult = 0;
    int len = my_strlen(Source);
    int deg = 1;
    for (int i = len - 1; i >= 0; i--)
    {
       resoult += deg * (Source[i] - '0');
       deg *= 10; 
    }
    return resoult;
}

/*int my_atoi_beta (const char *Source)
{
    int resoult = 0;
    int iterator = 0;
    int deg = 1;
    while (Source[deg] != ' ' && Source[deg] != '\n')
    {
        deg *= 10;
    }
    deg /= 10;
    int step = deg;
    for (int i = 0; i <= deg; i++)
    {
        resoult += (Source[i] - '0') * step;
        step /= 10;
    }
    return resoult;
} */

char *my_fgets (char *input, int maxn, FILE *stream)
{
    assert (stream != NULL);
    int i = 0;
    input[i] = '\0';
    while (i < maxn and input[i] != EOF)
    {   
        input[i] = (char)fgetc (stream);
        if (input[i] != '\n' && input[i] != EOF) i++;
        else  if (input[i] == EOF)
        {
            input[i] = '\0';
            break;
        }
        else input [i] = '\0';
    }
    input[i] = '\0';
    return input;
}
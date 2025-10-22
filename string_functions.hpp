#ifndef SOME_FUNCTION
#define SOME_FUNCTION

#include <stdio.h>
#include <math.h>
# include <assert.h>


void my_getline (char *Source);
void my_puts (const char Arr[]);
const char * my_strchr (const char *Arr, char c);
int my_strlen (const char Arr[]);
void my_strcpy (const char *Original, char *Parody);
char *my_strcat (char *destination, const char * to_paste);
int my_strcmp (const char * First, const char *Second);
char *my_strdup (const char *Orig);
int min (int a, int b);
void my_strncpy (const char *Original, char *Parody, int n);
char *my_strncat (char *destination, const char * to_paste, int n);
int my_atoi (const char *Source);
int my_atoi_beta (const char *Source);
char *my_fgets (char *input, int maxn, FILE *stream);

#endif // SOME_FUNCTION
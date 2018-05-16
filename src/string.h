#ifndef STRING
#define STRING

#include <stdio.h>
#include <stdlib.h>

int slen(char *str);

void stok_free(char** arr);
char** stok(char* str, char delim);
int s_tok(char *str, char delim, char *ptr[]);

int schr(char *str, char ch);

void scopy(char *s1, char *s2);

int s_cmp(char *str1, char *str2);

int str_chr(char *str, char *ch);
int str_tok(char *str, char *delim, char **ptr);


//void stok_print(char** arr);

//char *toLower(char *str);

//char toLowCase(char ch);

//int isLowCase(char ch);

//int isDigit(char ch);

//int isApperCase(char ch);

//int sequal(char *s1, char *s2);

//void suntok(char *str, char delim, char *ptr[], int cnt);

//int sstr(char *text, char *pattern);

//int sspn(char *str, char *sym);

//int s_str(char *txt, char *p);

//void concat(char *dest, char* str);

#endif
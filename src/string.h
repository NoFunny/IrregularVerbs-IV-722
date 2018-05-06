#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>

char** stok(char* str, char delim);

void stok_free(char** arr);

void stok_print(char** arr);

char *toLower(char *str);

char toLowCase(char ch);

int isLowCase(char ch);

int isDigit(char ch);

int isApperCase(char ch);

int slen(char *str);

void scopy(char *s1, char *s2);

int sequal(char *s1, char *s2);

int scmp(char *s1, char *s2);

int schr(char *str, char ch);

int s_stok(char *str, char delim, char *ptr[]);

void suntok(char *str, char delim, char *ptr[], int cnt);

int sstr(char *text, char *pattern);

int sspn(char *str, char *sym);

int s_str(char *txt, char *p);

void concat(char *dest, char* str);
#endif
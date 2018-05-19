#include <stdio.h>
#include <ctest.h>
#include "dictionary.h"
#include "interface.h"
#include "string.h"

                                 //STRING.C//
CTEST(string, SLEN) //Проверка ввода слов
{
	//Given
	char str[19] = "write;wrote;written";
	char str_1[1] = "\0";
	//When
	int real = slen(str);
	int real1 = slen(str_1);
	//Then
	const int expected = 19;
	const int expected1 = 0;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(string, SCHR) //Проверка ввода слов
{
	//Given
	char str[19] = "write;wrote;written";
 	char ch = 'o';
 	char ch1 = 'c';
	
	//When
	int real = schr(str, ch);
	int real1 = schr(str, ch1);

	//Then
	const int expected = 8;
	const int expected1 = -1;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(string, S_CMP_Ok) //Проверка ввода слов
{
	//Given
	char str1[19] = "write;wrote;written";
 	char str_1[19] = "write/wrote/written";
 	
 	char str2[19] = "write;wrote;written";
 	char str_2[5] = "write";
	//When
	int real = s_cmp(str1, str_1);
	int real1 = s_cmp(str2, str_2);
	//Then
	const int expected = 1;
	const int expected1 = -1;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}
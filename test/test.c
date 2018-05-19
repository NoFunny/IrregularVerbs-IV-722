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

#include <stdio.h>
#include <ctest.h>
#include "working_with_data.h"
#include "string.h"

//STRING.C
CTEST(string, SLEN) //Длина строки
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

CTEST(string, S_TOK) //Разбиение строки
{
	//Given
	char str[] = "write;wrote;written";
 	char delim = ';';
 	char delim_1 = '.';
 	char *ptr[3];

	//When
	int real = s_tok(str, delim, ptr);
	int real1 = s_tok(str, delim_1, ptr);

	//Then
	const int expected = 3;
	const int expected1 = 1;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(string, SCHR) //Поиск символа в строке
{
	//Given
	char str[] = "write;wrote;written";
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

CTEST(string, SCOPY) //Копирование строки
{
	//Given
	char str[] = "write;wrote;written";
	char str_1[] = "";
	
	//When
	scopy(str_1,str);

	//Then
	ASSERT_STR(str, str_1);
}

CTEST(string, S_CMP)  //Сравнение строк
{
	//Given
	char str1[] = "write;wrote;written";
 	char str_1[] = "write;wrote;written";
 	
 	char str2[] = "write;wrote;written";
 	char str_2[] = "write";

	//When
	int real = s_cmp(str1, str_1);
	int real1 = s_cmp(str2, str_2);

	//Then
	const int expected = 0;
	const int expected1 = 1;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(string, STR_CHR) //Поиск подстроки в строке
{
	//Given
	char str[19] = "write;wrote;written";
	char ch[2] = ";";
	char ch_1[6] = "write";

	//When
	int real = str_chr(str, ch);
	int real1 = str_chr(str, ch_1);

	//Then
	const int expected = 5;
	const int expected1 = 0;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(string, STR_TOK) //Разбиение строки
{
	//Given
	char str[] = "write;wrote;written";
	char delim[] = "/|\\,.;", *ptr[3];

	//When
	int real = str_tok(str, delim, ptr);

	//Then
	const int expected = 3;
	ASSERT_EQUAL(expected, real);
}

//DICTIONARY.C
CTEST(working_with_data, C_STRING) //Проверка подсчета размера словаря
{	
	//Given
	FILE *input = fopen("dictionary.txt", "r");
	FILE *input_1 = fopen("dict.txt", "r");
	
	//When
	int real = count_string(input);
	int real1 = count_string(input_1);
	
	//Then
	const int expected = 100;
	const int expected1 = 1;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected1, real1);
}

CTEST(dictionary, INIT) //Проверка инициализации словаря
{	
	//Given
	int max_words_in_dictionary = 0;
	int max_words_in_dictionary_1 = 100;

	//When
	dictionary *real = dictionary_init(max_words_in_dictionary);
	dictionary *real1 = dictionary_init(max_words_in_dictionary_1);
	
	//Then
	ASSERT_NULL(real);
	ASSERT_NOT_NULL(real1);
}

CTEST(dictionary, READING) //Проверка чтения словаря
{	
	// //Given
	int max_words_in_dictionary = 100;
	int max_words_in_dictionary_1 = 0;
	dictionary *tab = dictionary_init(max_words_in_dictionary);
	dictionary *tabl = dictionary_init(max_words_in_dictionary_1);

	//When
	dictionary *real = dictionary_reading(tab, max_words_in_dictionary);
	dictionary *real1 = dictionary_reading(tabl,max_words_in_dictionary_1);
	
	//Then
	ASSERT_NOT_NULL(real);
	ASSERT_NULL(real1);
}

CTEST(dictionary, RANDOM_GEN) //Проверка генератора рандомных чисел
{	
	// //Given
	int n = 5;
	int max_words_in_dictionary = 100;
	int max_words_in_dictionary_1 = 0;
	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	int *bucket = (int*)malloc(sizeof(int)*max_words_in_dictionary);

	int *value_1 = (int*)malloc(sizeof(int)*max_words_in_dictionary_1);
	int *bucket_1 = (int*)malloc(sizeof(int)*max_words_in_dictionary_1);

	//When
	int real = random_generator(max_words_in_dictionary, value, bucket, n);	

	int real1 = random_generator(max_words_in_dictionary_1, value_1, bucket_1, n);	
	
	//Then
	const int expected = 5;
	const int expected_1 = 0;
	ASSERT_EQUAL(expected, real);
	ASSERT_EQUAL(expected_1, real1);
}

CTEST(working_with_data, D_CLEAN) //Проверка очищения массива и структуры данных
{	
	// //Given
	int max_words_in_dictionary = 100;
	int *value = (int*)malloc(sizeof(int)*max_words_in_dictionary);
	dictionary *tab = dictionary_init(max_words_in_dictionary);

	//When
	int real = dictionary_clean(tab, value);

	//Then
	const int expected = 1;
	ASSERT_EQUAL(expected, real);
}	

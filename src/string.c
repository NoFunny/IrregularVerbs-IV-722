#include "string.h"

char** stok(char* str, char delim)
{
    int leng = slen(str);
    int i, j, k;
    int arr_count = 0;
    j = k = 0;
    
    for (i = 0; i < leng; i++){
        if (str[i] == delim){
            str[i] = '\0';
            arr_count++;
        }
    }
    arr_count++;

    char **res = (char**)malloc(sizeof(char*) * (arr_count + 1));
    if (res == NULL) return 0;
    res[arr_count] = NULL;

    for (i = 0; i < arr_count; i++){

        res[i] = (char*)malloc(sizeof(char) * (leng + 1));
        
        while(str[j] != '\0'){
            res[i][k] = str[j];
            k++;
            j++;
        }
        j++;

        res[i][k] = '\0';
        res[i] = realloc(res[i], k);
        k = 0;
    }

    return res;
}

void stok_free(char** arr)
{
    int i = 0;
    while(arr[i] != NULL){
        free(arr[i++]);
    }
    free(arr);
}

void stok_print(char** arr)
{
    int i = 0;
    int j = 0;
    while (arr[i] != NULL){
        while (arr[i][j] != '\0'){
            putchar(arr[i][j]);
            j++;
        }
        putchar('\n');
        i++;
        j=0;
    }
}

char *toLower(char *str)
{
	int i;
	for(i = 0; str[i] != '\0'; i++) {
		if(str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + ('a' - 'A');
		}
	}
	return str;
}
char toLowCase(char ch)
{
	if( ch >= 'A' && ch <= 'Z') {
		return ch + ('a' - 'A');
	}
	return ch;

}

int isLowCase(char ch)
{
	if( ch >= 'a' && ch <= 'z') {
		return 1;
	}
	return 0;
	
}

int isDigit(char ch)
{
	if( ch >= '0' && ch <= '9') {
		return 1;
	}
	return 0;
}

int isApperCase(char ch)
{
    if(ch >= 'A' && ch <= 'Z')
        return 1;

    return 0;
}

int slen(char *str)
{
	int i = 0;
	while(*str){
		i++;
		str++;
	}
	return i;
}

void scopy(char *s1, char *s2)
{
	while((*s2++ = *s1++) != '\0');
}

int sequal(char *s1, char *s2)
{
	int i, flg = 1;
		for(i = 0; flg && (s1[i]!='\0' || s2[i]!='\0');i++) {
			if( s1[i]!=s2[i] ) flg = 0;
		}
	return flg;
}

int scmp(char *s1, char *s2)
{
	int i, flg = 0;
	for( i = 0; (s1[i]==s2[i]) && s1[i]!='\0' && s2[i]!='\0'; i++);
		if( s1[i] < s2[i] ) 
			flg = -1; // если строки
		else if( s1[i] > s2[i] ) 
			flg = 1;// разной длины
	return flg;
}


int schr(char *str, char ch)
{
	int i, index = -1;
	for(i = 0; (str[i] != '\0') && (str[i] != ch); i++);
		if( str[i] == ch )
		index = i;

	return index;
}

int s_stok(char *str, char delim, char *ptr[])
{
	char *suf = str;
	ptr[0] = str; // первое поле – начало str
	int i, j = 1; // j – счетчик полей
	while( ( i = schr(suf, delim) ) >= 0 ){
		suf[i] = '\0';
		suf = suf + i + 1;
		ptr[j] = suf;
		j++;
	}
	return j;
}

void suntok(char *str, char delim, char *ptr[], int cnt)
{
	int i;
	for(i = 1; i < cnt; i++){
		*(ptr[i] - 1) = delim;
	}
}

int sspn(char *str, char *sym)
{
	int i;
	for( i = 0; str[i] != '\0' ; i++) {
		if( schr(sym, str[i] ) < 0 ) {
		break;
		}
	}
	return i;
}

int s_str(char *txt, char *p)
{
	char *suf = txt;
	int len = slen(p);
	int i, pos = -1;
	while( ( ( i = schr(suf,p[0]) ) >= 0) && (pos < 0) ){
		char tmp;
		suf = suf + i;
		tmp = suf[len];
		suf[len] = '\0';
		if( sequal(suf, p) ){ // посимвольное сравнение строк
			pos = suf - txt; // разность указателей = индекс
		}
		suf[len] = tmp;
		suf++;
	}
	return pos;
}

void concat(char *dest, char* str){
	while(*dest) {
		dest++;
	}
	while((*dest++ = *str++) != '\0');
}

int sstr(char *text, char *pattern)
{
    //  Если шаблон подстроки пустой, то возвращаем 0
    if (! *pattern)
        return 0;
 
    // Необходимые переменные.
    int pos = -1;
    const char *a, * b;
 
    b = pattern;
 
    // перебираем строку посимвольно. Как мы помним C-строка - это массив символов. Поэтому нам удобнее работать через указатели.
    for (; *text != 0; text++){
        // увеличиваем значение позиции на 1.
        pos++;
 
        // В случае, если исмволы не идентичны, остальной код пропускаем.
        if (*text != *b) {
            continue;
        }
 
        // Если че у нас символ в текущей позиции строки равен первому символу шаблона, то запускаем бесконечный цикл.
        // Он прерывается в случае несовпадения символов.
 
        // "а" присваиваем "text" с ее текущей позиции. Тогда позиция text в цикле не меняется, а меняется позиция в "a".
        a = text;
 
        while(1) {
 
            // Если b достиг конца шаблона, то мы нашли полное совпадение и можем вернуть позицию pos
            if (*b == 0){
                return pos;
            }
 
            // Если же следующие символы не равны, то прерываем функцию
            if (*a++ != *b++) {
                break;
            }
        }
 
        // Позицию в b снова сбрасываем на начало.
        b = pattern;
    }
 
    return -1;
}

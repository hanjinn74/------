#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
void main()
{
	char str[100];
	int str_cnt;
	int i;

	printf("영문자 및 숫자를 입력(100자 이하) :");
	scanf("%s", str);

	printf("\n");
	printf("입력한 문자열==>%s\n", str);
	printf("변환된 문자열==>");

	str_cnt = strlen(str);

	for (i = str_cnt; i >= 0; i--)
	{
		printf("%c", str[i]);
	}

	printf("\n");
}
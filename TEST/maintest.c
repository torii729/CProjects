// 2025.07.02. 구조체 배열과 파일 입출력 사용

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

typedef struct
{
	char Name[20];
	char Phone[20];
	char Pw[20];

}USER;

void fileSave(USER users[], int size);
void fileLoad();

int main()
{
	USER users[] = {
		{"ㄹㅇ", "010", "qlalf"},
		{"ㅁㄹ", "123", "번호"}
	};

	fileSave(users, SIZE);
	fileLoad();
	return 0;
}

void fileSave(USER users[], int size)
{
	FILE* test = fopen("test.txt", "w");

	if (test == NULL)
	{
		printf("파일을 열 수 없어요\n");
		return;
	}

	for (int i = 0; i < size; i++)
	{
		fprintf(test, "%s, %s, %s\n", users[i].Name, users[i].Phone, users[i].Pw);
	}

	fclose(test);
	printf("파일 저장됐음\n");
}

void fileLoad()
{
	FILE* test = fopen("test.txt", "r");

	if (test == NULL)
	{
		printf("파일을 열 수 없어요\n");
		return;
	}

	USER temp; // 파일에서 한 줄씩 데이터를 임시로 받아올 공간이 필요해서 선언
	printf("파일에서 불러온 정보들임\n");

	while (fscanf(test, "%s %s %s", temp.Name, temp.Phone, temp.Pw) == 3)
	{
		printf("이름 : %s 전화번호 : %s 비밀번호 : %s\n", temp.Name, temp.Phone, temp.Pw);
	}

	fclose(test);
}
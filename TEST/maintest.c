// 2025.07.02. ����ü �迭�� ���� ����� ���

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 2

// ����ü ����
typedef struct
{
	char Name[20];
	char Phone[20];
	char Pw[20];

}USER;

// �Լ� ����
void fileSave(USER users[], int size);
void fileLoad();

int main()
{
	// ����ü �迭
	USER users[] = {
		{"���", "010-1111-1111", "qwer!"},
		{"����", "010-9999-9999", "1234!"}
	};

	// �Լ� ȣ��
	fileSave(users, SIZE);
	fileLoad();
	return 0;
}

void fileSave(USER users[], int size)
{
	FILE* test = fopen("test.txt", "w");

	if (test == NULL)
	{
		printf("������ �� �� �����\n");
		return;
	}

	for (int i = 0; i < size; i++)
	{
		fprintf(test, "%s, %s, %s\n", users[i].Name, users[i].Phone, users[i].Pw);
	}

	fclose(test);
	printf("���� ����ƾ��\n");
}

void fileLoad()
{
	FILE* test = fopen("test.txt", "r");

	if (test == NULL)
	{
		printf("������ �� �� �����\n");
		return;
	}

	USER temp; // ���Ͽ��� �����͸� �� �پ� �ӽ÷� �޾ƿ� ������ �ʿ��ؼ� ����
	printf("���Ͽ��� �ҷ��� �����Դϴ�\n");

	while (fscanf(test, "%s %s %s", temp.Name, temp.Phone, temp.Pw) == 3)
	{
		printf("�̸� : %s ��ȭ��ȣ : %s ��й�ȣ : %s\n", temp.Name, temp.Phone, temp.Pw);
	}

	fclose(test);
}
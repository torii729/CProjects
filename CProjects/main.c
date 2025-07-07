/*
    ********************
    ������ ���� ���α׷�
    ********************

    �������� ������Ʈ
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //
#include <string.h>
#include <windows.h> //

#define MAX_MEMBERS 100

typedef struct
{
    char phone[20];
    char password[20];
}Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

void xy(int x, int y);
void setColor(int color);
void loadMembers();
void drawMenu();
int login();
void signUp(); // ȸ������

int main()
{
    char menuInput[10];
    int choice = 0;

    loadMembers();

    while (1)
    {
        drawMenu();
        fgets(menuInput, sizeof(menuInput), stdin);
        choice = atoi(menuInput);

        if (choice == 1)
        {
            if (login())
            {
                break;
            }
        }
        else if (choice == 2)
        {
            signUp();
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            printf("�߸��� �Է��Դϴ�.\n");
            system("pause");
        }
    }

    return 0;
}

void xy(int x, int y)
{
    COORD XY = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void loadMembers()
{
    FILE* file = fopen("member.txt", "r");
    if (file == NULL)
    {
        printf("ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
        return;
    }

    while (fscanf(file, "%s %s", members[memberCount].phone, members[memberCount].password) == 2)
    {
        memberCount++;
    }

    fclose(file);
}

void drawMenu()
{
    system("cls");
    setColor(10);

    xy(3, 0); printf("������������������������������������������������������������������������������������������");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("��");
        xy(47, i); printf("��");
    }
    xy(3, 15); printf("������������������������������������������������������������������������������������������");

    xy(10, 3); printf("������������������������������������������������������������       ��");
    xy(10, 4); printf("��        ������ �ý���       ��       ��");
    xy(10, 5); printf("������������������������������������������������������������       ��");
    xy(10, 6); printf("  1. �α���                          ��");
    xy(10, 7); printf("  2. ȸ������                        ��");
    xy(10, 8); printf("  3. ����                            ��");
    xy(10, 10); printf("  �޴� �Է� : ");

    setColor(7);
}

int login()
{
    char phone[20], password[20];

    system("cls");
    setColor(11);

    // ui �׸���
    xy(3, 0); printf("������������������������������������������������������������������������������������������");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("��");
        xy(47, i); printf("��");
    }
    xy(3, 15); printf("������������������������������������������������������������������������������������������");
    xy(10, 3); printf("������������������������������������������������������������       ��");
    xy(10, 4); printf("��        ������ �α���       ��       ��");
    xy(10, 5); printf("������������������������������������������������������������       ��");

    setColor(7);

    xy(10, 6); printf("��ȭ��ȣ �Է�");
    xy(10, 7); printf("[ex) 010-xxxx-xxxx] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    xy(10, 8); printf("��й�ȣ [���� 4�� + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0 && strcmp(members[i].password, password) == 0)
        {
            system("cls");
            setColor(10);

            // ui �׸���
            xy(3, 0); printf("������������������������������������������������������������������������������������������");
            for (int j = 1; j <= 14; j++)
            {
                xy(3, j); printf("��");
                xy(47, j); printf("��");
            }
            xy(3, 15); printf("������������������������������������������������������������������������������������������");
            xy(10, 3); printf("������������������������������������������������������������       ��");
            xy(10, 4); printf("��        ������ �ý���       ��       ��");
            xy(10, 5); printf("������������������������������������������������������������       ��");

            xy(10, 6); printf("�α��� ����! ȯ���մϴ�.\n");

            setColor(7);
            system("pause");
            return 1;
        }
    }

    setColor(12);
    xy(10, 9); printf("�α��� ����: ��ȭ��ȣ �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
    setColor(7);

    system("pause");
    return 0;
}

void signUp() {
    char phone[20], password[20];

    system("cls");
    setColor(11);

    // ui �׸���
    xy(3, 0); printf("������������������������������������������������������������������������������������������");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("��");
        xy(47, i); printf("��");
    }
    xy(3, 15); printf("������������������������������������������������������������������������������������������");
    xy(10, 3); printf("������������������������������������������������������������       ��");
    xy(10, 4); printf("��        ȸ������ ȭ��       ��       ��");
    xy(10, 5); printf("������������������������������������������������������������       ��");

    xy(10, 6); printf("��ȭ��ȣ �Է�");
    xy(10, 7); printf("[ex: 010-1234-5678] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0)
        {
            setColor(12);
            xy(10, 8); printf("�̹� ��ϵ� ��ȭ��ȣ�Դϴ�.\n");
            setColor(7);
            system("pause");
            return;
        }
    }

    xy(10, 9); printf("��й�ȣ �Է�");
    xy(10, 10); printf("[���� 4�ڸ� + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    strcpy(members[memberCount].phone, phone);
    strcpy(members[memberCount].password, password);
    memberCount++;

    FILE* file = fopen("member.txt", "a");

    if (file == NULL)
    {
        setColor(12);
        xy(10, 12); printf("ȸ�� ���� ���� ����\n");
        setColor(7);

        system("pause");
        return;
    }

    fprintf(file, "%s %s\n", phone, password);
    fclose(file);

    setColor(10);
    xy(10, 12); printf("ȸ������ �Ϸ�\n");
    setColor(7);

    system("pause");
}

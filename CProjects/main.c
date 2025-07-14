/*
    ********************
    ������ ���� ���α׷�
    ********************

    �������� ������Ʈ
    �ؽ�Ʈ �Է� ���
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_MEMBERS 100

/*
    ����ü ���� ����
*/

// ����� ���� ����ü
typedef struct
{
    char name[20]; // ����� �̸�
    char phone[20]; // ��ȭ��ȣ
    char password[20]; // ��й�ȣ
} Member;

// ���� ���� ����ü
typedef struct
{
    char id[30]; // ���� ID
    char bookTitle[50]; // ���� ����
    char bookAuthor[20]; // ���� ����
    char bookPublish[20]; // ���ǻ�
} Book;

// ���� ���� ����ü
typedef struct
{
    char id[30]; // ���� ID
    char borrowerPhone[20]; // ������ ��ȭ��ȣ
    int borrowYear; // ���� ����
    int borrowMonth; // ���� ��
    int borrowDay; // ���� ��
    int returnYear; // �ݳ� ����
    int returnMonth; // �ݳ� ��
    int returnDay; // �ݳ� ��
    int state; // ���� ����(0: ����, 1: ������, 2: ��ü)
} BorrowList;

/*
    ���� ���� ����
*/
Member members[MAX_MEMBERS];
int memberCount = 0; // ���� ��ϵ� ȸ�� ��
char currentUser[20]; // ���� �α����� ����� �̸� �����

/*
    �Լ� �����
*/
void gotoxy(int x, int y); // �ܼ� Ŀ�� �̵� �Լ�
void setColor(int color); // �ܼ� ���� ���� ���� �Լ�
void loadMembers(); // ȸ�� ���� ���Ͽ��� �ҷ�����
void drawMainMenu(); // �ʱ� ���� �޴� UI ��� �Լ�
int login(); // �α��� ��� �Լ�
void signUp(); // ȸ������ ��� �Լ�
void drawBox(int x, int y, int w, int h); // �簢�� �ڽ� �׸��� �Լ�
void drawTitleBox(int x, int y, const char* text); // ���� ���� ��� �Լ�
void drawUserMenu(); // �α��� �� ����� ���� �޴� �Լ�

/*
    ���� �Լ�
*/
int main()
{
    int choice;
    char input[10];

    loadMembers(); // ���α׷� ���� �� ȸ�� ���� ���� �ҷ�����

    while (1)
    {
        drawMainMenu(); // ���� ȭ�� ���

        gotoxy(13, 22);
        printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
        {
            if (login())
            {
                drawUserMenu(); // �α��� ���� �� ����� �޴� �̵�
            }
        }
        else if (choice == 2)
        {
            signUp(); // ȸ������ �̵�
        }
        else if (choice == 3)
        {
            break; // ����
        }
        else
        {
            gotoxy(13, 22); setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �������ּ���.");
            setColor(7);
            system("pause");
        }
    }
    return 0;
}

/*
    �ܼ� Ŀ�� ��ġ �̵� �Լ�
*/
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
    �ܼ� ���� ���� ���� �Լ�
*/
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*
    ȸ�� ������ ���Ͽ��� �ҷ����� �Լ�
*/
void loadMembers()
{
    FILE* file = fopen("member.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%s %s %s",
        members[memberCount].name,
        members[memberCount].phone,
        members[memberCount].password) == 3)
    {
        memberCount++;
    }
    fclose(file);
}

/*
    ���� �ڽ� �׸���
*/
void drawTitleBox(int x, int y, const char* text)
{
    gotoxy(x, y);     printf("������������������������������������������������������");
    gotoxy(x, y + 1); printf("��   %s  ��", text); // �ؽ�Ʈ ��� ��ġ
    gotoxy(x, y + 2); printf("������������������������������������������������������");
}

/*
    �簢�� �ڽ� ��� �Լ�
*/
void drawBox(int x, int y, int w, int h)
{
    gotoxy(x, y); printf("��");
    for (int i = 0; i < w - 2; i++)
    {
        printf("��");
    }
    printf("��");

    for (int i = 1; i < h - 1; i++)
    {
        gotoxy(x, y + i); printf("��");
        gotoxy(x + w - 1, y + i); printf("��");
    }

    gotoxy(x, y + h - 1); printf("��");
    for (int i = 0; i < w - 2; i++)
    {
        printf("��");
    }
    printf("��");
}

/*
    ���� ȭ�� UI ���
*/
void drawMainMenu()
{
    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 22); // ��ü ���� �ڽ�
    drawTitleBox(17, 4, "������ ���� ���α׷�"); // ���� ����

    drawBox(22, 8, 16, 3); // �α��� ��ư �ڽ�
    gotoxy(25, 9); printf("1. �α���");

    drawBox(22, 12, 16, 3); // ȸ������ ��ư �ڽ�
    gotoxy(25, 13); printf("2. ȸ������");

    setColor(12);
    drawBox(22, 16, 16, 3); // ���� ��ư �ڽ�
    gotoxy(25, 17); printf("3. ����");
    setColor(7);

    // ��ȣ �Է� ĭ ��� ���� ��
    gotoxy(10, 21); printf("��������������������������������������������������������������������������������");

    // �ϴ� �׵θ�
    gotoxy(10, 23); printf("��������������������������������������������������������������������������������");
}

/*
    �α��� ���
*/
int login()
{
    char name[20], phone[20], password[20];
    system("cls");

    drawBox(10, 2, 40, 22);
    drawTitleBox(17, 3, "   ����� �α���    ");
    drawBox(12, 6, 36, 17);

    gotoxy(14, 7); printf("�̸�        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("��ȭ��ȣ    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("��й�ȣ    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].name, name) == 0 &&
            strcmp(members[i].phone, phone) == 0 &&
            strcmp(members[i].password, password) == 0)
        {
            strcpy(currentUser, name); // �α��� ���� �� ����� �̸� ����("~~�� ȯ���մϴ�!" ������ "~~" ������)
            return 1;
        }
    }
    gotoxy(14, 19); setColor(12);
    printf("�α��� ����: ������ ��ġ���� �ʽ��ϴ�.\n");
    setColor(7);
    system("pause");
    return 0;
}

/*
    ȸ������ ���
*/
void signUp()
{
    return 0;
}

/*
    �α��� �� ����� �޴� ȭ��
*/
void drawUserMenu()
{
    char welcome[60];
    int choice;
    char input[10];

    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 22); // ��ü ���� �ڽ�
    drawTitleBox(17, 4, "������ ���� ���α׷�"); // ���� ����

    sprintf(welcome, "    %s ��, ȯ���մϴ�!", currentUser);
    setColor(10);
    gotoxy(17, 7); printf("%s", welcome);
    setColor(7);

    setColor(3);
    drawBox(14, 8, 16, 5); // ���� ����
    gotoxy(16, 10); printf("1. ���� ����");

    drawBox(31, 8, 16, 5); // ���� �ݳ�
    gotoxy(33, 10); printf("2. ���� �ݳ�");
    setColor(7);

    setColor(8);
    drawBox(14, 13, 11, 5); // ���� ���
    gotoxy(16, 15); printf("3. ���");

    drawBox(25, 13, 11, 5); // ���� �˻�
    gotoxy(27, 15); printf("4. �˻�");

    drawBox(36, 13, 11, 5); // ���� ����
    gotoxy(38, 15); printf("5. ����");
    setColor(7);

    setColor(12);
    drawBox(25, 18, 11, 3); // ����
    gotoxy(27, 19); printf("6. ����");
    setColor(7);

    // ��ȣ �Է� ĭ ��� ���� ��
    gotoxy(10, 21); printf("��������������������������������������������������������������������������������");

    // ��ȣ �Է� ���� ���
    gotoxy(13, 22); printf("��ȣ �Է� : ");

    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    // �ϴ� �׵θ�
    gotoxy(10, 23); printf("��������������������������������������������������������������������������������");



    // ���� ��� �߰� ������
}

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
char currentUser[20]; // ���� �α����� ����� �̸� �����

/*
    �Լ� �����
*/
void gotoxy(int x, int y); // �ܼ� Ŀ�� �̵� �Լ� (xy ��ǥ)
void setColor(int color); // �ܼ� ���� ���� ���� �Լ�
void drawMainMenu(); // �ʱ� ���� �޴� UI ��� �Լ�
void drawBox(int x, int y, int w, int h, const char text[]); // �簢�� �ڽ� �׸��� �Լ�
void drawUserMenu(); // �α��� �� ����� ���� �޴� �Լ�

int mainLogin(); // ���� ȭ�� (��ó�� ȭ��)
int login(); // �α��� ��� �Լ�
void signUp(); // ȸ������ ��� �Լ�

void handleBorrow(); // ���� ����
void handleReturn(); // ���� �ݳ�
void showBookList(); // ��� ����
void searchBook(); // ���� �˻�
void viewBorrowHistory(); // ���� ����


/*
    ���� �Լ�
*/
int main()
{
    mainLogin();
    return 0;
}

/*
    ���� ȭ�� (��ó�� ȭ��)
*/
int mainLogin()
{
    int choice;
    char input[10];

    while (1)  // ���� �ݺ� (���� : ȸ������ �Ϸ��ϰ� ����� �ٽ� ���ƿ;� ��, �ݺ����� ������ ȸ������ �Ϸ� �� ���α׷��� �����)
    {
        drawMainMenu(); // ���� ȭ�� ���

        gotoxy(13, 22);
        printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1 :
            if (login()) // �α��� ����
                drawUserMenu(); // �α��� ���� �� ����� �޴� �̵�
            break;

        case 2 :
            signUp(); // ȸ������ ����
            break;

        case 3 :
            return 0; // ����
        
        default :
            gotoxy(13, 22);
            setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
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
    �簢�� �ڽ� ��� �Լ�
*/
void drawBox(int x, int y, int width, int height, const char text[])
{
    // ���
    gotoxy(x, y); printf("��");
    for (int i = 0; i < width - 2; i++)
    {
        printf("��");
    }
    printf("��");

    // �߰�
    for (int i = 1; i < height - 1; i++) 
    {
        gotoxy(x, y + i); printf("��");
        for (int j = 0; j < width - 2; j++)
        {
            printf(" ");
        }
        printf("��");
    }

    // �ϴ�
    gotoxy(x, y + height - 1); printf("��");
    for (int i = 0; i < width - 2; i++)
    {
        printf("��");
    }
    printf("��");

    // �ؽ�Ʈ ��� (�߾� ����)
    if (text != NULL)
    {
        int textX = x + (width - (int)strlen(text)) / 2;
        int textY = y + 1;
        gotoxy(textX, textY);
        printf("%s", text);
    }
}

/*
    ���� ȭ�� UI ���
*/
void drawMainMenu()
{
    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 3, "������ ���� ���α׷�"); // ��ü ���� �ڽ�
    drawBox(10, 5, 40, 19, "");

    drawBox(22, 8, 16, 3, " 1. �α���"); // �α��� ��ư �ڽ�
   // gotoxy(25, 9); printf("1. �α���");

    drawBox(22, 12, 16, 3, " 2. ȸ������"); // ȸ������ ��ư �ڽ�
    // gotoxy(25, 13); printf("2. ȸ������");

    setColor(12);
    drawBox(22, 16, 16, 3, " 3. ����"); // ���� ��ư �ڽ�
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
    char fileName[20], filePhone[20], filePassword[20];

    FILE* file = fopen("member.txt", "r");
    if (file == NULL)
    {
        gotoxy(14, 19);
        setColor(12);
        printf("ȸ�� ������ ������ �����ϴ�.");
        setColor(7);
        system("pause");
        return 0;
    }

    system("cls");

    drawBox(10, 2, 40, 3, "����� �α���");
    drawBox(10, 5, 40, 19, "");
    drawBox(12, 6, 36, 17, "");

    gotoxy(14, 7); printf("�̸�        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("��ȭ��ȣ    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("��й�ȣ    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    int check = 0;

    while (fscanf(file, "%s %s %s", fileName, filePhone, filePassword) == 3)
    {
        if (strcmp(name, fileName) == 0 &&
            strcmp(phone, filePhone) == 0 &&
            strcmp(password, filePassword) == 0)
        {
            check = 1; 
            break;
        }
    }

    fclose(file);

    if (check)
    {
        strcpy(currentUser, name);
        return 1;
    }
    else
    {
        gotoxy(14, 19);
        setColor(12);
        printf("�α��� ����: ������ ��ġ���� �ʽ��ϴ�.\n");
        setColor(7);
        system("pause");
        return 0;
    }
}


/*
    ȸ������ ���
*/
void signUp()
{
    char name[20], phone[20], password[20];

    system("cls");

    drawBox(10, 2, 40, 3, "ȸ������");
    drawBox(10, 5, 40, 19, "");
    drawBox(12, 6, 36, 17, "");

    gotoxy(14, 7);  printf("�̸�        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("��ȭ��ȣ    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("��й�ȣ    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    FILE* file = fopen("member.txt", "a");

    if (file == NULL)
    {
        gotoxy(14, 19);
        setColor(12);
        printf("ȸ�� ���� ���� ����");
        setColor(7);
        system("pause");
        return;
    }

    fprintf(file, "\n%s %s %s", name, phone, password);
    fclose(file);

    gotoxy(14, 19);
    setColor(10);
    printf("ȸ������ �Ϸ�");
    setColor(7);
    system("pause");
}

/*
    �α��� �� ����� �޴� ȭ��
*/
void drawUserMenu()
{
    char welcome[60];
    char input[10];
    int choice;

    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 3, "������ ���� ���α׷�"); // ��ü ���� �ڽ�
    drawBox(10, 5, 40, 19, "");

    sprintf(welcome, "    %s ��, ȯ���մϴ�!", currentUser);
    setColor(10);
    gotoxy(17, 6); printf("%s", welcome);
    setColor(7);

    setColor(3);
    drawBox(14, 8, 16, 5, ""); // ���� ����
    gotoxy(16, 10); printf("1. ���� ����");
 
    drawBox(31, 8, 16, 5, ""); // ���� �ݳ�
    gotoxy(33, 10); printf("2. ���� �ݳ�");
    setColor(7);

    setColor(8);
    drawBox(14, 13, 11, 5, ""); // ���� ���
    gotoxy(16, 15); printf("3. ���");

    drawBox(25, 13, 11, 5, ""); // ���� �˻�
    gotoxy(27, 15); printf("4. �˻�");

    drawBox(36, 13, 11, 5, ""); // ���� ����
    gotoxy(38, 15); printf("5. ����");
    setColor(7);

    setColor(12);
    drawBox(23, 18, 15, 3, ""); // �ڷΰ���
    gotoxy(25, 19); printf("6. �ڷ� ����");
    setColor(7);

    // ��ȣ �Է� ĭ ��� ���� ��
    gotoxy(10, 21); printf("��������������������������������������������������������������������������������");

    // ��ȣ �Է� ����
    gotoxy(13, 22); printf("��ȣ �Է� : ");

    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    // �ϴ� �׵θ�
    gotoxy(10, 23); printf("��������������������������������������������������������������������������������");

    switch (choice)
    {
    case 1:
        handleBorrow();
    case 2:
        handleReturn();
    case 3:
        showBookList();
    case 4:
        searchBook();
    case 5:
        viewBorrowHistory();
    case 6:
        mainLogin();
    default:
        gotoxy(13, 22); setColor(12);
        printf("�߸��� �Է��Դϴ� . �ٽ� �Է����ּ���.");
        setColor(7);
        system("pause");
    }
}

// �̱��� �Լ���
void handleBorrow()
{
    system("cls");
    drawBox(10, 2, 40, 22, "");
    system("pause");
}

void handleReturn()
{
    system("cls");
    drawBox(10, 2, 40, 22, "");
    system("pause");
}

void showBookList()
{
    system("cls");
    drawBox(10, 2, 40, 22, "");
    system("pause");
}

void searchBook()
{
    system("cls");
    drawBox(10, 2, 40, 22, "");
    system("pause");
}

void viewBorrowHistory()
{
    system("cls");
    drawBox(10, 2, 40, 22, "");
    system("pause");
}
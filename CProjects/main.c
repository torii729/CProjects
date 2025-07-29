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
#include <conio.h>
#include <time.h>
#include "Struct.h" // ����ü(Member, Book, BorrowList) ��� ����

#define LEFT 75
#define RIGHT 77

/*
    ���� ���� ����
*/
Member members[1000];
Book books[1000];
Borrow borrowList[1000] = { 0 };
char currentUser[20]; // ���� �α����� ����� �̸� �����
char currentPhone[20]; // ���� �α����� ����� ��ȭ��ȣ �����
int year, month, day;

/*
    �Լ� �����
*/
void gotoxy(int x, int y); // �ܼ� Ŀ�� �̵� �Լ� (xy ��ǥ)
void setColor(int color); // �ܼ� ���� ���� ���� �Լ�
int manageMemberFile(Member members[], Member newMember, int mode); // member.txt ���� �аų� �߰� �Լ�
int manageBookFile(Book books[], Book newBook, int mode); // book.txt ���� �аų� �߰� �Լ�
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount); // borrowList.txt ���� �аų� �߰� �Լ�
void getDate(int dayOffset); // ��¥ ��� �Լ�
void drawBox(int x, int y, int w, int h, char text[]); // �簢�� �ڽ� �׸��� �Լ�
void drawMainMenu(); // �ʱ� ���� �޴� UI ��� �Լ�

int mainLogin(); // ���� ȭ�� (��ó�� ȭ��)
int selectLogin(); // �α��� ���� (�����? ������?)
int userMenu(); // �α��� �� "�����" ���� �޴� �Լ�
int adminMenu(); // �α��� �� "������" ���� �޴� �Լ�


int login();
void signUp(); // ȸ������ ��� �Լ�

void showBookList(); // ��� ����
void searchBook(); // ���� �˻�

// ������� �̱��� �Լ���
void handleBorrow(); // ���� ����
void handleReturn(); // ���� �ݳ�
void viewBorrowHistory(); // ���� ����

void addBook(); // ���� ���
void removeBook(); // ���� ����
void viewBorrowRecords(); // ���� ���� ��ȸ
void viewOverRecords(); // ��ü ���� ��ȸ

/*
    ���� �Լ�
*/
int main()
{
    mainLogin();
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
    ���� ���� �Լ� (member.txt)
*/
int manageMemberFile(Member members[], Member newMember, int mode)
{
    FILE* file;
    int count = 0;
    if (mode == 0) // ���� read
    {
        file = fopen("member.txt", "r");
        if (file == NULL)
        {
            setColor(12); gotoxy(14, 19); printf("ȸ�� ������ ������ �����ϴ�.");
            setColor(7); gotoxy(14, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %s", members[count].name, members[count].phone, members[count].password) == 3)
        {
            count++;
        }

        fclose(file);
        return count;
    }

    else if (mode == 1) // ���� append
    {
        file = fopen("member.txt", "a");
        if (file == NULL)
        {
            setColor(12); gotoxy(14, 19); printf("ȸ�� ������ ������ �����ϴ�.");
         
            
            setColor(7);  gotoxy(14, 20); system("pause");
           
            return 0;
        }
        
        fprintf(file, "\n%s %s %s", newMember.name, newMember.phone, newMember.password);
        fclose(file);

        return 1;
    }
    return 0;
}

/*
    ���� ���� �Լ� (book.txt)
*/
int manageBookFile(Book books[], Book newBook, int mode)
{

    int count = 0;
    FILE* file;

    if (mode == 0) // ���� read
    {
        file = fopen("book.txt", "r");
        if (file == NULL)
        {
            setColor(12); gotoxy(14, 19); printf("������ ������ �����ϴ�.");
            setColor(7); gotoxy(14, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %s %s", books[count].id, books[count].bookTitle, books[count].bookAuthor, books[count].bookPublish) == 4)
        {
            count++;
        }

        fclose(file);
        return count;
    }

    else if (mode == 1) // ���� append
    {
        // ���� �߰�
        file = fopen("book.txt", "a");
        if (file == NULL)
        {
            setColor(12); gotoxy(14, 19); printf("������ ������ �����ϴ�.");
            setColor(7); gotoxy(14, 20); system("pause");
            return 0;
        }

        fprintf(file, "\n%s %s %s %s", newBook.id, newBook.bookTitle, newBook.bookAuthor, newBook.bookPublish);
        fclose(file);

        return 1;
    }

    else if (mode == 2) // ����� write
    {
        // ���� ����
        file = fopen("borrowList.txt", "w");
        if (file == NULL)
        {
            setColor(12); gotoxy(14, 19); printf("������ ������ �����ϴ�.");
            setColor(7); gotoxy(14, 20); system("pause");
            return 0;
        }

        while (books[count].id[0] != '\0') // å ����� ���� �����ϸ� ��!
        {
            count++;
        }

        fclose(file);
        return 1;
    }
    return 0;
}

/*
    ���� ���� �Լ� (borrowList.txt)
*/
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // ���� �б�
    {
        file = fopen("borrowList.txt", "r");

        if (file == NULL)
        {
            setColor(12);  gotoxy(14, 19); printf("���� ������ ������ �����ϴ�."); 
            setColor(7); gotoxy(14, 20); system("pause");
            return 0;
        }

        while (fscanf(file, "%s %s %d %d %d %d %d %d %d",
            borrowList[count].id, borrowList[count].borrowerPhone,
            &borrowList[count].borrowYear, &borrowList[count].borrowMonth, &borrowList[count].borrowDay,
            &borrowList[count].returnYear, &borrowList[count].returnMonth,  &borrowList[count].returnDay,
            &borrowList[count].state) == 9)
        {
            count++;
        }

        fclose(file);
        return count;
    }
    else if (mode == 1) // ���� �߰�
    {
        file = fopen("borrowList.txt", "a");
        if (file == NULL)
        {
          
            setColor(12);  gotoxy(14, 19); printf("���� ������ ������ �����ϴ�.");
           
            setColor(7); gotoxy(14, 20); system("pause");
            
            return 0;
        }

        fprintf(file, "\n%s %s %d %d %d %d %d %d %d",
            newBorrow.id,
            newBorrow.borrowerPhone,
            newBorrow.borrowYear,
            newBorrow.borrowMonth,
            newBorrow.borrowDay,
            newBorrow.returnYear,
            newBorrow.returnMonth,
            newBorrow.returnDay,
            newBorrow.state);
        fclose(file);
        return 1;
    }
    else if (mode == 2) // ���� �����
    {
        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL)
        {
          
            setColor(12);   gotoxy(14, 19); printf("�ӽ� ���� ���� ������");
            setColor(7); gotoxy(13, 20); system("pause");
            
            return 0;
        }

        // borrowCount�� ����� ��ȿ�� �׸� ������ �� �ִٰ� ��

        for (int i = 0; i < borrowCount; i++)
        {
            if (i == 0) // �� ���Ͽ� ���� ���� �� 
            {
                fprintf(tempFile, "%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
            else
            {
                fprintf(tempFile, "\n%s %s %d %d %d %d %d %d %d",
                    borrowList[i].id, borrowList[i].borrowerPhone,
                    borrowList[i].borrowYear, borrowList[i].borrowMonth, borrowList[i].borrowDay,
                    borrowList[i].returnYear, borrowList[i].returnMonth, borrowList[i].returnDay,
                    borrowList[i].state);
            }
        }

        fclose(tempFile);
    }
    return 0;
}

/*
    �簢�� �ڽ� ��� �Լ�
*/
void drawBox(int x, int y, int width, int height, char text[])
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

    drawBox(22, 12, 16, 3, " 2. ȸ������"); // ȸ������ ��ư �ڽ�

    setColor(12);
    drawBox(22, 16, 16, 3, " 3. ����"); // ���� ��ư �ڽ�
    setColor(7);

    // ��ȣ �Է� ĭ ��� ���� ��
    gotoxy(10, 21); printf("��������������������������������������������������������������������������������");

    // �ϴ� �׵θ�
    gotoxy(10, 23); printf("��������������������������������������������������������������������������������");
}

/*
    ���� ȭ�� (��ó�� ȭ��)
*/
int mainLogin()
{
    char input[10];

    while (1)  // ���� �ݺ� (���� : ȸ������ �Ϸ��ϰ� ����� �ٽ� ���ƿ;� ��, �ݺ����� ������ ȸ������ �Ϸ� �� ���α׷��� �����)
    {
        drawMainMenu(); // ���� ȭ�� ���

        gotoxy(13, 22);
        printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == '1')
        {
            selectLogin();
        }
        else if (input[0] == '2')
        {
            signUp();
        }
        else if (input[0] == '3')
        {
            return 0;
        }
        else
        {
            gotoxy(13, 22);
            setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(13, 20); system("pause");
        }
    }
    return 0;
}

/*
    �α��� ���� ȭ��
*/
int selectLogin()
{
    char input[10];

    drawMainMenu(); // ���� ȭ�� ���

    drawBox(10, 2, 40, 3, "�α��� ����");
    drawBox(22, 8, 16, 3, " 1. �����"); // ����� �α���
    drawBox(22, 12, 16, 3, " 2. ������"); // ������ �α���

    setColor(12);
    drawBox(22, 16, 16, 3, " 3. �ڷ� ����"); // ���� ȭ������ ���ư���
    setColor(7);

    gotoxy(13, 22);
    printf("��ȣ �Է� : ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == '1')
    {
        if (login())  // �α���
        {
            userMenu(); // �α��� ���� �� ����� �޴��� �̵�
            return 1;
        }
    }
    else if (input[0] == '2')
    {
        if (login())  // �α���
        {
            adminMenu(); // �α��� ���� �� ������ �޴��� �̵�
            return 1;
        }
    }
    else if (input[0] == '3')
    {
        return 1;
    }
    else
    {
        gotoxy(13, 22);
        setColor(12);
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
        setColor(7);
        gotoxy(13, 20); system("pause");
    }
    return 0;
}

/*
    �α��� �� ����� �޴� ȭ��
*/
int userMenu()
{
    char welcome[60];
    char input[10];

    while (1)
    {
        system("cls");
        setColor(7);

        drawBox(10, 2, 40, 3, "������ ���� ���α׷�"); // ��ü ���� �ڽ�
        drawBox(10, 5, 40, 19, "");

        sprintf(welcome, "    %s ��, ȯ���մϴ�!", currentUser); // sprintf -> welcome �迭�� " currentUser�� ȯ���մϴ�!" ���ڿ� �����ϴ� ��
        setColor(10);
        gotoxy(17, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(14, 8, 16, 5, ""); // ���� ����
        gotoxy(16, 10); printf("1. ���� ����");

        drawBox(31, 8, 16, 5, ""); // ���� �ݳ�
        gotoxy(33, 10); printf("2. ���� �ݳ�");
        setColor(7);

        setColor(3);
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

        gotoxy(10, 21); printf("��������������������������������������������������������������������������������");
        gotoxy(13, 22); printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(10, 23); printf("��������������������������������������������������������������������������������");

        if (input[0] == '1')
        {
            handleBorrow();
        }
        else if (input[0] == '2')
        {
            handleReturn();
        }
        else if (input[0] == '3')
        {
            showBookList();
        }
        else if (input[0] == '4')
        {
            searchBook();
        }
        else if (input[0] == '5')
        {
            viewBorrowHistory();
        }
        else if (input[0] == '6')
        {
            return 0;
        }
        else
        {
            gotoxy(13, 22); setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(13, 20); system("pause");
        }
    }
}

/*
    �α��� �� ������ �޴� ȭ��
*/
int adminMenu()
{
    char welcome[60];
    char input[10];

    while (1)
    {
        system("cls");
        setColor(7);

        drawBox(10, 2, 40, 3, "������ ���� ���α׷�");
        drawBox(10, 5, 40, 19, "");

        sprintf(welcome, "    %s ��, ȯ���մϴ�.", currentUser);
        setColor(10);
        gotoxy(17, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(14, 8, 16, 5, ""); // ���� ���
        gotoxy(16, 10); printf("1. ���� ���");

        drawBox(31, 8, 16, 5, ""); // ���� ����
        gotoxy(33, 10); printf("2. ���� ����");
        setColor(7);

        setColor(3);
        drawBox(14, 13, 16, 5, ""); // ��ü ���� ����
        gotoxy(16, 15); printf("3. ���� ����");

        drawBox(31, 13, 16, 5, ""); // ��ü ��ü ����
        gotoxy(33, 15); printf("4. ��ü ����");
        setColor(7);

        setColor(12);
        drawBox(23, 18, 15, 3, ""); // �ڷΰ���
        gotoxy(25, 19); printf("5. �ڷ� ����");
        setColor(7);

        gotoxy(10, 21); printf("��������������������������������������������������������������������������������");
        gotoxy(13, 22); printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(10, 23); printf("��������������������������������������������������������������������������������");

        if (input[0] == '1')
        {
            addBook();
        }
        else if (input[0] == '2')
        {
            removeBook();
        }
        else if (input[0] == '3')
        {
            viewBorrowRecords();
        }
        else if (input[0] == '4')
        {
            viewOverRecords();
        }
        else if (input[0] == '5')
        {
            return 0;
        }
        else
        {
            gotoxy(13, 22); setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(13, 20); system("pause");
        }
    }
}

/*
    ��¥ ���
*/
void getDate(int offset)
{
    time_t now = time(NULL);
    struct tm date = *localtime(&now);

    date.tm_mday += offset;
    mktime(&date); // ��¥ ����

    year = date.tm_year + 1900;
    month = date.tm_mon + 1;
    day = date.tm_mday;
}

/*
    �α��� ���
*/
int login()
{
    char name[20], phone[20], password[20];
    Member null = { 0 };
    int count = manageMemberFile(members, null, 0);
    if (count == 0)
    {

        return 0;
    }

    system("cls");
    drawBox(10, 2, 40, 3, "�α���");
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

    for (int i = 0; i < count; i++)
    {
        if (strcmp(name, members[i].name) == 0 &&
            strcmp(phone, members[i].phone) == 0 &&
            strcmp(password, members[i].password) == 0)
        {
            check = 1; 
            break;
        }
    }

    if (check)
    {
        strcpy(currentUser, name);
        strcpy(currentPhone, phone);
        return 1;
    }
    else
    {
        gotoxy(14, 19);
        setColor(12);
        printf("�α��� ����: ������ ��ġ���� �ʽ��ϴ�.\n");
        setColor(7);
        gotoxy(13, 20); system("pause");
        return 0;
    }
}

/*
    ȸ������ ���
*/
void signUp()
{
    Member newMember = { 0 };
    Member null = { 0 };
    int count = manageMemberFile(members, null, 0);

    system("cls");
    drawBox(10, 2, 40, 3, "ȸ������");
    drawBox(10, 5, 40, 19, "");
    drawBox(12, 6, 36, 17, "");

    gotoxy(14, 7); printf("�̸�        : ");
    fgets(newMember.name, sizeof(newMember.name), stdin); // ���ͱ��� �Է¹���
    newMember.name[strcspn(newMember.name, "\n")] = 0; // \n�� ��ġ�� �ε����� ã�� �� ��ġ�� \0���� ���ڿ� ���� ���� �� �ִ�. -> \n�� ���ڿ� ������ �ٲ��ش�. -> \n ����

    while (1)
    {
        int check = 0;

        gotoxy(14, 11); printf("��ȭ��ȣ    : ");
        fgets(newMember.phone, sizeof(newMember.phone), stdin);
        newMember.phone[strcspn(newMember.phone, "\n")] = 0;

        for (int i = 0; i < count; i++)
        {
            if (strcmp(newMember.phone, members[i].phone) == 0)
            {
                check = 1;
                gotoxy(14, 19);
                setColor(12);
                printf("�̹� ��ϵ� ��ȭ��ȣ�Դϴ�.");
                setColor(7);
                gotoxy(13, 20); system("pause");
                gotoxy(24, 11); printf("                    ");
                break;
            }
        }
        if (check == 0)
        {
            break;
        }
    }

    gotoxy(14, 15); printf("��й�ȣ    : ");  
    fgets(newMember.password, sizeof(newMember.password), stdin);
    newMember.password[strcspn(newMember.password, "\n")] = 0;

    int check = manageMemberFile(NULL, newMember, 1);

    if (check == 1)
    {
        setColor(10);
        gotoxy(14, 19); printf("                           ");
        gotoxy(14, 19); printf("ȸ������ �Ϸ�");
        setColor(7);
        gotoxy(13, 20); system("pause");
    }
    else
    {
        gotoxy(14, 19);
        setColor(12);
        printf("ȸ�� ���� ���� ����");
        setColor(7);
        gotoxy(13, 20); system("pause");
    }
}

/*
    *************
    �̱��� �Լ���
    *************
*/

/*
    ���� ���� ��� (�̱���)
*/
void handleBorrow()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0); // ���� ��� �ҷ�����
    char borrowId[10];

    showBookList(); // ���� ��� ��� (����Ű Ž�� �� ID �Է� ����)

    system("cls");
    setColor(3);
    drawBox(10, 5, 60, 3, "���� ����");
    setColor(7);
    drawBox(10, 8, 60, 11, "");

    gotoxy(12, 9); printf("������ ������ ��ȣ(ID)�� �Է��ϼ��� (0 : ���) : ");
    fgets(borrowId, sizeof(borrowId), stdin);
    borrowId[strcspn(borrowId, "\n")] = 0;

    if (borrowId == 0)
    {
        return;
    }

    int found = 0;

    // ���� ��Ͽ��� �Է��� ID ã��
    for (int i = 0; i < count; i++)
    {
        if (strcmp(borrowId, books[i].id) == 0)
        {
            found = 1;

            Borrow newBorrow = { 0 };
            strcpy(newBorrow.id, borrowId);
            strcpy(newBorrow.borrowerPhone, currentPhone);

            // ��¥ ���
            getDate(0); // ����
            newBorrow.borrowYear = year;
            newBorrow.borrowMonth = month;
            newBorrow.borrowDay = day;

            getDate(10); // �ݳ����� 10�� ���� ���
            newBorrow.returnYear = year;
            newBorrow.returnMonth = month;
            newBorrow.returnDay = day;
            newBorrow.state = 1; // 1 : ���� ������ ��Ÿ������

            // ���� ���� ���� (manageBorrowFile �Լ� �̿�)
            if (manageBorrowFile(NULL, newBorrow, 1, NULL) == 1)
            {
                setColor(10);
                gotoxy(12, 12); printf("������ �Ϸ�Ǿ����ϴ�!");
                gotoxy(12, 13); printf("�ݳ� ���� : %d�� %d�� %d�ϱ���", year, month, day);
                setColor(7);
            }
            else
            {
                setColor(12);
                gotoxy(12, 12);  printf("���� ���� ���� ����.");
                setColor(7);
            }
            break;
        }
    }

    if (found == 0)
    {
        gotoxy(12, 12); printf("�ش� ID�� ������ ã�� �� �����ϴ�.");
    }

    gotoxy(12, 15); printf("����Ϸ��� �ƹ� Ű�� ��������...");
    _getch();
}

/*
    ���� �ݳ� ��� (�ݳ��� ���� ��ȣ�� �Է�) (�̱���)
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 }; // �ʱ�ȭ�� ���ϸ� �ݳ��� �ȵǴ� ���� �߻��ϹǷ� �ʼ�;;
    Borrow nullBorrow = { 0 };
    Book nullBook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // ���� ��� �ҷ�����
    int bookCount = manageBookFile(books, nullBook, 0); // ���� ��� �ҷ�����
    if (borrowCount == 0)
    {
        gotoxy(12, 7); printf("���� �����Ͱ� �����ϴ�.");
        gotoxy(12, 9); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
        _getch();
        return;
    }

    system("cls");
    setColor(3);
    drawBox(10, 2, 60, 3, "���� �ݳ�");
    setColor(7);
    drawBox(10, 5, 60, 22, "");
    gotoxy(10, 24); printf("������������������������������������������������������������������������������������������������������������������������");

    // �α����� ����ڰ� ���� å�� �����ϱ� ���ؼ� ������ �κ� ,
    int userBorrowList[1000]; 
    int userCount = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        // �α����� ��ȭ��ȣ�� ��ġ�ϴ� ���
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0)
        {
            userBorrowList[userCount] = i;
            userCount++;
        }
    }

    if (userCount == 0)
    {
        gotoxy(12, 7); printf("���� ���� ���� ������ �����ϴ�.");
        gotoxy(12, 9); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
        _getch();
        return;
    }

    gotoxy(12, 6); printf("���� ���� ���� ��� :");

    // ui ��ġ������
    int b = 8;
    int c = 9;

    for (int i = 0; i < userCount; i++)
    {
        int idx = userBorrowList[i];
        char copyTitle[50] = { 0 };

        for (int j = 0; j < bookCount; j++)
        {
            // ���� ������ �ִ� å ��ȣ�� å ������ �ִ� å ��ȣ�� ��
            if (strcmp(borrowList[idx].id, books[j].id) == 0)
            {
                strcpy(copyTitle, books[j].bookTitle);
                break;
            }
        }

        setColor(10);
        drawBox(11, b, 58, 3, "");
        gotoxy(12, c); printf(" %d��%-20s��%d-%d-%d", i + 1, copyTitle,
            borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay);
        setColor(7);

        b += 3;
        c += 3;
    }

    char input[10];

    gotoxy(12, 25); printf("�ݳ��� ��ȣ �Է� (0 : ���) : ");
    fgets(input, sizeof(input), stdin);

    int select = atoi(input); // �� �̷��� �ؾߵɱ�? atoi�� ���� ���� ��ȯ�� �ȴ���

    if (select == 0)
    {
        return;
    }

    if (select > userCount || select < 0)
    {
        setColor(12); gotoxy(12, 22); printf("�߸��� ��ȣ �Է��Դϴ�.");
        setColor(7); gotoxy(12, 23); printf("�ƹ� Ű�� ������ ���ư��ϴ�..");
        _getch();
        return;
    }

    // �����ϴ� ����
    int removeIndex = userBorrowList[select - 1]; // select���� -1�� ���ϸ� �ε��� 0������ �ȳ��� ��

    for (int i = removeIndex; i < borrowCount - 1; i++)
    {
        // ����� ���� �� �ؿ� �ִ� ����� �� �پ� ��ܿͼ� ������ ����ε� �� ��
        borrowList[i] = borrowList[i + 1];
    }
    borrowCount --; // ���� �׸�� ����

    // borrowList.txt�� �����ϴ� ����
    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount))
    {
        setColor(10); gotoxy(12, 22); printf("������ ���������� �ݳ��Ǿ����ϴ�!");
        setColor(7);
    }

    gotoxy(12, 23); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
    _getch();
}

/*
    ���� ��� ��ȸ ���
*/
void showBookList()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0); // ���� ������ ��ȣ �����
    int startIndex = 0;
    char input[10];
    char titleShort[30];

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(10, 2, 60, 3, "���� ���");
        setColor(7);
        drawBox(10, 5, 60, 22, "");

        gotoxy(11, 6); printf("��ȣ������                ������            �����ǻ�");
        gotoxy(10, 7); printf("������������������������������������������������������������������������������������������������������������������������");

        for (int i = 0; i < 15; i++)
        {
            // startIndex�� ù ����� ����Ŵ, i�� ���ؼ� ���������� �����
            int bookIndex = startIndex + i;
            
            if (bookIndex >= count)
            {
                break; // ��ü ���� ���� ������(å�� �� ������) �ߴ��ϴ� ���
            }

            // ���� �ڸ��� (10���� �ʰ� �� 7���ڿ��ٰ� ������ǥ)
            if (strlen(books[bookIndex].bookTitle) > 25)
            {
                snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bookIndex].bookTitle);
            }
            else
            {
                strcpy(titleShort, books[bookIndex].bookTitle);
            }

            // ������ ���
            setColor(3);
            gotoxy(12, 8 + i);
            printf(" %-2s��%-20s��%-16s��%-5s\n", books[bookIndex].id, titleShort,
                books[bookIndex].bookAuthor, books[bookIndex].bookPublish);
            setColor(7);
        }

        gotoxy(10, 24); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(10, 26); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(13, 25); printf("[0] �ڷ� ����");
    
        char key = _getch();

        if (key == 0 || key == -32)  // -32 �⺻ ���ε�
        {
            key = _getch();  // ���� Ű �� �д°�

            if (key == LEFT && startIndex >= 15)
            {
                startIndex = startIndex - 15; // 15 ���� ������ ��µ� 15���� ��� �����Բ�
            }

            else if (key == RIGHT && startIndex + 15 < count)
            {
                startIndex = startIndex + 15;
            }
        }
        else if (key == '0')  // �ڷΰ���
        {
            return;
        }
    }
}

/*
    ���� �˻� ���
*/
void searchBook()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0); // ���� ���� �ҷ�����
    char word[50];

    while (1)
    {
        // ui ����
        system("cls");
        setColor(3);
        drawBox(10, 2, 60, 3, "���� �˻�");
        setColor(7);

        drawBox(10, 5, 60, 22, "");
        gotoxy(10, 7); printf("������������������������������������������������������������������������������������������������������������������������");

        gotoxy(11, 8); printf(" ��ȣ�� ����                 �� ����             �� ���ǻ�");
        gotoxy(10, 9); printf("������������������������������������������������������������������������������������������������������������������������");

        // �˻�
        gotoxy(11, 6); printf("�˻��� ���� ���� �Ǵ� ���� (�ڷ� ���� : 0) : ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = 0; // ���� �����ϴ¤�  �װ�

        if (strcmp(word, "0") == 0)
        {
            break; // ����
        }
        
        int check = 0;
        int b = 10;
        int c = 11;

        for (int i = 0; i < count; i++)
        {
            if (strstr(books[i].bookTitle, word) || strstr(books[i].bookAuthor, word))
            {
                check++;

                setColor(10);
                drawBox(11, b, 58, 3, ""); 
                gotoxy(12, c); printf(" %-2s �� %-20s �� %-16s �� %-5s\n", books[i].id,
                    books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
                setColor(7);

                b += 3;
                c += 3;
            }
        }

        if (check == 0)
        {
            setColor(12);
            gotoxy(12, 24); printf("�ش� Ű����� ��ġ�ϴ� ������ ã�� �� �����ϴ�.\n");
            setColor(7);
        }
        gotoxy(12, 24); printf("�ƹ� Ű�� ������ �ٽ� �˻��մϴ�.");
        _getch();
    }
}

/*
    ���� ��ȸ ���(�����) (Ű�� �����ϰ� Ȯ��) (�̱���)
*/
void viewBorrowHistory()
{
    char input[10];

    system("cls");
    drawBox(10, 2, 60, 3, "���� ��ȸ");
    drawBox(10, 5, 60, 19, "");

    for (int i = 0; i < 10; i++)
    {
        gotoxy(14, 7 + i);
        printf("%d.", i + 1);
    }

    gotoxy(10, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(10, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(13, 22); printf("[1] ���� [2] ���� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == '0')
    {
        return; // �ڷΰ���
    }
}

/*
    ���� �߰� ��� (���� ����(����, ����, ���ǻ�) ���ʴ�� �Է� �� ����) (�Ϻ� ����)
*/
void addBook()
{
    char input[100];
    char newTitle[50], newAuthor[30], newPublish[20];
    char newId[10];
    int count = 0; // ������ ���� ��ȣ �����

    FILE* file = fopen("book.txt", "r");
    if (file != NULL)
    {
        while (fscanf(file, "%s %s %s %s", books[count].id, books[count].bookTitle,
            books[count].bookAuthor, books[count].bookPublish) == 4)
        {
            count++;
        }
        sprintf(newId, "%d", count + 1);
        fclose(file);
    }

    system("cls");
    setColor(3);
    drawBox(10, 2, 60, 3, "���� �߰�");
    setColor(7);
    drawBox(10, 5, 60, 19, "");
    gotoxy(10, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(10, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(13, 22); printf("[1] ���� �߰� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == '0')
    {
        return;
    }
    else if (input[0] == '1')
    {
        gotoxy(14, 7);  printf("����        : ");
        fgets(newTitle, sizeof(newTitle), stdin); // ���ͱ��� �Է¹���
        newTitle[strcspn(newTitle, "\n")] = 0; // \n ����
    
        gotoxy(14, 11); printf("����        : ");
        fgets(newAuthor, sizeof(newAuthor), stdin);
        newAuthor[strcspn(newAuthor, "\n")] = 0;
        
        gotoxy(14, 15); printf("���ǻ�      : ");
        fgets(newPublish, sizeof(newPublish), stdin);
        newPublish[strcspn(newPublish, "\n")] = 0;
    
        FILE* file = fopen("book.txt", "a");

        if (file == NULL)
        {
            gotoxy(14, 19);
            setColor(12);
            printf("���� �߰� ����.");
            setColor(7);
            gotoxy(13, 20); system("pause");
            return;
        }

        fprintf(file, "\n%s %s %s %s", newId, newTitle, newAuthor, newPublish);
        fclose(file);

        gotoxy(14, 19);
        setColor(10);
        printf("���� �߰��� �Ϸ�Ǿ����ϴ�.");
        setColor(7);
    }
    gotoxy(13, 20); system("pause");
}

/*
    ���� ���� ��� (���� ��ȣ(1, 2, 3...) �Է��ؼ� ����) (�̱���)
*/
void removeBook()
{
    char input[10];

    system("cls");
    drawBox(10, 2, 60, 3, "���� ����");
    drawBox(10, 5, 60, 19, "");

    for (int i = 0; i < 10; i++)
    {
        gotoxy(14, 8 + i);
        printf("%d.", i + 1);
    }

    gotoxy(10, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(10, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(13, 22); printf("[1] ���� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == '0')
    {
        return;
    }
    else if (input[0] == '1')
    {
        gotoxy(13, 22); printf("������ ���� ��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(13, 20); system("pause");
    }
}

/*
    ���� ��ȸ ��� (������) (Ű�� �����ϰ� Ȯ��) (�̱���)
*/
void viewBorrowRecords()
{
    char input[10];

    system("cls");
    drawBox(10, 2, 60, 3, "���� ��ȸ (������)");
    drawBox(10, 5, 60, 19, "");

    for (int i = 0; i < 10; i++)
    {
        gotoxy(14, 8 + i);
        printf("%d.", i + 1);
    }

    gotoxy(10, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(10, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(13, 22); printf("[2] ���� [1] ���� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == 0)
    {
        return;
    }
}

/*
    ��ü ��ȸ ��� (�̱���)
*/
void viewOverRecords()
{
    char input[10];

    system("cls");
    drawBox(10, 2, 60, 3, "��ü ��ȸ");
    drawBox(10, 5, 60, 19, "");

    for (int i = 0; i < 10; i++)
    {
        gotoxy(14, 8 + i);
        printf("%d.", i + 1);
    }

    gotoxy(10, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(10, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(13, 22); printf("[1] ���� [2] ���� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == 0)
    {
        return;
    }
}

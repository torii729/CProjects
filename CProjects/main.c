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
    ���� ���� ����...
*/
Member members[1000];
Book books[1000];
char currentUser[20]; // ���� �α����� ����� �̸� �����
char currentPhone[20]; // ���� �α����� ����� ��ȭ��ȣ �����
int year, month, day;

/*
    �Լ� �����
*/
void gotoxy(int x, int y); // �ܼ� Ŀ�� �̵� �Լ� (xy ��ǥ)
void setColor(int color); // �ܼ� ���� ���� ���� �Լ�
int manageMemberFile(Member members[], Member newMember, int mode); // member.txt ���� �аų� �߰� �Լ�
int manageBookFile(Book books[], Book newBook, int mode, int bookCount); // book.txt ���� �аų� �߰� �Լ�
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount); // borrowList.txt ���� �аų� �߰� �Լ�
void getDate(int offset); // ��¥ ��� �Լ�
void drawBox(int x, int y, int w, int h, char text[]); // �簢�� �ڽ� �׸��� �Լ�
void drawMainMenu(); // �ʱ� ���� �޴� UI ��� �Լ�

int mainLogin(); // ���� ȭ�� (��ó�� ȭ��)
int selectLogin(); // �α��� ���� (�����? ������?)
int userMenu(); // �α��� �� "�����" ���� �޴� �Լ�
int adminMenu(); // �α��� �� "������" ���� �޴� �Լ�

int login(); // �α��� ��� �Լ�
void signUp(); // ȸ������ ��� �Լ�

void showBookList(); // ��� ����
void searchBook(); // ���� �˻�
void handleBorrow(); // ���� ����
void handleReturn(); // ���� �ݳ�
void viewBorrowHistory(); // ���� ����

void addBook(); // ���� ���
void removeBook(); // ���� ����
void viewBorrowRecords(); // ����/��ü ���� ��ȸ

/*
    ���� �Լ�
*/
int main()
{
    Borrow list[1000] = { 0 };
    Borrow null = { 0 };
    int borrowCount = manageBorrowFile(list, null, 0, 0); // ��ü ���� ��� �ҷ�����

    getDate(0); // ���� ��¥ (year, month, day)

    for (int i = 0; i < borrowCount; i++)
    {
        if (list[i].state == 1) // ���� ���̸�
        {
            // �ݳ� �������� ���� ��¥���� �ռ��� ��쿡 ��ü��(state�� 2��) �����ϤѴ� ���ǹ�
            if (list[i].returnYear < year
                || (list[i].returnYear == year && list[i].returnMonth < month)
                || (list[i].returnYear == year && list[i].returnMonth == month && list[i].returnDay < day))
            {
                list[i].state = 2; // ��ü�� ����
            }
        }
    }
    manageBorrowFile(list, null, 2, borrowCount); // ���� ����� ����

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
            setColor(12); gotoxy(42, 19); printf("ȸ�� ������ ������ �����ϴ�.");
            setColor(7); gotoxy(42, 20); system("pause");
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
            setColor(12); gotoxy(42, 19); printf("ȸ�� ������ ������ �����ϴ�.");
         
            
            setColor(7);  gotoxy(42, 20); system("pause");
           
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
int manageBookFile(Book books[], Book newBook, int mode, int bookCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // ���� read
    {
        file = fopen("book.txt", "r");
        if (file == NULL)
        {
            setColor(12); gotoxy(42, 19); printf("������ ������ �����ϴ�.");
            setColor(7); gotoxy(42, 20); system("pause");
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
            setColor(12); gotoxy(42, 19); printf("������ ������ �����ϴ�.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }

        fprintf(file, "\n%s %s %s %s", newBook.id, newBook.bookTitle, newBook.bookAuthor, newBook.bookPublish);
        fclose(file);

        return 1;
    }

    else if (mode == 2) // ���� �����
    {
        FILE* tempBookFile = fopen("tempBook.txt", "w");
        if (tempBookFile == NULL)
        {
            setColor(12);   gotoxy(42, 19); printf("�ӽ� ���� ���� ������");
            setColor(7); gotoxy(42, 20); system("pause");

            return 0;
        }

        // borrowCount�� ����� ��ȿ�� �׸� ������ �� �ִٰ� ��

        for (int i = 0; i < bookCount; i++)
        {
            if (i == 0) // �� ���Ͽ� ���� ���� �� 
            {
                fprintf(tempBookFile, "%s %s %s %s", books[i].id, books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
            }
            else
            {
                fprintf(tempBookFile, "\n%s %s %s %s", books[i].id, books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
            }
        }
        fclose(tempBookFile);

        if (remove("book.txt") != 0 || rename("tempBook.txt", "book.txt") != 0)
        {
            setColor(12); gotoxy(42, 19); printf("���� ���� ����.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }
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
            setColor(12);  gotoxy(42, 19); printf("���� ������ ������ �����ϴ�."); 
            setColor(7); gotoxy(42, 20); system("pause");
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
          
            setColor(12);  gotoxy(42, 19); printf("���� ������ ������ �����ϴ�.");
           
            setColor(7); gotoxy(42, 20); system("pause");
            
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
            setColor(12);   gotoxy(42, 19); printf("�ӽ� ���� ���� ������");
            setColor(7); gotoxy(42, 20); system("pause");
            
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

        if (remove("borrowList.txt") != 0 || rename("temp.txt", "borrowList.txt") != 0)
        {
            setColor(12); gotoxy(42, 19); printf("���� ���� ����.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
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

    drawBox(40, 2, 40, 3, "������ ���� ���α׷�"); // ��ü ���� �ڽ�
    drawBox(40, 5, 40, 19, "");

    drawBox(52, 8, 16, 3, " 1. �α���"); // �α��� ��ư �ڽ�

    drawBox(52, 12, 16, 3, " 2. ȸ������"); // ȸ������ ��ư �ڽ�

    setColor(12);
    drawBox(52, 16, 16, 3, " 3. ����"); // ���� ��ư �ڽ�
    setColor(7);

    // ��ȣ �Է� ĭ ��� ���� ��
    gotoxy(40, 21); printf("��������������������������������������������������������������������������������");

    // �ϴ� �׵θ�
    gotoxy(40, 23); printf("��������������������������������������������������������������������������������");
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

        gotoxy(42, 22);
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
            gotoxy(42, 22);
            setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(42, 20); system("pause");
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

    drawBox(40, 2, 40, 3, " �α��� ����");
    drawBox(52, 8, 16, 3, " 1. �����"); // ����� �α���
    drawBox(52, 12, 16, 3, " 2. ������"); // ������ �α���

    setColor(12);
    drawBox(52, 16, 16, 3, " 3. �ڷ� ����"); // ���� ȭ������ ���ư���
    setColor(7);

    gotoxy(42, 22);
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
        gotoxy(42, 22);
        setColor(12);
        printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
        setColor(7);
        gotoxy(42, 20); system("pause");
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
        //+30
        drawBox(40, 2, 40, 3, "������ ���� ���α׷�"); // ��ü ���� �ڽ�
        drawBox(40, 5, 40, 19, "");

        sprintf(welcome, "   %s ��, ȯ���մϴ�!", currentUser); // sprintf -> welcome �迭�� " currentUser�� ȯ���մϴ�!" ���ڿ� �����ϴ� ��
        setColor(10);
        gotoxy(47, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(44, 8, 16, 5, ""); // ���� ����
        gotoxy(46, 10); printf("1. ���� ����");

        drawBox(61, 8, 16, 5, ""); // ���� �ݳ�
        gotoxy(63, 10); printf("2. ���� �ݳ�");
        setColor(7);

        setColor(3);
        drawBox(44, 13, 11, 5, ""); // ���� ���
        gotoxy(46, 15); printf("3. ���");

        drawBox(55, 13, 11, 5, ""); // ���� �˻�
        gotoxy(57, 15); printf("4. �˻�");

        drawBox(66, 13, 11, 5, ""); // ���� ����
        gotoxy(68, 15); printf("5. ����");
        setColor(7);

        setColor(12);
        drawBox(53, 18, 15, 3, ""); // �ڷΰ���
        gotoxy(55, 19); printf("6. �α׾ƿ�");
        setColor(7);

        gotoxy(40, 21); printf("��������������������������������������������������������������������������������");
        gotoxy(43, 22); printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(40, 23); printf("��������������������������������������������������������������������������������");

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
            gotoxy(43, 22); setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(43, 20); system("pause");
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

        drawBox(40, 2, 40, 3, "������ ���� ���α׷�");
        drawBox(40, 5, 40, 19, "");

        sprintf(welcome, "    %s ��, ȯ���մϴ�.", currentUser);
        setColor(10);
        gotoxy(47, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(44, 8, 16, 5, ""); // ���� ���
        gotoxy(46, 10); printf("1. ���� ���");

        drawBox(61, 8, 16, 5, ""); // ���� ����
        gotoxy(63, 10); printf("2. ���� ����");
        setColor(7);

        setColor(3);
        drawBox(44, 13, 33, 5, ""); // ��ü ���� ����
        gotoxy(46, 15); printf("      3. ����/��ü ����");
        setColor(7);

        setColor(12);
        drawBox(53, 18, 15, 3, ""); // �ڷΰ���
        gotoxy(55, 19); printf("4. �α׾ƿ�");
        setColor(7);

        gotoxy(40, 21); printf("��������������������������������������������������������������������������������");
        gotoxy(43, 22); printf("��ȣ �Է� : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(40, 23); printf("��������������������������������������������������������������������������������");

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
            return 0;
        }
        else
        {
            gotoxy(43, 22); setColor(12);
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
            setColor(7);
            gotoxy(43, 20); system("pause");
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
    mktime(&date);

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
    drawBox(40, 2, 40, 3, "�α���");
    drawBox(40, 5, 40, 19, "");
    drawBox(42, 6, 36, 17, "");

    gotoxy(44, 7); printf("�̸�        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 11); printf("��ȭ��ȣ    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(44, 15); printf("��й�ȣ    : ");

    int idx = 0;
    char k;

    while (1)
    {
        k = _getch();

        if (k == 13) // ����ġ�� �Է� �Ϸ�
        {
            password[idx] = '\0'; // �������� ���ڿ����� �迭�� ���͸� ���� �������ν� �Ǵ��� �� ������...
            break;
        }
        else if (k == 8) // �齺���̽� ������ �������� �ϴµ�...
        {
            printf("\b \b"); // ??
        }
        else if (k >= 33 && k <= 126) // !���� ~�����ε� �����𸣰����� ��� ���� ����
        {
            // �Է��� ���ڸ� �����ϳ�, ������ ��µǴ� �� *��
            password[idx++] = k;
            printf("*");
        }
    }

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
        gotoxy(44, 19);
        setColor(12);
        printf("������ ��ġ���� �ʽ��ϴ�.\n");
        setColor(7);
        gotoxy(44, 20); system("pause");
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
    drawBox(40, 2, 40, 3, "ȸ������");
    drawBox(40, 5, 40, 19, "");
    drawBox(42, 6, 36, 17, "");

    while (1)
    {
        gotoxy(44, 7); printf("�̸�        : ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = 0;

        // �̸��� �������� üũ
        int empty = 1;
        for (int i = 0; newMember.name[i] != '\0'; i++)
        {
            if (newMember.name[i] != ' ' && newMember.name[i] != '\t')
            {
                empty = 0;
                break;
            }
        }
        if (empty)
        {
            setColor(12);
            gotoxy(44, 19); printf("�̸��� ������ �� �����ϴ�.");
            setColor(7);
            gotoxy(44, 20); system("pause");
            gotoxy(58, 7); printf("                    ");
            continue;
        }
        break;
    }

    while (1)
    {
        int check = 0;

        gotoxy(44, 11); printf("��ȭ��ȣ    : ");
        fgets(newMember.phone, sizeof(newMember.phone), stdin);
        newMember.phone[strcspn(newMember.phone, "\n")] = 0;

        int len = 0;
        int lastWasDash = 0;
        int validFormat = 1;

        for (; newMember.phone[len] != '\0'; len++)
        {
            char ch = newMember.phone[len];
            if (!((ch >= '0' && ch <= '9') || ch == '-'))
            {
                validFormat = 0;
                break;
            }
            if (ch == '-')
            {
                if (lastWasDash)
                {
                    validFormat = 0;
                    break;
                }
                lastWasDash = 1;
            }
            else
            {
                lastWasDash = 0;
            }
        }
        if (len == 0 || newMember.phone[0] == '-' || newMember.phone[len - 1] == '-')
            validFormat = 0;

        if (!validFormat)
        {
            setColor(12);
            gotoxy(44, 19); printf("��ȭ��ȣ ������ �ùٸ��� �ʽ��ϴ�.");
            setColor(7);
            gotoxy(44, 20); system("pause");
            gotoxy(58, 11); printf("                    ");
            continue;
        }

        for (int i = 0; i < count; i++)
        {
            if (strcmp(newMember.phone, members[i].phone) == 0)
            {
                check = 1;
                gotoxy(44, 19);
                setColor(12);
                printf("�̹� ��ϵ� ��ȭ��ȣ�Դϴ�.");
                setColor(7);
                gotoxy(44, 20); system("pause");
                gotoxy(58, 11); printf("                  ");
                break;
            }
        }
        if (check == 0) break;
    }

    while (1)
    {
        gotoxy(44, 15); printf("��й�ȣ    : ");
        fgets(newMember.password, sizeof(newMember.password), stdin);
        newMember.password[strcspn(newMember.password, "\n")] = 0;

        int hasSpace = 0;
        for (int i = 0; newMember.password[i] != '\0'; i++)
        {
            if (newMember.password[i] == ' ' || newMember.password[i] == '\t')
            {
                hasSpace = 1;
                break;
            }
        }
        if (hasSpace)
        {
            setColor(12);
            gotoxy(44, 19); printf("��й�ȣ�� ������ ������ �� �����ϴ�.");
            setColor(7);
            gotoxy(44, 20); system("pause");
            gotoxy(58, 15); printf("                 ");
            continue;
        }
        break;
    }

    int check = manageMemberFile(NULL, newMember, 1);

    if (check == 1)
    {
        setColor(10);
        gotoxy(43, 19); printf("                      ");
        gotoxy(44, 19); printf("ȸ������ �Ϸ�");
        setColor(7);
        gotoxy(44, 20); system("pause");
    }
}

/*
    ���� ���� ���
*/
void handleBorrow()
{
    Book nullbook = { 0 };
    Borrow nullborrow = { 0 };
    Borrow temp[1000] = { 0 };
    int count = manageBookFile(books, nullbook, 0, 0);
    int borrowCount = manageBorrowFile(temp, nullborrow, 0, 0);
    char borrowId[10];

    // ��ü ������ üũ
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(temp[i].borrowerPhone, currentPhone) == 0 && temp[i].state == 2) // state 2 = ��ü
        {
            system("cls");
            setColor(3);
            drawBox(30, 5, 60, 3, "���� ����");
            setColor(7);
            drawBox(30, 8, 60, 11, "");

            setColor(12);
            gotoxy(32, 12);
            printf("��ü ������ �־� ������ ���ѵ˴ϴ�.");
            setColor(7);
            gotoxy(32, 14);
            printf("����Ϸ��� �ƹ� Ű�� ��������...");
            _getch();
            return;
        }
    }

    // 3�� �̻� ���� ����
    int userBorrowCount = 0;
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(temp[i].borrowerPhone, currentPhone) == 0 && temp[i].state == 1)
        {
            userBorrowCount++;
        }
    }

    if (userBorrowCount >= 3)
    {
        system("cls");
        setColor(3);
        drawBox(30, 5, 60, 3, "���� ����");
        setColor(7);
        drawBox(30, 8, 60, 11, "");

        setColor(12);
        gotoxy(32, 12);
        printf("�̹� 3�� �̻� ���� ���Դϴ�. �� �̻� ������ �� �����ϴ�.");
        setColor(7);
        gotoxy(32, 14);
        printf("����Ϸ��� �ƹ� Ű�� ��������...");
        _getch();
        return;
    }

    showBookList();

    system("cls");
    setColor(3);
    drawBox(30, 5, 60, 3, "���� ����");
    setColor(7);
    drawBox(30, 8, 60, 11, "");

    gotoxy(32, 9);
    printf("������ ������ ��ȣ(ID)�� �Է��ϼ��� (0 : ���) : ");
    fgets(borrowId, sizeof(borrowId), stdin);
    borrowId[strcspn(borrowId, "\n")] = 0;

    int found = 0;

    for (int i = 0; i < count; i++)
    {
        if (strcmp(borrowId, books[i].id) == 0)
        {
            found = 1;

            for (int a = 0; a < borrowCount; a++)
            {
                if (strcmp(temp[a].id, borrowId) == 0 && temp[a].state == 1)
                {
                    setColor(12);
                    gotoxy(32, 12);
                    printf("�ش� ������ ���� ���� ���Դϴ�.");
                    setColor(7);
                    gotoxy(32, 14);
                    printf("����Ϸ��� �ƹ� Ű�� ��������...");
                    _getch();
                    return;
                }
            }

            Borrow newBorrow = { 0 };

            strcpy(newBorrow.id, borrowId);
            strcpy(newBorrow.borrowerPhone, currentPhone);

            getDate(0);
            newBorrow.borrowYear = year;
            newBorrow.borrowMonth = month;
            newBorrow.borrowDay = day;

            getDate(10);
            newBorrow.returnYear = year;
            newBorrow.returnMonth = month;
            newBorrow.returnDay = day;
            newBorrow.state = 1;

            if (manageBorrowFile(NULL, newBorrow, 1, 0) == 1)
            {
                setColor(10);
                gotoxy(32, 12);
                printf("������ �Ϸ�Ǿ����ϴ�!");
                gotoxy(32, 13);
                printf("�ݳ� ���� : %d�� %d�� %d�ϱ���", year, month, day);
                setColor(7);
            }
            else
            {
                setColor(12);
                gotoxy(32, 12);
                printf("���� ���� ���� ����.");
                setColor(7);
            }
            break;
        }
    }

    if (found == 0)
    {
        gotoxy(32, 12);
        printf("�ش� ID�� ������ ã�� �� �����ϴ�.");
    }

    gotoxy(32, 15);
    printf("����Ϸ��� �ƹ� Ű�� ��������...");
    _getch();
}

/*
    ���� �ݳ� ���
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 }; // �ʱ�ȭ�� ���ϸ� �ݳ��� �ȵǴ� ���� �߻��ϹǷ� �ʼ�;
    Borrow nullBorrow = { 0 };
    Book nullBook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // ���� ��� �ҷ�����
    int bookCount = manageBookFile(books, nullBook, 0, 0); // ���� ��� �ҷ�����
    if (borrowCount == 0)
    {
        gotoxy(32, 7); printf("���� �����Ͱ� �����ϴ�.");
        gotoxy(32, 9); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
        _getch();
        return;
    }

    system("cls");
    setColor(3);
    drawBox(30, 2, 60, 3, "���� �ݳ�");
    setColor(7);
    drawBox(30, 5, 60, 22, "");
    gotoxy(30, 24); printf("������������������������������������������������������������������������������������������������������������������������");

    // �α����� ����ڰ� ���� å�� �����ϱ� ���ؼ� ������ �κ� ,
    int userBorrowList[1000];
    int userCount = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        // �α����� ��ȭ��ȣ�� ��ġ�ϴ� ���
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0
                && borrowList[i].state == 1 || borrowList[i].state == 2)
        {
            userBorrowList[userCount] = i;
            userCount++;
        }
    }

    if (userCount == 0)
    {
        gotoxy(32, 7); printf("���� ���� ���� ������ �����ϴ�.");
        gotoxy(32, 9); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
        _getch();
        return;
    }

    gotoxy(31, 6); printf("��ȣ�� ����                           �� �ݳ� ������");
    gotoxy(30, 7); printf("������������������������������������������������������������������������������������������������������������������������");

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
        drawBox(31, b, 58, 3, "");
        gotoxy(32, c); printf(" %d �� %-30s �� %d-%d-%d", i + 1, copyTitle,
            borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay);
        setColor(7);

        b += 3;
        c += 3;
    }

    char input[10];

    gotoxy(32, 25); printf("�ݳ��� ��ȣ �Է� (0 : ���) : ");
    fgets(input, sizeof(input), stdin);

    int select = atoi(input); // atoi�� ���� ���� ��ȯ�� �ȴ��� �ű��� ��������

    if (select == 0)
    {
        return;
    }

    if (select > userCount || select < 1)
    {
        setColor(12); gotoxy(32, 22); printf("�߸��� ��ȣ �Է��Դϴ�.");
        setColor(7); gotoxy(32, 23); printf("�ƹ� Ű�� ������ ���ư��ϴ�..");
        _getch();
        return;
    }

    int idx = userBorrowList[select - 1]; // select���� -1�� ���ϸ� �ε��� 0������ �ȳ��� �� �Ф�

    borrowList[idx].state = 0; // ���� �ݳ� ó��

    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount))
    {
        setColor(10); gotoxy(32, 22); printf("������ ���������� �ݳ��Ǿ����ϴ�!");
    }

    gotoxy(32, 23); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
    _getch();
}

/*
    ���� ��� ��ȸ ���
*/
void showBookList()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0, 0); // ���� ������ ��ȣ �����
    int startIndex = 0;
    char input[10];
    char titleShort[30];

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "���� ���");
        setColor(7);
        drawBox(30, 5, 60, 22, "");

        gotoxy(31, 6); printf("��ȣ������                ������            �����ǻ�");
        gotoxy(30, 7); printf("������������������������������������������������������������������������������������������������������������������������");

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
            gotoxy(32, 8 + i);
            printf(" %-2s��%-20s��%-16s��%-5s\n", books[bookIndex].id, titleShort,
                books[bookIndex].bookAuthor, books[bookIndex].bookPublish);
            setColor(7);
        }

        gotoxy(30, 24); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(30, 26); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(33, 25); printf("[0] �ڷ� ����");

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
    int count = manageBookFile(books, null, 0, 0); // ���� ���� �ҷ�����
    char word[50];

    while (1)
    {
        // ui ����
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "���� �˻�");
        setColor(7);

        drawBox(30, 5, 60, 22, "");
        gotoxy(30, 7); printf("������������������������������������������������������������������������������������������������������������������������");

        gotoxy(31, 8); printf(" ��ȣ�� ����                 �� ����             �� ���ǻ�");
        gotoxy(30, 9); printf("������������������������������������������������������������������������������������������������������������������������");

        // �˻�
        gotoxy(31, 6); printf("�˻��� ���� ���� �Ǵ� ���� (�ڷ� ���� : 0) : ");
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
                drawBox(31, b, 58, 3, "");
                gotoxy(32, c); printf(" %-2s �� %-20s �� %-13s �� %-5s\n", books[i].id,
                    books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
                setColor(7);

                b += 3;
                c += 3;
            }
        }

        if (check == 0)
        {
            setColor(12);
            gotoxy(32, 23); printf("�ش� Ű����� ��ġ�ϴ� ������ ã�� �� �����ϴ�.\n");
            setColor(7);
        }
        gotoxy(32, 24); printf("�ƹ� Ű�� ������ �ٽ� �˻��մϴ�.");
        _getch();
    }
}

/*
    ���� ��ȸ ��� (�����) (���� ID ����)
*/
void viewBorrowHistory()
{
    Borrow borrowList[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    // ID ���� �������� ����
    for (int i = 0; i < borrowCount - 1; i++)
    {
        for (int j = i + 1; j < borrowCount; j++)
        {
            if (strcmp(borrowList[i].id, borrowList[j].id) > 0)
            {
                Borrow temp = borrowList[i];
                borrowList[i] = borrowList[j];
                borrowList[j] = temp;
            }
        }
    }


    Borrow userList[1000];

    int count1 = 0;
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0)
        {
            userList[count1++] = borrowList[i];
        }
    }

    int startIndex = 0;
    char title[31];

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(20, 1, 80, 3, "���� ���� ��ȸ");
        setColor(7);
        drawBox(20, 4, 80, 25, " ID | ����                           | ������      | �ݳ� ������  | ����     ");
        gotoxy(20, 6);
        printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������");

        int check = 0;

        for (int i = 0; i < 17; i++)
        {
            int recordIndex = startIndex + i;

            if (recordIndex >= count1)
            {
                break; // ���� ����� ��� ��
            }

            check = 1;

            strcpy(title, "(���� ����)");

            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(userList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(title, books[j].bookTitle);
                    break;
                }
            }

            if (userList[recordIndex].state == 2)
            {
                setColor(12); // ��ü
            }
            else if (userList[recordIndex].state == 1)
            {
                setColor(10); // ���� ��
            }
            else if (userList[recordIndex].state == 0)
            {
                setColor(8);  // �ݳ� �Ϸ�
            }
            else
            {
            setColor(7);
            }   

            gotoxy(22, 8 + i);
            printf("%-2s | %-30s | %d-%02d-%02d  | %d-%02d-%02d   | %s",
                userList[recordIndex].id, title,
                userList[recordIndex].borrowYear, userList[recordIndex].borrowMonth, userList[recordIndex].borrowDay,
                userList[recordIndex].returnYear, userList[recordIndex].returnMonth, userList[recordIndex].returnDay,
                userList[recordIndex].state == 0 ? "�ݳ� �Ϸ�" : (userList[recordIndex].state == 1 ? "���� ��" : "��ü ��"));
        }

        setColor(7);

        if (check == 0)
        {
            gotoxy(22, 8);
            printf("���� ������ �����ϴ�.");
        }

        gotoxy(20, 26);  printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������");
        gotoxy(22, 27); printf("[��] ���� ������  [��] ���� ������  [0] �ڷ� ����");

        char key = _getch();

        if (key == 0 || key == -32) // ����Ű
        {
            key = _getch();

            if (key == LEFT && startIndex >= 17)
            {
                startIndex -= 17;
            }
            else if (key == RIGHT && startIndex + 17 < count1)
            {
                startIndex += 17;
            }
        }
        else if (key == '0') // �ڷ� ����
        {
            return;
        }
    }
}

/*
    ���� �߰� ���
*/
void addBook()
{
    char input[100];
    Book newbook = { 0 };
    int count = manageBookFile(books, newbook, 0, 0);
    sprintf(newbook.id, "%d", count + 1);

    system("cls");
    setColor(3); drawBox(30, 2, 60, 3, "���� �߰�");
    setColor(7);
    drawBox(30, 5, 60, 19, "");
    gotoxy(30, 21); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(30, 23); printf("������������������������������������������������������������������������������������������������������������������������");
    gotoxy(33, 22); printf("[1] ���� �߰� [0] �ڷ� ���� : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == '0')
    {
        return;
    }
    else if (input[0] == '1')
    {
        gotoxy(33, 7);  printf("����        : ");
        fgets(newbook.bookTitle, sizeof(newbook.bookTitle), stdin); // ���ͱ��� �Է¹���
        newbook.bookTitle[strcspn(newbook.bookTitle, "\n")] = 0; // \n ����

        gotoxy(33, 11); printf("����        : ");
        fgets(newbook.bookAuthor, sizeof(newbook.bookAuthor), stdin);
        newbook.bookAuthor[strcspn(newbook.bookAuthor, "\n")] = 0;

        gotoxy(33, 15); printf("���ǻ�      : ");
        fgets(newbook.bookPublish, sizeof(newbook.bookPublish), stdin);
        newbook.bookPublish[strcspn(newbook.bookPublish, "\n")] = 0;

        // book.txt�� å �߰��ϱ�
        if (manageBookFile(NULL, newbook, 1, 0))
        {
            gotoxy(34, 19); setColor(10); printf("���� �߰��� �Ϸ�Ǿ����ϴ�.");
        }
        else
        {
            gotoxy(34, 19); setColor(12); printf("���� �߰� ����.");
        }
        setColor(7);
    }
    gotoxy(33, 20); system("pause");
}

/*
    ���� ���� ���
*/
void removeBook()
{
    Book nullbook = { 0 };
    int startIndex = 0;
    int removeIndex = 0;
    char input1[10] = { 0 };
    char input2[10] = { 0 };
    char titleShort[30];

    int count = manageBookFile(books, nullbook, 0, 0); // ���� ��� �б�

    if (count == 0)
    {
        gotoxy(12, 7); printf("���� �����Ͱ� �����ϴ�.");
        gotoxy(12, 9); printf("�ƹ� Ű�� ������ ���ư��ϴ�.");
        _getch();
        return;
    }

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "���� ����");
        setColor(7);
        drawBox(30, 5, 60, 22, "");

        gotoxy(31, 6); printf("��ȣ������                ������            �����ǻ�");
        gotoxy(30, 7); printf("������������������������������������������������������������������������������������������������������������������������");

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
            gotoxy(32, 8 + i);
            printf(" %-2s��%-20s��%-16s��%-5s\n", books[bookIndex].id, titleShort,
                books[bookIndex].bookAuthor, books[bookIndex].bookPublish);
            setColor(7);
        }

        gotoxy(30, 24); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(30, 26); printf("������������������������������������������������������������������������������������������������������������������������");
        gotoxy(33, 25); printf("[1] ������ ���� �Է� [0] �ڷ� ����");

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
            continue;
        }
        else if (key == '0')  // �ڷΰ���
        {
            return;
        }
        else if (key == '1')
        {
            gotoxy(47, 25); printf("                             ");
            gotoxy(33, 25); printf("������ ���� ��ȣ �Է� : ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = 0;

            int select = atoi(input1);

            if (select > count || select < 1)
            {
                gotoxy(34, 20); setColor(12); printf("�߸��� ��ȣ�Դϴ�.");
                setColor(7); _getch();
                continue;
            }

            removeIndex = select - 1;
        }

        system("cls");
        setColor(3); drawBox(30, 2, 60, 3, "���� ���� Ȯ��"); setColor(7);
        drawBox(30, 5, 60, 9, "");
        setColor(12); gotoxy(34, 7); printf("������ �����Ͻðڽ��ϱ�?"); setColor(7);
        gotoxy(34, 8); printf("����: %s", books[removeIndex].bookTitle);

        gotoxy(34, 9); printf("[Y] ��  [N] �ƴϿ�(�ڷ� ����) : ");
        fgets(input2, sizeof(input2), stdin);
        input2[strcspn(input2, "\n")] = 0;

        if (input2[0] == 'y')
        {
            for (int i = removeIndex; i < count - 1; i++)
            {
                // ����� ���� �� �ؿ� �ִ� ����� �� �پ� ��ܿͼ� ������ ����ε� �� ��
                books[i] = books[i + 1];
            }
            count--; // �׸�� ����

            // borrowList.txt�� �����ϴ� ����
            if (manageBookFile(books, nullbook, 2, count))
            {
                // å ��ȣ �ٽ� ��� �Ǵµ�
                for (int i = 0; i < count; i++)
                {
                    snprintf(books[i].id, sizeof(books[i].id), "%d", i + 1);
                }

                // ���� ������
                manageBookFile(books, nullbook, 2, count);

                setColor(10); gotoxy(34, 11); printf("������ �����Ǿ����ϴ�.");
                setColor(7);
            }
            gotoxy(34, 12); printf("�ƹ� Ű�� ������ ���ư��ϴ�...");
            _getch();
            return;
        }
        else if (input2[0] == 'n')
        {
            gotoxy(34, 11); printf("��ҵǾ����ϴ�.");
            _getch();
            continue;
        }
        else
        {
            gotoxy(34, 11); setColor(12); printf("�߸��� �Է��Դϴ�.");
            setColor(7);
        }
    }
}

/*
    ���� ��ȸ ��� (������) (��ü > ���� > �ݳ��Ϸ� ���� ����)
*/
void viewBorrowRecords()
{
    Borrow borrowList[1000] = { 0 };
    Book books[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    // state ���� �������� ����
    for (int i = 0; i < borrowCount - 1; i++)
    {
        for (int j = i + 1; j < borrowCount; j++)
        {
            if (borrowList[i].state < borrowList[j].state)
            {
                Borrow temp = borrowList[i];
                borrowList[i] = borrowList[j];
                borrowList[j] = temp;
            }
        }
    }

    int startIndex = 0;
    char titleShort[31];

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(20, 1, 80, 3, "��ü ���� ���� ��ȸ");
        setColor(7);
        drawBox(20, 4, 80, 25, " ID | ����                           | ��ȭ��ȣ      | �ݳ� ������ | ����     ");
        gotoxy(20, 6); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������");

        int check = 0;

        for (int i = 0; i < 17; i++)
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= borrowCount)
                break;

            check = 1;

            // ���� ã��
            strcpy(titleShort, "�������");
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(borrowList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(titleShort, books[j].bookTitle);
                    break;
                }
            }

            // ���º� ����
            if (borrowList[recordIndex].state == 2)
            {
                setColor(12); // ��ü
            }
            else if (borrowList[recordIndex].state == 1)
            {
                setColor(10); // ���� ��
            }
            else if (borrowList[recordIndex].state == 0)
            {
                setColor(8);  // �ݳ� �Ϸ�
            }
            else
            {
                setColor(7);
            }

            gotoxy(22, 8 + i);
            printf("%-2s | %-30s | %-13s | %d-%02d-%02d  | %s",
                borrowList[recordIndex].id, titleShort, borrowList[recordIndex].borrowerPhone,
                borrowList[recordIndex].returnYear, borrowList[recordIndex].returnMonth, borrowList[recordIndex].returnDay,
                borrowList[recordIndex].state == 0 ? "�ݳ� �Ϸ�" : (borrowList[recordIndex].state == 1 ? "���� ��" : "��ü ��"));
        }

        setColor(7);
        if (check == 0)
        {
            gotoxy(22, 8);
            printf("���� ������ �����ϴ�.");
        }

        gotoxy(20, 26); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������������");
        gotoxy(22, 27); printf("[��] ���� ������  [��] ���� ������  [0] �ڷ� ����");

        char key = _getch();
        if (key == 0 || key == -32)  // ����Ű
        {
            key = _getch();
            if (key == LEFT && startIndex >= 17)
            {
                startIndex -= 17;
            }
            else if (key == RIGHT && startIndex + 17 < borrowCount)
            {
                startIndex += 17;
            }
        }
        else if (key == '0')
        {
            return;
        }
    }
}

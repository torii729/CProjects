/*
    ********************
    도서관 대출 프로그램
    ********************

    여름방학 프로젝트
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
void signUp(); // 회원가입

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
            printf("잘못된 입력입니다.\n");
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
        printf("회원 파일을 불러올 수 없습니다.\n");
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

    xy(3, 0); printf("┌───────────────────────────────────────────┐");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("│");
        xy(47, i); printf("│");
    }
    xy(3, 15); printf("└───────────────────────────────────────────┘");

    xy(10, 3); printf("┌────────────────────────────┐       │");
    xy(10, 4); printf("│        도서관 시스템       │       │");
    xy(10, 5); printf("└────────────────────────────┘       │");
    xy(10, 6); printf("  1. 로그인                          │");
    xy(10, 7); printf("  2. 회원가입                        │");
    xy(10, 8); printf("  3. 종료                            │");
    xy(10, 10); printf("  메뉴 입력 : ");

    setColor(7);
}

int login()
{
    char phone[20], password[20];

    system("cls");
    setColor(11);

    // ui 그리기
    xy(3, 0); printf("┌───────────────────────────────────────────┐");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("│");
        xy(47, i); printf("│");
    }
    xy(3, 15); printf("└───────────────────────────────────────────┘");
    xy(10, 3); printf("┌────────────────────────────┐       │");
    xy(10, 4); printf("│        도서관 로그인       │       │");
    xy(10, 5); printf("└────────────────────────────┘       │");

    setColor(7);

    xy(10, 6); printf("전화번호 입력");
    xy(10, 7); printf("[ex) 010-xxxx-xxxx] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    xy(10, 8); printf("비밀번호 [숫자 4개 + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0 && strcmp(members[i].password, password) == 0)
        {
            system("cls");
            setColor(10);

            // ui 그리기
            xy(3, 0); printf("┌───────────────────────────────────────────┐");
            for (int j = 1; j <= 14; j++)
            {
                xy(3, j); printf("│");
                xy(47, j); printf("│");
            }
            xy(3, 15); printf("└───────────────────────────────────────────┘");
            xy(10, 3); printf("┌────────────────────────────┐       │");
            xy(10, 4); printf("│        도서관 시스템       │       │");
            xy(10, 5); printf("└────────────────────────────┘       │");

            xy(10, 6); printf("로그인 성공! 환영합니다.\n");

            setColor(7);
            system("pause");
            return 1;
        }
    }

    setColor(12);
    xy(10, 9); printf("로그인 실패: 전화번호 또는 비밀번호가 틀렸습니다.\n");
    setColor(7);

    system("pause");
    return 0;
}

void signUp() {
    char phone[20], password[20];

    system("cls");
    setColor(11);

    // ui 그리기
    xy(3, 0); printf("┌───────────────────────────────────────────┐");
    for (int i = 1; i <= 14; i++)
    {
        xy(3, i); printf("│");
        xy(47, i); printf("│");
    }
    xy(3, 15); printf("└───────────────────────────────────────────┘");
    xy(10, 3); printf("┌────────────────────────────┐       │");
    xy(10, 4); printf("│        회원가입 화면       │       │");
    xy(10, 5); printf("└────────────────────────────┘       │");

    xy(10, 6); printf("전화번호 입력");
    xy(10, 7); printf("[ex: 010-1234-5678] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0)
        {
            setColor(12);
            xy(10, 8); printf("이미 등록된 전화번호입니다.\n");
            setColor(7);
            system("pause");
            return;
        }
    }

    xy(10, 9); printf("비밀번호 입력");
    xy(10, 10); printf("[숫자 4자리 + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    strcpy(members[memberCount].phone, phone);
    strcpy(members[memberCount].password, password);
    memberCount++;

    FILE* file = fopen("member.txt", "a");

    if (file == NULL)
    {
        setColor(12);
        xy(10, 12); printf("회원 파일 저장 실패\n");
        setColor(7);

        system("pause");
        return;
    }

    fprintf(file, "%s %s\n", phone, password);
    fclose(file);

    setColor(10);
    xy(10, 12); printf("회원가입 완료\n");
    setColor(7);

    system("pause");
}

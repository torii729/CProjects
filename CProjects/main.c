// 도서관 대출 프로그램

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // gotoxy, setColor 사용

#define MAX_MEMBERS 100

typedef struct {
    char phone[20];
    char password[20];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

// 콘솔 커서 이동
void gotoxy(int x, int y) {
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 텍스트 색상 설정
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 회원 정보 파일에서 불러오기
void loadMembers() {
    FILE* file = fopen("member.txt", "r");
    if (file == NULL) {
        printf("회원 파일을 불러올 수 없습니다.\n");
        return;
    }

    while (fscanf(file, "%s %s", members[memberCount].phone, members[memberCount].password) == 2) {
        memberCount++;
    }

    fclose(file);
}

// 메인 메뉴 UI
void drawMainMenu() {
    system("cls");
    setColor(10); // 초록색

    gotoxy(3, 0); printf("┌────────────────────────────────────────────┐");
    gotoxy(3, 1); printf("│");
    gotoxy(3, 2); printf("│");
    gotoxy(3, 3); printf("│");
    gotoxy(3, 4); printf("│");
    gotoxy(3, 5); printf("│");
    gotoxy(3, 6); printf("│");
    gotoxy(3, 7); printf("│");
    gotoxy(3, 8); printf("│");
    gotoxy(3, 9); printf("│");
    gotoxy(3, 10); printf("│");
    gotoxy(3, 11); printf("│");
    gotoxy(3, 12); printf("│");
    gotoxy(3, 13); printf("│");
    gotoxy(3, 14); printf("│");
    gotoxy(3, 15); printf("└────────────────────────────────────────────┘");

    gotoxy(48, 1); printf("│");
    gotoxy(48, 2); printf("│");
    gotoxy(48, 8); printf("│");
    gotoxy(48, 9); printf("│");
    gotoxy(48, 10); printf("│");
    gotoxy(48, 11); printf("│");
    gotoxy(48, 12); printf("│");
    gotoxy(48, 13); printf("│");
    gotoxy(48, 14); printf("│");

    gotoxy(10, 3); printf("┌────────────────────────────┐        │");
    gotoxy(10, 4); printf("│        도서관 시스템       │        │");
    gotoxy(10, 5); printf("└────────────────────────────┘        │");
    gotoxy(10, 6); printf("  1. 로그인                           │");
    gotoxy(10, 7); printf("  2. 종료                             │");
    gotoxy(10, 9); printf("  메뉴 입력 : ");

    setColor(7); // 기본 색상
}

// 로그인 기능
int login() {
    char phone[20], password[20];

    system("cls");
    setColor(11); // 밝은 파랑
    gotoxy(3, 0); printf("┌────────────────────────────────────────────┐");
    gotoxy(3, 1); printf("│");
    gotoxy(3, 2); printf("│");
    gotoxy(3, 3); printf("│");
    gotoxy(3, 4); printf("│");
    gotoxy(3, 5); printf("│");
    gotoxy(3, 6); printf("│");
    gotoxy(3, 7); printf("│");
    gotoxy(3, 8); printf("│");
    gotoxy(3, 9); printf("│");
    gotoxy(3, 10); printf("│");
    gotoxy(3, 11); printf("│");
    gotoxy(3, 12); printf("│");
    gotoxy(3, 13); printf("│");
    gotoxy(3, 14); printf("│");
    gotoxy(3, 15); printf("└────────────────────────────────────────────┘");

    gotoxy(48, 1); printf("│");
    gotoxy(48, 2); printf("│");
    gotoxy(48, 8); printf("│");
    gotoxy(48, 9); printf("│");
    gotoxy(48, 10); printf("│");
    gotoxy(48, 11); printf("│");
    gotoxy(48, 12); printf("│");
    gotoxy(48, 13); printf("│");
    gotoxy(48, 14); printf("│");

    gotoxy(10, 3); printf("┌────────────────────────────┐        │");
    gotoxy(10, 4); printf("│        도서관 로그인       │        │");
    gotoxy(10, 5); printf("└────────────────────────────┘        │");

    gotoxy(48, 6); printf("│");
    gotoxy(48, 7); printf("│");

    setColor(7);

    gotoxy(10, 6); printf("전화번호 입력");
    gotoxy(10, 7); printf("[ex) 010-xxxx-xxxx] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(10, 8); printf("비밀번호 [숫자 4개 + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0 && strcmp(members[i].password, password) == 0) {
            system("cls");
            setColor(10);
            gotoxy(3, 0); printf("┌────────────────────────────────────────────┐");
            gotoxy(3, 1); printf("│");
            gotoxy(3, 2); printf("│");
            gotoxy(3, 3); printf("│");
            gotoxy(3, 4); printf("│");
            gotoxy(3, 5); printf("│");
            gotoxy(3, 6); printf("│");
            gotoxy(3, 7); printf("│");
            gotoxy(3, 8); printf("│");
            gotoxy(3, 9); printf("│");
            gotoxy(3, 10); printf("│");
            gotoxy(3, 11); printf("│");
            gotoxy(3, 12); printf("│");
            gotoxy(3, 13); printf("│");
            gotoxy(3, 14); printf("│");
            gotoxy(3, 15); printf("└────────────────────────────────────────────┘");

            gotoxy(48, 1); printf("│");
            gotoxy(48, 2); printf("│");
            gotoxy(48, 8); printf("│");
            gotoxy(48, 9); printf("│");
            gotoxy(48, 10); printf("│");
            gotoxy(48, 11); printf("│");
            gotoxy(48, 12); printf("│");
            gotoxy(48, 13); printf("│");
            gotoxy(48, 14); printf("│");

            gotoxy(10, 3); printf("┌────────────────────────────┐        │");
            gotoxy(10, 4); printf("│        도서관 시스템       │        │");
            gotoxy(10, 5); printf("└────────────────────────────┘        │");
            gotoxy(10, 6); printf("로그인 성공! 환영합니다.\n");
            setColor(7);
            system("pause");
            return 1;
        }
    }

    setColor(12);
    gotoxy(10, 9); printf("로그인 실패: 전화번호 또는 비밀번호가 틀렸습니다.\n");
    setColor(7);
    system("pause");
    return 0;
}

int main() 
{
    char menuInput[10];
    int choice = 0;

    loadMembers();  // 파일에서 회원 정보 불러오기

    while (1) {
        drawMainMenu();
        fgets(menuInput, sizeof(menuInput), stdin);
        choice = atoi(menuInput);  // 문자열을 정수로 변환

        if (choice == 1) {
            if (login()) {
                break; // 로그인 성공
            }
        }
        else if (choice == 2) {
            break;
        }
        else {
            printf("잘못된 입력입니다.\n");
            system("pause");
        }
    }

    return 0;
}
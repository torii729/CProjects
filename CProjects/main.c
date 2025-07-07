/*
    ********************
    도서관 대출 프로그램
    ********************

    여름방학 프로젝트
    텍스트 입력 방식
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_MEMBERS 100

/*
    구조체 정의 영역
*/

// 사용자 정보 구조체
typedef struct
{
    char name[20]; // 사용자 이름
    char phone[20]; // 전화번호
    char password[20]; // 비밀번호
} Member;

// 도서 정보 구조체
typedef struct
{
    char id[30]; // 도서 ID
    char bookTitle[50]; // 도서 제목
    char bookAuthor[20]; // 도서 저자
    char bookPublish[20]; // 출판사
} Book;

// 대출 정보 구조체
typedef struct
{
    char id[30]; // 도서 ID
    char borrowerPhone[20]; // 대출자 전화번호
    int borrowYear; // 대출 연도
    int borrowMonth; // 대출 월
    int borrowDay; // 대출 일
    int returnYear; // 반납 연도
    int returnMonth; // 반납 월
    int returnDay; // 반납 일
    int state; // 대출 상태(0: 가능, 1: 대출중, 2: 연체)
} BorrowList;

/*
    전역 변수 선언
*/
Member members[MAX_MEMBERS];
int memberCount = 0; // 현재 등록된 회원 수
char currentUser[20]; // 현재 로그인한 사용자 이름 저장용

/*
    함수 선언부
*/
void gotoxy(int x, int y); // 콘솔 커서 이동 함수
void setColor(int color); // 콘솔 글자 색상 변경 함수
void loadMembers(); // 회원 정보 파일에서 불러오기
void drawMainMenu(); // 초기 메인 메뉴 UI 출력 함수
int login(); // 로그인 기능 함수
void signUp(); // 회원가입 기능 함수
void drawBox(int x, int y, int w, int h); // 사각형 박스 그리기 함수
void drawTitleBox(int x, int y, const char* text); // 제목 상자 출력 함수
void drawUserMenu(); // 로그인 후 사용자 메인 메뉴 함수

/*
    메인 함수
*/
int main()
{
    int choice;
    char input[10];

    loadMembers(); // 프로그램 실행 시 회원 정보 먼저 불러오기

    while (1)
    {
        drawMainMenu(); // 메인 화면 출력

        gotoxy(13, 22);
        printf("번호 입력 : ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1)
        {
            if (login())
            {
                drawUserMenu(); // 로그인 성공 시 사용자 메뉴 이동
            }
        }
        else if (choice == 2)
        {
            signUp(); // 회원가입 이동
        }
        else if (choice == 3)
        {
            break; // 종료
        }
        else
        {
            gotoxy(13, 22); setColor(12);
            printf("잘못된 입력입니다. 다시 선택해주세요.");
            setColor(7);
            system("pause");
        }
    }
    return 0;
}

/*
    콘솔 커서 위치 이동 함수
*/
void gotoxy(int x, int y)
{
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*
    콘솔 글자 색상 변경 함수
*/
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*
    회원 정보를 파일에서 불러오는 함수
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
    제목 박스 그리기
*/
void drawTitleBox(int x, int y, const char* text)
{
    gotoxy(x, y);     printf("┌─────────────────────────┐");
    gotoxy(x, y + 1); printf("│   %s  │", text); // 텍스트 가운데 배치
    gotoxy(x, y + 2); printf("└─────────────────────────┘");
}

/*
    사각형 박스 출력 함수
*/
void drawBox(int x, int y, int w, int h)
{
    gotoxy(x, y); printf("┌");
    for (int i = 0; i < w - 2; i++)
    {
        printf("─");
    }
    printf("┐");

    for (int i = 1; i < h - 1; i++)
    {
        gotoxy(x, y + i); printf("│");
        gotoxy(x + w - 1, y + i); printf("│");
    }

    gotoxy(x, y + h - 1); printf("└");
    for (int i = 0; i < w - 2; i++)
    {
        printf("─");
    }
    printf("┘");
}

/*
    메인 화면 UI 출력
*/
void drawMainMenu()
{
    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 22); // 전체 메인 박스
    drawTitleBox(17, 4, "도서관 대출 프로그램"); // 제목 상자

    drawBox(22, 8, 16, 3); // 로그인 버튼 박스
    gotoxy(25, 9); printf("1. 로그인");

    drawBox(22, 12, 16, 3); // 회원가입 버튼 박스
    gotoxy(25, 13); printf("2. 회원가입");

    setColor(12);
    drawBox(22, 16, 16, 3); // 종료 버튼 박스
    gotoxy(25, 17); printf("3. 종료");
    setColor(7);

    // 번호 입력 칸 상단 구분 선
    gotoxy(10, 21); printf("├──────────────────────────────────────┤");

    // 하단 테두리
    gotoxy(10, 23); printf("└──────────────────────────────────────┘");
}

/*
    로그인 기능
*/
int login()
{
    char name[20], phone[20], password[20];
    system("cls");

    drawBox(10, 2, 40, 22);
    drawTitleBox(17, 3, "   사용자 로그인    ");
    drawBox(12, 6, 36, 17);

    gotoxy(14, 7); printf("이름        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("전화번호    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("비밀번호    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].name, name) == 0 &&
            strcmp(members[i].phone, phone) == 0 &&
            strcmp(members[i].password, password) == 0)
        {
            strcpy(currentUser, name); // 로그인 성공 시 사용자 이름 저장("~~님 환영합니다!" 문구의 "~~" 때문에)
            return 1;
        }
    }
    gotoxy(14, 19); setColor(12);
    printf("로그인 실패: 정보가 일치하지 않습니다.\n");
    setColor(7);
    system("pause");
    return 0;
}

/*
    회원가입 기능
*/
void signUp()
{
    return 0;
}

/*
    로그인 후 사용자 메뉴 화면
*/
void drawUserMenu()
{
    char welcome[60];
    int choice;
    char input[10];

    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 22); // 전체 메인 박스
    drawTitleBox(17, 4, "도서관 대출 프로그램"); // 제목 상자

    sprintf(welcome, "    %s 님, 환영합니다!", currentUser);
    setColor(10);
    gotoxy(17, 7); printf("%s", welcome);
    setColor(7);

    setColor(3);
    drawBox(14, 8, 16, 5); // 도서 대출
    gotoxy(16, 10); printf("1. 도서 대출");

    drawBox(31, 8, 16, 5); // 도서 반납
    gotoxy(33, 10); printf("2. 도서 반납");
    setColor(7);

    setColor(8);
    drawBox(14, 13, 11, 5); // 도서 목록
    gotoxy(16, 15); printf("3. 목록");

    drawBox(25, 13, 11, 5); // 도서 검색
    gotoxy(27, 15); printf("4. 검색");

    drawBox(36, 13, 11, 5); // 대출 내역
    gotoxy(38, 15); printf("5. 내역");
    setColor(7);

    setColor(12);
    drawBox(25, 18, 11, 3); // 종료
    gotoxy(27, 19); printf("6. 종료");
    setColor(7);

    // 번호 입력 칸 상단 구분 선
    gotoxy(10, 21); printf("├──────────────────────────────────────┤");

    // 번호 입력 문구 출력
    gotoxy(13, 22); printf("번호 입력 : ");

    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    // 하단 테두리
    gotoxy(10, 23); printf("└──────────────────────────────────────┘");



    // 이후 기능 추가 예정임
}

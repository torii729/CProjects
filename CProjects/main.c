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
char currentUser[20]; // 현재 로그인한 사용자 이름 저장용

/*
    함수 선언부
*/
void gotoxy(int x, int y); // 콘솔 커서 이동 함수 (xy 좌표)
void setColor(int color); // 콘솔 글자 색상 변경 함수
void drawMainMenu(); // 초기 메인 메뉴 UI 출력 함수
void drawBox(int x, int y, int w, int h, const char text[]); // 사각형 박스 그리기 함수
void drawUserMenu(); // 로그인 후 사용자 메인 메뉴 함수

int mainLogin(); // 메인 화면 (맨처음 화면)
int login(); // 로그인 기능 함수
void signUp(); // 회원가입 기능 함수

void handleBorrow(); // 도서 대출
void handleReturn(); // 도서 반납
void showBookList(); // 목록 보기
void searchBook(); // 도서 검색
void viewBorrowHistory(); // 대출 내역


/*
    메인 함수
*/
int main()
{
    mainLogin();
    return 0;
}

/*
    메인 화면 (맨처음 화면)
*/
int mainLogin()
{
    int choice;
    char input[10];

    while (1)  // 무한 반복 (예시 : 회원가입 완료하고 여기로 다시 돌아와야 함, 반복하지 않으면 회원가입 완료 시 프로그램이 종료됨)
    {
        drawMainMenu(); // 메인 화면 출력

        gotoxy(13, 22);
        printf("번호 입력 : ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice)
        {
        case 1 :
            if (login()) // 로그인 실행
                drawUserMenu(); // 로그인 성공 시 사용자 메뉴 이동
            break;

        case 2 :
            signUp(); // 회원가입 실행
            break;

        case 3 :
            return 0; // 종료
        
        default :
            gotoxy(13, 22);
            setColor(12);
            printf("잘못된 입력입니다. 다시 입력해주세요.");
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
    사각형 박스 출력 함수
*/
void drawBox(int x, int y, int width, int height, const char text[])
{
    // 상단
    gotoxy(x, y); printf("┌");
    for (int i = 0; i < width - 2; i++)
    {
        printf("─");
    }
    printf("┐");

    // 중간
    for (int i = 1; i < height - 1; i++) 
    {
        gotoxy(x, y + i); printf("│");
        for (int j = 0; j < width - 2; j++)
        {
            printf(" ");
        }
        printf("│");
    }

    // 하단
    gotoxy(x, y + height - 1); printf("└");
    for (int i = 0; i < width - 2; i++)
    {
        printf("─");
    }
    printf("┘");

    // 텍스트 출력 (중앙 정렬)
    if (text != NULL)
    {
        int textX = x + (width - (int)strlen(text)) / 2;
        int textY = y + 1;
        gotoxy(textX, textY);
        printf("%s", text);
    }
}

/*
    메인 화면 UI 출력
*/
void drawMainMenu()
{
    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 3, "도서관 대출 프로그램"); // 전체 메인 박스
    drawBox(10, 5, 40, 19, "");

    drawBox(22, 8, 16, 3, " 1. 로그인"); // 로그인 버튼 박스
   // gotoxy(25, 9); printf("1. 로그인");

    drawBox(22, 12, 16, 3, " 2. 회원가입"); // 회원가입 버튼 박스
    // gotoxy(25, 13); printf("2. 회원가입");

    setColor(12);
    drawBox(22, 16, 16, 3, " 3. 종료"); // 종료 버튼 박스
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
    char fileName[20], filePhone[20], filePassword[20];

    FILE* file = fopen("member.txt", "r");
    if (file == NULL)
    {
        gotoxy(14, 19);
        setColor(12);
        printf("회원 데이터 파일이 없습니다.");
        setColor(7);
        system("pause");
        return 0;
    }

    system("cls");

    drawBox(10, 2, 40, 3, "사용자 로그인");
    drawBox(10, 5, 40, 19, "");
    drawBox(12, 6, 36, 17, "");

    gotoxy(14, 7); printf("이름        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("전화번호    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("비밀번호    : ");
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
        printf("로그인 실패: 정보가 일치하지 않습니다.\n");
        setColor(7);
        system("pause");
        return 0;
    }
}


/*
    회원가입 기능
*/
void signUp()
{
    char name[20], phone[20], password[20];

    system("cls");

    drawBox(10, 2, 40, 3, "회원가입");
    drawBox(10, 5, 40, 19, "");
    drawBox(12, 6, 36, 17, "");

    gotoxy(14, 7);  printf("이름        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(14, 11); printf("전화번호    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(14, 15); printf("비밀번호    : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    FILE* file = fopen("member.txt", "a");

    if (file == NULL)
    {
        gotoxy(14, 19);
        setColor(12);
        printf("회원 정보 저장 실패");
        setColor(7);
        system("pause");
        return;
    }

    fprintf(file, "\n%s %s %s", name, phone, password);
    fclose(file);

    gotoxy(14, 19);
    setColor(10);
    printf("회원가입 완료");
    setColor(7);
    system("pause");
}

/*
    로그인 후 사용자 메뉴 화면
*/
void drawUserMenu()
{
    char welcome[60];
    char input[10];
    int choice;

    system("cls");
    setColor(7);

    drawBox(10, 2, 40, 3, "도서관 대출 프로그램"); // 전체 메인 박스
    drawBox(10, 5, 40, 19, "");

    sprintf(welcome, "    %s 님, 환영합니다!", currentUser);
    setColor(10);
    gotoxy(17, 6); printf("%s", welcome);
    setColor(7);

    setColor(3);
    drawBox(14, 8, 16, 5, ""); // 도서 대출
    gotoxy(16, 10); printf("1. 도서 대출");
 
    drawBox(31, 8, 16, 5, ""); // 도서 반납
    gotoxy(33, 10); printf("2. 도서 반납");
    setColor(7);

    setColor(8);
    drawBox(14, 13, 11, 5, ""); // 도서 목록
    gotoxy(16, 15); printf("3. 목록");

    drawBox(25, 13, 11, 5, ""); // 도서 검색
    gotoxy(27, 15); printf("4. 검색");

    drawBox(36, 13, 11, 5, ""); // 대출 내역
    gotoxy(38, 15); printf("5. 내역");
    setColor(7);

    setColor(12);
    drawBox(23, 18, 15, 3, ""); // 뒤로가기
    gotoxy(25, 19); printf("6. 뒤로 가기");
    setColor(7);

    // 번호 입력 칸 상단 구분 선
    gotoxy(10, 21); printf("├──────────────────────────────────────┤");

    // 번호 입력 문구
    gotoxy(13, 22); printf("번호 입력 : ");

    fgets(input, sizeof(input), stdin);
    choice = atoi(input);

    // 하단 테두리
    gotoxy(10, 23); printf("└──────────────────────────────────────┘");

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
        printf("잘못된 입력입니다 . 다시 입력해주세요.");
        setColor(7);
        system("pause");
    }
}

// 미구현 함수들
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
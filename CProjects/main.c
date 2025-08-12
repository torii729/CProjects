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
#include <conio.h>
#include <time.h>
#include "Struct.h" // 구조체(Member, Book, BorrowList) 헤더 파일

#define LEFT 75
#define RIGHT 77

/*
    전역 변수 선언...
*/
Member members[1000];
Book books[1000];
char currentUser[20]; // 현재 로그인한 사용자 이름 저장용
char currentPhone[20]; // 현재 로그인한 사용자 전화번호 저장용
int year, month, day;

/*
    함수 선언부
*/
void gotoxy(int x, int y); // 콘솔 커서 이동 함수 (xy 좌표)
void setColor(int color); // 콘솔 글자 색상 변경 함수
int manageMemberFile(Member members[], Member newMember, int mode); // member.txt 파일 읽거나 추가 함수
int manageBookFile(Book books[], Book newBook, int mode, int bookCount); // book.txt 파일 읽거나 추가 함수
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount); // borrowList.txt 파일 읽거나 추가 함수
void getDate(int offset); // 날짜 계산 함수
void drawBox(int x, int y, int w, int h, char text[]); // 사각형 박스 그리기 함수
void drawMainMenu(); // 초기 메인 메뉴 UI 출력 함수

int mainLogin(); // 메인 화면 (맨처음 화면)
int selectLogin(); // 로그인 선택 (사용자? 관리자?)
int userMenu(); // 로그인 후 "사용자" 메인 메뉴 함수
int adminMenu(); // 로그인 후 "관리자" 메인 메뉴 함수

int login(); // 로그인 기능 함수
void signUp(); // 회원가입 기능 함수

void showBookList(); // 목록 보기
void searchBook(); // 도서 검색
void handleBorrow(); // 도서 대출
void handleReturn(); // 도서 반납
void viewBorrowHistory(); // 대출 내역

void addBook(); // 도서 등록
void removeBook(); // 도서 삭제
void viewBorrowRecords(); // 대출/연체 내역 조회

/*
    메인 함수
*/
int main()
{
    Borrow list[1000] = { 0 };
    Borrow null = { 0 };
    int borrowCount = manageBorrowFile(list, null, 0, 0); // 전체 대출 목록 불러오기

    getDate(0); // 오늘 날짜 (year, month, day)

    for (int i = 0; i < borrowCount; i++)
    {
        if (list[i].state == 1) // 대출 중이면
        {
            // 반납 예정일이 오늘 날짜보다 앞서는 경우에 연체로(state를 2로) 변경하ㅡ는 조건문
            if (list[i].returnYear < year
                || (list[i].returnYear == year && list[i].returnMonth < month)
                || (list[i].returnYear == year && list[i].returnMonth == month && list[i].returnDay < day))
            {
                list[i].state = 2; // 연체로 변경
            }
        }
    }
    manageBorrowFile(list, null, 2, borrowCount); // 파일 덮어쓰기 저장

    mainLogin();
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
    파일 관리 함수 (member.txt)
*/
int manageMemberFile(Member members[], Member newMember, int mode)
{
    FILE* file;
    int count = 0;
    if (mode == 0) // 파일 read
    {
        file = fopen("member.txt", "r");
        if (file == NULL)
        {
            setColor(12); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다.");
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

    else if (mode == 1) // 파일 append
    {
        file = fopen("member.txt", "a");
        if (file == NULL)
        {
            setColor(12); gotoxy(42, 19); printf("회원 데이터 파일이 없습니다.");
         
            
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
    파일 관리 함수 (book.txt)
*/
int manageBookFile(Book books[], Book newBook, int mode, int bookCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // 파일 read
    {
        file = fopen("book.txt", "r");
        if (file == NULL)
        {
            setColor(12); gotoxy(42, 19); printf("데이터 파일이 없습니다.");
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
    else if (mode == 1) // 파일 append
    {
        // 도서 추가
        file = fopen("book.txt", "a");
        if (file == NULL)
        {
            setColor(12); gotoxy(42, 19); printf("데이터 파일이 없습니다.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }

        fprintf(file, "\n%s %s %s %s", newBook.id, newBook.bookTitle, newBook.bookAuthor, newBook.bookPublish);
        fclose(file);

        return 1;
    }

    else if (mode == 2) // 파일 덮어쓰기
    {
        FILE* tempBookFile = fopen("tempBook.txt", "w");
        if (tempBookFile == NULL)
        {
            setColor(12);   gotoxy(42, 19); printf("임시 파일 생성 실패함");
            setColor(7); gotoxy(42, 20); system("pause");

            return 0;
        }

        // borrowCount를 사용해 유효한 항목만 저장할 수 있다고 함

        for (int i = 0; i < bookCount; i++)
        {
            if (i == 0) // 빈 파일에 최초 저장 시 
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
            setColor(12); gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }
    return 0;
}

/*
    파일 관리 함수 (borrowList.txt)
*/
int manageBorrowFile(Borrow borrowList[], Borrow newBorrow, int mode, int borrowCount)
{
    int count = 0;
    FILE* file;

    if (mode == 0) // 파일 읽기
    {
        file = fopen("borrowList.txt", "r");

        if (file == NULL)
        {
            setColor(12);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다."); 
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
    else if (mode == 1) // 파일 추가
    {
        file = fopen("borrowList.txt", "a");
        if (file == NULL)
        {
          
            setColor(12);  gotoxy(42, 19); printf("대출 데이터 파일이 없습니다.");
           
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
    else if (mode == 2) // 파일 덮어쓰기
    {
        FILE* tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL)
        {
            setColor(12);   gotoxy(42, 19); printf("임시 파일 생성 실패함");
            setColor(7); gotoxy(42, 20); system("pause");
            
            return 0;
        }

        // borrowCount를 사용해 유효한 항목만 저장할 수 있다고 함

        for (int i = 0; i < borrowCount; i++)
        {
            if (i == 0) // 빈 파일에 최초 저장 시 
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
            setColor(12); gotoxy(42, 19); printf("파일 갱신 실패.");
            setColor(7); gotoxy(42, 20); system("pause");
            return 0;
        }
        return 1;
    }
    return 0;
}

/*
    사각형 박스 출력 함수
*/
void drawBox(int x, int y, int width, int height, char text[])
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

    drawBox(40, 2, 40, 3, "도서관 대출 프로그램"); // 전체 메인 박스
    drawBox(40, 5, 40, 19, "");

    drawBox(52, 8, 16, 3, " 1. 로그인"); // 로그인 버튼 박스

    drawBox(52, 12, 16, 3, " 2. 회원가입"); // 회원가입 버튼 박스

    setColor(12);
    drawBox(52, 16, 16, 3, " 3. 종료"); // 종료 버튼 박스
    setColor(7);

    // 번호 입력 칸 상단 구분 선
    gotoxy(40, 21); printf("├──────────────────────────────────────┤");

    // 하단 테두리
    gotoxy(40, 23); printf("└──────────────────────────────────────┘");
}

/*
    메인 화면 (맨처음 화면)
*/
int mainLogin()
{
    char input[10];

    while (1)  // 무한 반복 (예시 : 회원가입 완료하고 여기로 다시 돌아와야 함, 반복하지 않으면 회원가입 완료 시 프로그램이 종료됨)
    {
        drawMainMenu(); // 메인 화면 출력

        gotoxy(42, 22);
        printf("번호 입력 : ");
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
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(7);
            gotoxy(42, 20); system("pause");
        }
    }
    return 0;
}

/*
    로그인 선택 화면
*/
int selectLogin()
{
    char input[10];

    drawMainMenu(); // 메인 화면 출력

    drawBox(40, 2, 40, 3, " 로그인 선택");
    drawBox(52, 8, 16, 3, " 1. 사용자"); // 사용자 로그인
    drawBox(52, 12, 16, 3, " 2. 관리자"); // 관리자 로그인

    setColor(12);
    drawBox(52, 16, 16, 3, " 3. 뒤로 가기"); // 메인 화면으로 돌아가기
    setColor(7);

    gotoxy(42, 22);
    printf("번호 입력 : ");
    fgets(input, sizeof(input), stdin);

    if (input[0] == '1')
    {
        if (login())  // 로그인
        {
            userMenu(); // 로그인 성공 시 사용자 메뉴로 이동
            return 1;
        }
    }
    else if (input[0] == '2')
    {
        if (login())  // 로그인
        {
            adminMenu(); // 로그인 성공 시 관리자 메뉴로 이동
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
        printf("잘못된 입력입니다. 다시 입력해주세요.");
        setColor(7);
        gotoxy(42, 20); system("pause");
    }
    return 0;
}

/*
    로그인 후 사용자 메뉴 화면
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
        drawBox(40, 2, 40, 3, "도서관 대출 프로그램"); // 전체 메인 박스
        drawBox(40, 5, 40, 19, "");

        sprintf(welcome, "   %s 님, 환영합니다!", currentUser); // sprintf -> welcome 배열에 " currentUser님 환영합니다!" 문자열 저장하는 것
        setColor(10);
        gotoxy(47, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(44, 8, 16, 5, ""); // 도서 대출
        gotoxy(46, 10); printf("1. 도서 대출");

        drawBox(61, 8, 16, 5, ""); // 도서 반납
        gotoxy(63, 10); printf("2. 도서 반납");
        setColor(7);

        setColor(3);
        drawBox(44, 13, 11, 5, ""); // 도서 목록
        gotoxy(46, 15); printf("3. 목록");

        drawBox(55, 13, 11, 5, ""); // 도서 검색
        gotoxy(57, 15); printf("4. 검색");

        drawBox(66, 13, 11, 5, ""); // 대출 내역
        gotoxy(68, 15); printf("5. 내역");
        setColor(7);

        setColor(12);
        drawBox(53, 18, 15, 3, ""); // 뒤로가기
        gotoxy(55, 19); printf("6. 로그아웃");
        setColor(7);

        gotoxy(40, 21); printf("├──────────────────────────────────────┤");
        gotoxy(43, 22); printf("번호 입력 : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(40, 23); printf("└──────────────────────────────────────┘");

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
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(7);
            gotoxy(43, 20); system("pause");
        }
    }
}

/*
    로그인 후 관리자 메뉴 화면
*/
int adminMenu()
{
    char welcome[60];
    char input[10];

    while (1)
    {
        system("cls");
        setColor(7);

        drawBox(40, 2, 40, 3, "도서관 대출 프로그램");
        drawBox(40, 5, 40, 19, "");

        sprintf(welcome, "    %s 님, 환영합니다.", currentUser);
        setColor(10);
        gotoxy(47, 6); printf("%s", welcome);
        setColor(7);

        setColor(6);
        drawBox(44, 8, 16, 5, ""); // 도서 등록
        gotoxy(46, 10); printf("1. 도서 등록");

        drawBox(61, 8, 16, 5, ""); // 도서 삭제
        gotoxy(63, 10); printf("2. 도서 삭제");
        setColor(7);

        setColor(3);
        drawBox(44, 13, 33, 5, ""); // 전체 대출 내역
        gotoxy(46, 15); printf("      3. 대출/연체 내역");
        setColor(7);

        setColor(12);
        drawBox(53, 18, 15, 3, ""); // 뒤로가기
        gotoxy(55, 19); printf("4. 로그아웃");
        setColor(7);

        gotoxy(40, 21); printf("├──────────────────────────────────────┤");
        gotoxy(43, 22); printf("번호 입력 : ");
        fgets(input, sizeof(input), stdin);
        gotoxy(40, 23); printf("└──────────────────────────────────────┘");

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
            printf("잘못된 입력입니다. 다시 입력해주세요.");
            setColor(7);
            gotoxy(43, 20); system("pause");
        }
    }
}

/*
    날짜 계산
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
    로그인 기능
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
    drawBox(40, 2, 40, 3, "로그인");
    drawBox(40, 5, 40, 19, "");
    drawBox(42, 6, 36, 17, "");

    gotoxy(44, 7); printf("이름        : ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    gotoxy(44, 11); printf("전화번호    : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(44, 15); printf("비밀번호    : ");

    int idx = 0;
    char k;

    while (1)
    {
        k = _getch();

        if (k == 13) // 엔터치면 입력 완료
        {
            password[idx] = '\0'; // 어디까지가 문자열인지 배열에 엔터를 직접 넣음으로써 판단할 수 ㅇㅆ게...
            break;
        }
        else if (k == 8) // 백스페이스 누르면 지워져야 하는데...
        {
            printf("\b \b"); // ??
        }
        else if (k >= 33 && k <= 126) // !부터 ~까지인데 뭔지모르겟으면 톡방 사진 참고
        {
            // 입력한 문자를 저장하나, 실제로 출력되는 건 *임
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
        printf("정보가 일치하지 않습니다.\n");
        setColor(7);
        gotoxy(44, 20); system("pause");
        return 0;
    }
}

/*
    회원가입 기능
*/
void signUp()
{
    Member newMember = { 0 };
    Member null = { 0 };
    int count = manageMemberFile(members, null, 0);

    system("cls");
    drawBox(40, 2, 40, 3, "회원가입");
    drawBox(40, 5, 40, 19, "");
    drawBox(42, 6, 36, 17, "");

    while (1)
    {
        gotoxy(44, 7); printf("이름        : ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = 0;

        // 이름이 공백인지 체크
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
            gotoxy(44, 19); printf("이름은 공백일 수 없습니다.");
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

        gotoxy(44, 11); printf("전화번호    : ");
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
            gotoxy(44, 19); printf("전화번호 형식이 올바르지 않습니다.");
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
                printf("이미 등록된 전화번호입니다.");
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
        gotoxy(44, 15); printf("비밀번호    : ");
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
            gotoxy(44, 19); printf("비밀번호에 공백을 포함할 수 없습니다.");
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
        gotoxy(44, 19); printf("회원가입 완료");
        setColor(7);
        gotoxy(44, 20); system("pause");
    }
}

/*
    도서 대출 기능
*/
void handleBorrow()
{
    Book nullbook = { 0 };
    Borrow nullborrow = { 0 };
    Borrow temp[1000] = { 0 };
    int count = manageBookFile(books, nullbook, 0, 0);
    int borrowCount = manageBorrowFile(temp, nullborrow, 0, 0);
    char borrowId[10];

    // 연체 중인지 체크
    for (int i = 0; i < borrowCount; i++)
    {
        if (strcmp(temp[i].borrowerPhone, currentPhone) == 0 && temp[i].state == 2) // state 2 = 연체
        {
            system("cls");
            setColor(3);
            drawBox(30, 5, 60, 3, "도서 대출");
            setColor(7);
            drawBox(30, 8, 60, 11, "");

            setColor(12);
            gotoxy(32, 12);
            printf("연체 도서가 있어 대출이 제한됩니다.");
            setColor(7);
            gotoxy(32, 14);
            printf("계속하려면 아무 키나 누르세요...");
            _getch();
            return;
        }
    }

    // 3권 이상 대출 제한
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
        drawBox(30, 5, 60, 3, "도서 대출");
        setColor(7);
        drawBox(30, 8, 60, 11, "");

        setColor(12);
        gotoxy(32, 12);
        printf("이미 3권 이상 대출 중입니다. 더 이상 대출할 수 없습니다.");
        setColor(7);
        gotoxy(32, 14);
        printf("계속하려면 아무 키나 누르세요...");
        _getch();
        return;
    }

    showBookList();

    system("cls");
    setColor(3);
    drawBox(30, 5, 60, 3, "도서 대출");
    setColor(7);
    drawBox(30, 8, 60, 11, "");

    gotoxy(32, 9);
    printf("대출할 도서의 번호(ID)를 입력하세요 (0 : 취소) : ");
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
                    printf("해당 도서는 현재 대출 중입니다.");
                    setColor(7);
                    gotoxy(32, 14);
                    printf("계속하려면 아무 키나 누르세요...");
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
                printf("대출이 완료되었습니다!");
                gotoxy(32, 13);
                printf("반납 기한 : %d년 %d월 %d일까지", year, month, day);
                setColor(7);
            }
            else
            {
                setColor(12);
                gotoxy(32, 12);
                printf("대출 정보 저장 실패.");
                setColor(7);
            }
            break;
        }
    }

    if (found == 0)
    {
        gotoxy(32, 12);
        printf("해당 ID의 도서를 찾을 수 없습니다.");
    }

    gotoxy(32, 15);
    printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

/*
    도서 반납 기능
*/
void handleReturn()
{
    Borrow borrowList[1000] = { 0 }; // 초기화를 안하면 반납이 안되는 오류 발생하므로 필수;
    Borrow nullBorrow = { 0 };
    Book nullBook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullBorrow, 0, 0); // 대출 목록 불러오기
    int bookCount = manageBookFile(books, nullBook, 0, 0); // 도서 목록 불러오기
    if (borrowCount == 0)
    {
        gotoxy(32, 7); printf("대출 데이터가 없습니다.");
        gotoxy(32, 9); printf("아무 키나 누르면 돌아갑니다...");
        _getch();
        return;
    }

    system("cls");
    setColor(3);
    drawBox(30, 2, 60, 3, "도서 반납");
    setColor(7);
    drawBox(30, 5, 60, 22, "");
    gotoxy(30, 24); printf("├──────────────────────────────────────────────────────────┤");

    // 로그인한 사용자가 빌린 책만 추출하기 위해서 선언한 부분 ,
    int userBorrowList[1000];
    int userCount = 0;

    for (int i = 0; i < borrowCount; i++)
    {
        // 로그인한 전화번호가 일치하는 경우
        if (strcmp(borrowList[i].borrowerPhone, currentPhone) == 0
                && borrowList[i].state == 1 || borrowList[i].state == 2)
        {
            userBorrowList[userCount] = i;
            userCount++;
        }
    }

    if (userCount == 0)
    {
        gotoxy(32, 7); printf("현재 대출 중인 도서가 없습니다.");
        gotoxy(32, 9); printf("아무 키나 누르면 돌아갑니다...");
        _getch();
        return;
    }

    gotoxy(31, 6); printf("번호│ 제목                           │ 반납 예정일");
    gotoxy(30, 7); printf("├──────────────────────────────────────────────────────────┤");

    // ui 위치때문에
    int b = 8;
    int c = 9;

    for (int i = 0; i < userCount; i++)
    {
        int idx = userBorrowList[i];
        char copyTitle[50] = { 0 };

        for (int j = 0; j < bookCount; j++)
        {
            // 대출 정보에 있는 책 번호랑 책 정보에 있는 책 번호랑 비교
            if (strcmp(borrowList[idx].id, books[j].id) == 0)
            {
                strcpy(copyTitle, books[j].bookTitle);
                break;
            }
        }

        setColor(10);
        drawBox(31, b, 58, 3, "");
        gotoxy(32, c); printf(" %d │ %-30s │ %d-%d-%d", i + 1, copyTitle,
            borrowList[idx].returnYear, borrowList[idx].returnMonth, borrowList[idx].returnDay);
        setColor(7);

        b += 3;
        c += 3;
    }

    char input[10];

    gotoxy(32, 25); printf("반납할 번호 입력 (0 : 취소) : ");
    fgets(input, sizeof(input), stdin);

    int select = atoi(input); // atoi를 쓰면 정수 변환이 된다함 신기해 무지막지

    if (select == 0)
    {
        return;
    }

    if (select > userCount || select < 1)
    {
        setColor(12); gotoxy(32, 22); printf("잘못된 번호 입력입니다.");
        setColor(7); gotoxy(32, 23); printf("아무 키나 누르면 돌아갑니다..");
        _getch();
        return;
    }

    int idx = userBorrowList[select - 1]; // select에서 -1을 안하면 인덱스 0번부터 안나옴 ㅠ ㅠㅠ

    borrowList[idx].state = 0; // 정상 반납 처리

    if (manageBorrowFile(borrowList, nullBorrow, 2, borrowCount))
    {
        setColor(10); gotoxy(32, 22); printf("도서가 성공적으로 반납되었습니다!");
    }

    gotoxy(32, 23); printf("아무 키나 누르면 돌아갑니다...");
    _getch();
}

/*
    도서 목록 조회 기능
*/
void showBookList()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0, 0); // 도서 마지막 번호 저장용
    int startIndex = 0;
    char input[10];
    char titleShort[30];

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "도서 목록");
        setColor(7);
        drawBox(30, 5, 60, 22, "");

        gotoxy(31, 6); printf("번호│제목                │저자            │출판사");
        gotoxy(30, 7); printf("├──────────────────────────────────────────────────────────┤");

        for (int i = 0; i < 15; i++)
        {
            // startIndex가 첫 목록을 가리킴, i를 더해서 순차적으로 출력함
            int bookIndex = startIndex + i;

            if (bookIndex >= count)
            {
                break; // 전체 도서 수를 넘으면(책이 더 없으면) 중단하는 기능
            }

            // 제목 자르기 (10글자 초과 시 7글자에다가 말줄임표)
            if (strlen(books[bookIndex].bookTitle) > 25)
            {
                snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bookIndex].bookTitle);
            }
            else
            {
                strcpy(titleShort, books[bookIndex].bookTitle);
            }

            // 순차적 출력
            setColor(3);
            gotoxy(32, 8 + i);
            printf(" %-2s│%-20s│%-16s│%-5s\n", books[bookIndex].id, titleShort,
                books[bookIndex].bookAuthor, books[bookIndex].bookPublish);
            setColor(7);
        }

        gotoxy(30, 24); printf("├──────────────────────────────────────────────────────────┤");
        gotoxy(30, 26); printf("└──────────────────────────────────────────────────────────┘");
        gotoxy(33, 25); printf("[0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == -32)  // -32 기본 값인듯
        {
            key = _getch();  // 실제 키 값 읽는거

            if (key == LEFT && startIndex >= 15)
            {
                startIndex = startIndex - 15; // 15 빼서 이전에 출력된 15개의 목록 나오게끔
            }

            else if (key == RIGHT && startIndex + 15 < count)
            {
                startIndex = startIndex + 15;
            }
        }
        else if (key == '0')  // 뒤로가기
        {
            return;
        }
    }
}

/*
    도서 검색 기능
*/
void searchBook()
{
    Book null = { 0 };
    int count = manageBookFile(books, null, 0, 0); // 도서 정보 불러오기
    char word[50];

    while (1)
    {
        // ui 시작
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "도서 검색");
        setColor(7);

        drawBox(30, 5, 60, 22, "");
        gotoxy(30, 7); printf("├──────────────────────────────────────────────────────────┤");

        gotoxy(31, 8); printf(" 번호│ 제목                 │ 저자             │ 출판사");
        gotoxy(30, 9); printf("├──────────────────────────────────────────────────────────┤");

        // 검색
        gotoxy(31, 6); printf("검색할 도서 제목 또는 저자 (뒤로 가기 : 0) : ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = 0; // 엔터 제거하는ㄱ  그거

        if (strcmp(word, "0") == 0)
        {
            break; // ㄴㄴ
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
                gotoxy(32, c); printf(" %-2s │ %-20s │ %-13s │ %-5s\n", books[i].id,
                    books[i].bookTitle, books[i].bookAuthor, books[i].bookPublish);
                setColor(7);

                b += 3;
                c += 3;
            }
        }

        if (check == 0)
        {
            setColor(12);
            gotoxy(32, 23); printf("해당 키워드와 일치하는 도서를 찾을 수 없습니다.\n");
            setColor(7);
        }
        gotoxy(32, 24); printf("아무 키나 누르면 다시 검색합니다.");
        _getch();
    }
}

/*
    대출 조회 기능 (사용자) (도서 ID 순서)
*/
void viewBorrowHistory()
{
    Borrow borrowList[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    // ID 기준 오름차순 정렬
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
        drawBox(20, 1, 80, 3, "대출 내역 조회");
        setColor(7);
        drawBox(20, 4, 80, 25, " ID | 제목                           | 대출일      | 반납 예정일  | 상태     ");
        gotoxy(20, 6);
        printf("├──────────────────────────────────────────────────────────────────────────────┤");

        int check = 0;

        for (int i = 0; i < 17; i++)
        {
            int recordIndex = startIndex + i;

            if (recordIndex >= count1)
            {
                break; // 현재 사용자 기록 끝
            }

            check = 1;

            strcpy(title, "(제목 없음)");

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
                setColor(12); // 연체
            }
            else if (userList[recordIndex].state == 1)
            {
                setColor(10); // 대출 중
            }
            else if (userList[recordIndex].state == 0)
            {
                setColor(8);  // 반납 완료
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
                userList[recordIndex].state == 0 ? "반납 완료" : (userList[recordIndex].state == 1 ? "대출 중" : "연체 중"));
        }

        setColor(7);

        if (check == 0)
        {
            gotoxy(22, 8);
            printf("대출 내역이 없습니다.");
        }

        gotoxy(20, 26);  printf("├──────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(22, 27); printf("[←] 이전 페이지  [→] 다음 페이지  [0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == -32) // 방향키
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
        else if (key == '0') // 뒤로 가기
        {
            return;
        }
    }
}

/*
    도서 추가 기능
*/
void addBook()
{
    char input[100];
    Book newbook = { 0 };
    int count = manageBookFile(books, newbook, 0, 0);
    sprintf(newbook.id, "%d", count + 1);

    system("cls");
    setColor(3); drawBox(30, 2, 60, 3, "도서 추가");
    setColor(7);
    drawBox(30, 5, 60, 19, "");
    gotoxy(30, 21); printf("├──────────────────────────────────────────────────────────┤");
    gotoxy(30, 23); printf("└──────────────────────────────────────────────────────────┘");
    gotoxy(33, 22); printf("[1] 도서 추가 [0] 뒤로 가기 : ");

    fgets(input, sizeof(input), stdin);

    if (input[0] == '0')
    {
        return;
    }
    else if (input[0] == '1')
    {
        gotoxy(33, 7);  printf("제목        : ");
        fgets(newbook.bookTitle, sizeof(newbook.bookTitle), stdin); // 엔터까지 입력받음
        newbook.bookTitle[strcspn(newbook.bookTitle, "\n")] = 0; // \n 제거

        gotoxy(33, 11); printf("저자        : ");
        fgets(newbook.bookAuthor, sizeof(newbook.bookAuthor), stdin);
        newbook.bookAuthor[strcspn(newbook.bookAuthor, "\n")] = 0;

        gotoxy(33, 15); printf("출판사      : ");
        fgets(newbook.bookPublish, sizeof(newbook.bookPublish), stdin);
        newbook.bookPublish[strcspn(newbook.bookPublish, "\n")] = 0;

        // book.txt에 책 추가하기
        if (manageBookFile(NULL, newbook, 1, 0))
        {
            gotoxy(34, 19); setColor(10); printf("도서 추가가 완료되었습니다.");
        }
        else
        {
            gotoxy(34, 19); setColor(12); printf("도서 추가 실패.");
        }
        setColor(7);
    }
    gotoxy(33, 20); system("pause");
}

/*
    도서 삭제 기능
*/
void removeBook()
{
    Book nullbook = { 0 };
    int startIndex = 0;
    int removeIndex = 0;
    char input1[10] = { 0 };
    char input2[10] = { 0 };
    char titleShort[30];

    int count = manageBookFile(books, nullbook, 0, 0); // 도서 목록 읽기

    if (count == 0)
    {
        gotoxy(12, 7); printf("도서 데이터가 없습니다.");
        gotoxy(12, 9); printf("아무 키나 누르면 돌아갑니다.");
        _getch();
        return;
    }

    while (1)
    {
        system("cls");
        setColor(3);
        drawBox(30, 2, 60, 3, "도서 삭제");
        setColor(7);
        drawBox(30, 5, 60, 22, "");

        gotoxy(31, 6); printf("번호│제목                │저자            │출판사");
        gotoxy(30, 7); printf("├──────────────────────────────────────────────────────────┤");

        for (int i = 0; i < 15; i++)
        {
            // startIndex가 첫 목록을 가리킴, i를 더해서 순차적으로 출력함
            int bookIndex = startIndex + i;

            if (bookIndex >= count)
            {
                break; // 전체 도서 수를 넘으면(책이 더 없으면) 중단하는 기능
            }

            // 제목 자르기 (10글자 초과 시 7글자에다가 말줄임표)
            if (strlen(books[bookIndex].bookTitle) > 25)
            {
                snprintf(titleShort, sizeof(titleShort), "%.14s...", books[bookIndex].bookTitle);
            }
            else
            {
                strcpy(titleShort, books[bookIndex].bookTitle);
            }

            // 순차적 출력
            setColor(3);
            gotoxy(32, 8 + i);
            printf(" %-2s│%-20s│%-16s│%-5s\n", books[bookIndex].id, titleShort,
                books[bookIndex].bookAuthor, books[bookIndex].bookPublish);
            setColor(7);
        }

        gotoxy(30, 24); printf("├──────────────────────────────────────────────────────────┤");
        gotoxy(30, 26); printf("└──────────────────────────────────────────────────────────┘");
        gotoxy(33, 25); printf("[1] 삭제할 도서 입력 [0] 뒤로 가기");

        char key = _getch();

        if (key == 0 || key == -32)  // -32 기본 값인듯
        {
            key = _getch();  // 실제 키 값 읽는거

            if (key == LEFT && startIndex >= 15)
            {
                startIndex = startIndex - 15; // 15 빼서 이전에 출력된 15개의 목록 나오게끔
            }
            else if (key == RIGHT && startIndex + 15 < count)
            {
                startIndex = startIndex + 15;
            }
            continue;
        }
        else if (key == '0')  // 뒤로가기
        {
            return;
        }
        else if (key == '1')
        {
            gotoxy(47, 25); printf("                             ");
            gotoxy(33, 25); printf("삭제할 도서 번호 입력 : ");
            fgets(input1, sizeof(input1), stdin);
            input1[strcspn(input1, "\n")] = 0;

            int select = atoi(input1);

            if (select > count || select < 1)
            {
                gotoxy(34, 20); setColor(12); printf("잘못된 번호입니다.");
                setColor(7); _getch();
                continue;
            }

            removeIndex = select - 1;
        }

        system("cls");
        setColor(3); drawBox(30, 2, 60, 3, "도서 삭제 확인"); setColor(7);
        drawBox(30, 5, 60, 9, "");
        setColor(12); gotoxy(34, 7); printf("정말로 삭제하시겠습니까?"); setColor(7);
        gotoxy(34, 8); printf("제목: %s", books[removeIndex].bookTitle);

        gotoxy(34, 9); printf("[Y] 예  [N] 아니오(뒤로 가기) : ");
        fgets(input2, sizeof(input2), stdin);
        input2[strcspn(input2, "\n")] = 0;

        if (input2[0] == 'y')
        {
            for (int i = removeIndex; i < count - 1; i++)
            {
                // 지우고 싶은 행 밑에 있는 행들을 한 줄씩 당겨와서 덮어씌우는 방식인데 잘 됨
                books[i] = books[i + 1];
            }
            count--; // 항목수 감소

            // borrowList.txt에 저장하는 과정
            if (manageBookFile(books, nullbook, 2, count))
            {
                // 책 번호 다시 써야 되는데
                for (int i = 0; i < count; i++)
                {
                    snprintf(books[i].id, sizeof(books[i].id), "%d", i + 1);
                }

                // 파일 재저장
                manageBookFile(books, nullbook, 2, count);

                setColor(10); gotoxy(34, 11); printf("도서가 삭제되었습니다.");
                setColor(7);
            }
            gotoxy(34, 12); printf("아무 키나 누르면 돌아갑니다...");
            _getch();
            return;
        }
        else if (input2[0] == 'n')
        {
            gotoxy(34, 11); printf("취소되었습니다.");
            _getch();
            continue;
        }
        else
        {
            gotoxy(34, 11); setColor(12); printf("잘못된 입력입니다.");
            setColor(7);
        }
    }
}

/*
    대출 조회 기능 (관리자) (연체 > 대출 > 반납완료 정렬 ㄱㄱ)
*/
void viewBorrowRecords()
{
    Borrow borrowList[1000] = { 0 };
    Book books[1000] = { 0 };
    Borrow nullborrow = { 0 };
    Book nullbook = { 0 };
    int borrowCount = manageBorrowFile(borrowList, nullborrow, 0, 0);
    int bookCount = manageBookFile(books, nullbook, 0, 0);

    // state 기준 내림차순 정렬
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
        drawBox(20, 1, 80, 3, "전체 대출 내역 조회");
        setColor(7);
        drawBox(20, 4, 80, 25, " ID | 제목                           | 전화번호      | 반납 예정일 | 상태     ");
        gotoxy(20, 6); printf("├──────────────────────────────────────────────────────────────────────────────┤");

        int check = 0;

        for (int i = 0; i < 17; i++)
        {
            int recordIndex = startIndex + i;
            if (recordIndex >= borrowCount)
                break;

            check = 1;

            // 제목 찾기
            strcpy(titleShort, "제목없음");
            for (int j = 0; j < bookCount; j++)
            {
                if (strcmp(borrowList[recordIndex].id, books[j].id) == 0)
                {
                    strcpy(titleShort, books[j].bookTitle);
                    break;
                }
            }

            // 상태별 색상
            if (borrowList[recordIndex].state == 2)
            {
                setColor(12); // 연체
            }
            else if (borrowList[recordIndex].state == 1)
            {
                setColor(10); // 대출 중
            }
            else if (borrowList[recordIndex].state == 0)
            {
                setColor(8);  // 반납 완료
            }
            else
            {
                setColor(7);
            }

            gotoxy(22, 8 + i);
            printf("%-2s | %-30s | %-13s | %d-%02d-%02d  | %s",
                borrowList[recordIndex].id, titleShort, borrowList[recordIndex].borrowerPhone,
                borrowList[recordIndex].returnYear, borrowList[recordIndex].returnMonth, borrowList[recordIndex].returnDay,
                borrowList[recordIndex].state == 0 ? "반납 완료" : (borrowList[recordIndex].state == 1 ? "대출 중" : "연체 중"));
        }

        setColor(7);
        if (check == 0)
        {
            gotoxy(22, 8);
            printf("대출 내역이 없습니다.");
        }

        gotoxy(20, 26); printf("├──────────────────────────────────────────────────────────────────────────────┤");
        gotoxy(22, 27); printf("[←] 이전 페이지  [→] 다음 페이지  [0] 뒤로 가기");

        char key = _getch();
        if (key == 0 || key == -32)  // 방향키
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

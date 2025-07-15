#pragma once

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
    char bookAuthor[30]; // 도서 저자
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
} Borrow;

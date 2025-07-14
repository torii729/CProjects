#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define TOTAL_BOOKS 100
#define BOOKS_PER_PAGE 10

char books[TOTAL_BOOKS][50]; // å ���� ����

void drawPage(int page) {
    system("cls");
    printf("����������������������������������������������\n");
    printf("��      ���� ����       ��\n");
    printf("����������������������������������������������\n");

    int start = page * BOOKS_PER_PAGE;
    int end = start + BOOKS_PER_PAGE;
    if (end > TOTAL_BOOKS) end = TOTAL_BOOKS;

    for (int i = start; i < end; i++) {
        printf("�� %2d. %-18s��\n", i + 1, books[i]);
    }

    printf("����������������������������������������������\n");
    printf("�� �� ����   ������ %2d/%2d   ���� �� ��\n", page + 1, (TOTAL_BOOKS + BOOKS_PER_PAGE - 1) / BOOKS_PER_PAGE);
    printf("����������������������������������������������\n");
}

int main() {
    int page = 0;
    int totalPages = (TOTAL_BOOKS + BOOKS_PER_PAGE - 1) / BOOKS_PER_PAGE;

    // ���ÿ� ���� å �̸�
    for (int i = 0; i < TOTAL_BOOKS; i++) {
        sprintf(books[i], "å %d", i + 1);
    }

    while (1) {
        drawPage(page);

        int key = _getch();
        if (key == 224) { // ����Ű
            key = _getch();
            if (key == 75 && page > 0) page--;        // ��
            else if (key == 77 && page < totalPages - 1) page++;  // ��
        }
        else if (key == 27) { // Esc Ű
            break;
        }
    }

    return 0;
}

/*



*/

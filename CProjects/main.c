// ������ ���� ���α׷�

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // gotoxy, setColor ���

#define MAX_MEMBERS 100

typedef struct {
    char phone[20];
    char password[20];
} Member;

Member members[MAX_MEMBERS];
int memberCount = 0;

// �ܼ� Ŀ�� �̵�
void gotoxy(int x, int y) {
    COORD Pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �ؽ�Ʈ ���� ����
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ȸ�� ���� ���Ͽ��� �ҷ�����
void loadMembers() {
    FILE* file = fopen("member.txt", "r");
    if (file == NULL) {
        printf("ȸ�� ������ �ҷ��� �� �����ϴ�.\n");
        return;
    }

    while (fscanf(file, "%s %s", members[memberCount].phone, members[memberCount].password) == 2) {
        memberCount++;
    }

    fclose(file);
}

// ���� �޴� UI
void drawMainMenu() {
    system("cls");
    setColor(10); // �ʷϻ�

    gotoxy(3, 0); printf("��������������������������������������������������������������������������������������������");
    gotoxy(3, 1); printf("��");
    gotoxy(3, 2); printf("��");
    gotoxy(3, 3); printf("��");
    gotoxy(3, 4); printf("��");
    gotoxy(3, 5); printf("��");
    gotoxy(3, 6); printf("��");
    gotoxy(3, 7); printf("��");
    gotoxy(3, 8); printf("��");
    gotoxy(3, 9); printf("��");
    gotoxy(3, 10); printf("��");
    gotoxy(3, 11); printf("��");
    gotoxy(3, 12); printf("��");
    gotoxy(3, 13); printf("��");
    gotoxy(3, 14); printf("��");
    gotoxy(3, 15); printf("��������������������������������������������������������������������������������������������");

    gotoxy(48, 1); printf("��");
    gotoxy(48, 2); printf("��");
    gotoxy(48, 8); printf("��");
    gotoxy(48, 9); printf("��");
    gotoxy(48, 10); printf("��");
    gotoxy(48, 11); printf("��");
    gotoxy(48, 12); printf("��");
    gotoxy(48, 13); printf("��");
    gotoxy(48, 14); printf("��");

    gotoxy(10, 3); printf("������������������������������������������������������������        ��");
    gotoxy(10, 4); printf("��        ������ �ý���       ��        ��");
    gotoxy(10, 5); printf("������������������������������������������������������������        ��");
    gotoxy(10, 6); printf("  1. �α���                           ��");
    gotoxy(10, 7); printf("  2. ����                             ��");
    gotoxy(10, 9); printf("  �޴� �Է� : ");

    setColor(7); // �⺻ ����
}

// �α��� ���
int login() {
    char phone[20], password[20];

    system("cls");
    setColor(11); // ���� �Ķ�
    gotoxy(3, 0); printf("��������������������������������������������������������������������������������������������");
    gotoxy(3, 1); printf("��");
    gotoxy(3, 2); printf("��");
    gotoxy(3, 3); printf("��");
    gotoxy(3, 4); printf("��");
    gotoxy(3, 5); printf("��");
    gotoxy(3, 6); printf("��");
    gotoxy(3, 7); printf("��");
    gotoxy(3, 8); printf("��");
    gotoxy(3, 9); printf("��");
    gotoxy(3, 10); printf("��");
    gotoxy(3, 11); printf("��");
    gotoxy(3, 12); printf("��");
    gotoxy(3, 13); printf("��");
    gotoxy(3, 14); printf("��");
    gotoxy(3, 15); printf("��������������������������������������������������������������������������������������������");

    gotoxy(48, 1); printf("��");
    gotoxy(48, 2); printf("��");
    gotoxy(48, 8); printf("��");
    gotoxy(48, 9); printf("��");
    gotoxy(48, 10); printf("��");
    gotoxy(48, 11); printf("��");
    gotoxy(48, 12); printf("��");
    gotoxy(48, 13); printf("��");
    gotoxy(48, 14); printf("��");

    gotoxy(10, 3); printf("������������������������������������������������������������        ��");
    gotoxy(10, 4); printf("��        ������ �α���       ��        ��");
    gotoxy(10, 5); printf("������������������������������������������������������������        ��");

    gotoxy(48, 6); printf("��");
    gotoxy(48, 7); printf("��");

    setColor(7);

    gotoxy(10, 6); printf("��ȭ��ȣ �Է�");
    gotoxy(10, 7); printf("[ex) 010-xxxx-xxxx] : ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0;

    gotoxy(10, 8); printf("��й�ȣ [���� 4�� + !] : ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    for (int i = 0; i < memberCount; i++)
    {
        if (strcmp(members[i].phone, phone) == 0 && strcmp(members[i].password, password) == 0) {
            system("cls");
            setColor(10);
            gotoxy(3, 0); printf("��������������������������������������������������������������������������������������������");
            gotoxy(3, 1); printf("��");
            gotoxy(3, 2); printf("��");
            gotoxy(3, 3); printf("��");
            gotoxy(3, 4); printf("��");
            gotoxy(3, 5); printf("��");
            gotoxy(3, 6); printf("��");
            gotoxy(3, 7); printf("��");
            gotoxy(3, 8); printf("��");
            gotoxy(3, 9); printf("��");
            gotoxy(3, 10); printf("��");
            gotoxy(3, 11); printf("��");
            gotoxy(3, 12); printf("��");
            gotoxy(3, 13); printf("��");
            gotoxy(3, 14); printf("��");
            gotoxy(3, 15); printf("��������������������������������������������������������������������������������������������");

            gotoxy(48, 1); printf("��");
            gotoxy(48, 2); printf("��");
            gotoxy(48, 8); printf("��");
            gotoxy(48, 9); printf("��");
            gotoxy(48, 10); printf("��");
            gotoxy(48, 11); printf("��");
            gotoxy(48, 12); printf("��");
            gotoxy(48, 13); printf("��");
            gotoxy(48, 14); printf("��");

            gotoxy(10, 3); printf("������������������������������������������������������������        ��");
            gotoxy(10, 4); printf("��        ������ �ý���       ��        ��");
            gotoxy(10, 5); printf("������������������������������������������������������������        ��");
            gotoxy(10, 6); printf("�α��� ����! ȯ���մϴ�.\n");
            setColor(7);
            system("pause");
            return 1;
        }
    }

    setColor(12);
    gotoxy(10, 9); printf("�α��� ����: ��ȭ��ȣ �Ǵ� ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n");
    setColor(7);
    system("pause");
    return 0;
}

int main() 
{
    char menuInput[10];
    int choice = 0;

    loadMembers();  // ���Ͽ��� ȸ�� ���� �ҷ�����

    while (1) {
        drawMainMenu();
        fgets(menuInput, sizeof(menuInput), stdin);
        choice = atoi(menuInput);  // ���ڿ��� ������ ��ȯ

        if (choice == 1) {
            if (login()) {
                break; // �α��� ����
            }
        }
        else if (choice == 2) {
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�.\n");
            system("pause");
        }
    }

    return 0;
}
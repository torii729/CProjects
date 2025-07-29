#pragma once

// ����� ���� ����ü
typedef struct
{
    char name[20]; // ����� �̸�
    char phone[20]; // ��ȭ��ȣ
    char password[20]; // ��й�ȣ
} Member;

// ���� ���� ����ü
typedef struct
{
    char id[30]; // ���� ID
    char bookTitle[50]; // ���� ����
    char bookAuthor[30]; // ���� ����
    char bookPublish[20]; // ���ǻ�
} Book;

// ���� ���� ����ü
typedef struct
{
    char id[30]; // ���� ID
    char borrowerPhone[20]; // ������ ��ȭ��ȣ
    int borrowYear; // ���� ����
    int borrowMonth; // ���� ��
    int borrowDay; // ���� ��
    int returnYear; // �ݳ� ����
    int returnMonth; // �ݳ� ��
    int returnDay; // �ݳ� ��
    int state; // ���� ����(0: ����, 1: ������, 2: ��ü)
} Borrow;

#pragma once

#include <iostream>
#include <string>

using namespace std;

#define FILESYSTEM_SIZE 1000


struct File
{
    string fileName; // �������� �����
    int fileSize; // ������ �����
    unsigned char* data; // ������
};


struct Node // ���������, ���������� ������ ������
{
    File* file; // ����
    Node* next, * prev; // ��������� �� ������ ���������� � ����������� ��������� ������
};


class FileSystem
{
    Node* head, * tail; // ��������� �� ������ ������ ������ � ��� �����
    int nodesCount; // ���������� ���������
    int size; // ���������� ��������� ������ � ������� �������

public:
    FileSystem(); // �����������
    FileSystem(const FileSystem&); // ����������� �����������
    ~FileSystem(); // ����������

    void addTail(File* file); // ���������� � ����� ������
    void addHead(File* file); // ���������� � ������ ������
    void add(int pos, File* file); // ������� ��������

    void del(int pos = 0); // �������� ��������
    void delAll(); // ������� ���� ������

    int getCount(); // �������� ����������
    int getFreeSize(); // �������� ���������� ��������� ������
    Node* get(int); // �������� ������� ������

    int checkFile(string fileName); // ��������� ���� �� ���� � ����� ������
    void filesList(); // ������ ������ ���� ������

    void print(int pos); // ������ ������������� ��������
    File* copy(string fileName); // ���������� ����

};

int autotest();
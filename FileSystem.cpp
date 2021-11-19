#include "Header.h"


FileSystem::FileSystem() // ��������������
{
    head = NULL;
    tail = NULL;
    nodesCount = 0;
    size = FILESYSTEM_SIZE;
}

FileSystem::FileSystem(const FileSystem& L)
{
    head = tail = NULL;
    nodesCount = 0;

    // ������ ������, �� �������� ��������
    Node* temp = L.head;
    while (temp != NULL) { // ���� �� ����� ������
        // �������� ������
        addTail(temp->file);
        temp = temp->next;
    }
}

FileSystem::~FileSystem() //����������
{
    delAll(); // ������� ��� ��������
}

void FileSystem::addHead(File* file)
{
    Node* temp = new Node; // ������� ����� �������

    temp->prev = NULL; // ����������� ���
    temp->file = file; // ��������� ������
    temp->next = head; // ��������� - ������ ������

    if (head != NULL) { // ���� �������� ����
        head->prev = temp;
    }

    // ���� ������� ������, �� �� ������������ � ������ � �����
    if (nodesCount == 0) {
        head = tail = temp;
    }
    else { // ����� ����� ������� - ��������
        head = temp;
    }

    size -= file->fileSize;
    nodesCount++;
}

void FileSystem::addTail(File* file)
{
    Node* temp = new Node; // ������� ����� �������
    temp->next = NULL; // ���������� ���
    temp->file = file; // ��������� ������
    temp->prev = tail; // ���������� - ������ �����

    if (tail != NULL) { // ���� �������� ����?
        tail->next = temp;
    }

    // ���� ������� ������, �� �� ������������ � ������ � �����
    if (nodesCount == 0) {
        head = tail = temp;
    }
    else { // ����� ����� ������� - ���������
        tail = temp;
    }

    size -= file->fileSize;
    nodesCount++;
}

void FileSystem::add(int pos, File* file)
{
    if (pos < 1 || pos > nodesCount + 1) { // ������� �� 1 �� nodesCount?
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    if (pos == nodesCount + 1) { // ���� ������� � ����� ������
        addTail(file);
        return;
    }
    else if (pos == 1) { // ���� ������� � ������ ������
        addHead(file);
        return;
    }


    // ����������� �� ������ n - 1 ���������
    Node* ins = head;
    int i = 1; // �������
    while (i < pos) { // ������� �� ��������, ����� ������� �����������
        ins = ins->next;
        i++;
    }

    // ������� �� ��������, ������� ������������
    Node* prevIns = ins->prev;

    Node* temp = new Node; // ������� ����� �������
    temp->file = file;

    // ��������� ������
    if (prevIns != NULL && nodesCount != 1) {
        prevIns->next = temp;
    }

    temp->next = ins;
    temp->prev = prevIns;
    ins->prev = temp;

    size -= file->fileSize;
    nodesCount++;
}

void FileSystem::del(int pos)
{
    Node* del = head;

    int i = 1; // �������
    while (i < pos) { // ������� �� ��������, ������� ���������
        del = del->next;
        i++;
    }

    // ������� �� ��������, ������� ������������ ����������
    Node* prevDel = del->prev;
    // ������� �� ��������, ������� ������� �� ���������
    Node* afterDel = del->next;

    // ���� ������� �� ������
    if (prevDel != NULL && nodesCount != 1)
        prevDel->next = afterDel;
    // ���� ������� �� �����
    if (afterDel != NULL && nodesCount != 1)
        afterDel->prev = prevDel;

    // ��������� �������?
    if (pos == 1) {
        head = afterDel;
    }
    if (pos == nodesCount) {
        tail = prevDel;
    }
    
    size += del->file->fileSize;

    delete del; // �������� ��������
    nodesCount--;
}

void FileSystem::delAll()
{
    // ���� �������� ��������, ������� �� ������ � ������
    while (nodesCount != 0) {
        del(1);
    }
}

int FileSystem::getCount()
{
    return nodesCount;
}

int FileSystem::getFreeSize()
{
    return size;
}

Node* FileSystem::get(int pos)
{
    if (pos < 1 || pos > nodesCount) { // ������� �� 1 �� nodesCount?
        // �������� �������
        cout << "Incorrect position !!!\n";
        return 0;
    }

    Node* temp = head;

    int i = 1;
    while (i < pos && temp != 0) { // ���� ������ ��� �������
        temp = temp->next;
        i++;
    }

    if (temp != NULL) {
        return temp;
    }
    return NULL;
}


void FileSystem::print(int pos)
{
    if (pos < 1 || pos > nodesCount) { // ������� �� 1 �� nodesCount?
        // �������� �������
        cout << "Incorrect position !!!\n";
        return;
    }

    Node* temp;

    // ���������� � ����� ������� ������� ���������
    if (pos <= nodesCount / 2) { // ������ � ������
        temp = head;
        int i = 1;

        while (i < pos) {
            // ��������� �� ������� ��������
            temp = temp->next;
            i++;
        }
    }
    else { // ������ � ������
        temp = tail;
        int i = 1;

        while (i <= nodesCount - pos) {
            // ��������� �� ������� ��������
            temp = temp->prev;
            i++;
        }
    }
    // ����� ��������
    cout << pos << "File: ";
    cout << "    " << temp->file->fileName << endl;
    cout << "        " << temp->file->data << endl;
}

File* FileSystem::copy(string fileName)
{
    int filePos = checkFile(fileName);
    if (filePos != 0) {
        File* f = get(filePos)->file;
        File* copyFile = new File;
        copyFile->fileName = string("copy_") + f->fileName;
        copyFile->fileSize = f->fileSize;
        copyFile->data = new unsigned char[f->fileSize];

        for (int i = 0; i < f->fileSize; i++) {
            copyFile->data[i] = f->data[i];
        }
        addTail(copyFile);

        return copyFile;
    }
    return NULL;
}

void FileSystem::filesList()
{
    // ���� � ������ ������������ ��������, �� ����������� �� ����
    // � �������� ��������, ������� � �������
    if (nodesCount != 0) {
        Node* temp = head;
        cout << "Files:" << endl;
        while (temp->next != NULL) {
            cout << "    " << temp->file->fileName << endl;
            cout << "        " << temp->file->data << endl;
            temp = temp->next;
        }
        cout << "    " << temp->file->fileName << endl;
        cout << "        ";
        for (int i = 0; i < temp->file->fileSize; i++) {
            cout << temp->file->data[i];
        }
        cout << endl;
        cout << endl;
    }
    else {
        cout << endl << "No files!" << endl;
    }
}

int FileSystem::checkFile(string fileName)
{
    int pos = 1; // ������� �����
    if (nodesCount != 0) {
        Node* temp = head;
        while (temp->next != NULL) {
            if (temp->file->fileName == fileName) {
                return pos;
            }
            pos++;
            temp = temp->next;
        }
        if (temp->file->fileName == fileName) {
            return pos;
        }
    }
    return 0;
}

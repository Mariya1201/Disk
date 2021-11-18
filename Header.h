#pragma once

#include <iostream>
#include <string>

using namespace std;

#define FILESYSTEM_SIZE 1000


struct File
{
    string fileName; // Название файла
    int fileSize; // Размер файла
    unsigned char* data; // Данные
};


struct Node // Структура, являющаяся звеном списка
{
    File* file; // Файл
    Node* next, * prev; // Указатели на адреса следующего и предыдущего элементов списка
};


class FileSystem
{
    Node* head, * tail; // Указатели на адреса начала списка и его конца
    int nodesCount; // Количество элементов
    int size; // Количество свободной памяти в фаловой системе

public:
    FileSystem(); // Конструктор
    FileSystem(const FileSystem&); // Конструктор копирования
    ~FileSystem(); // Деструктор

    void addTail(File* file); // Добавление в конец списка
    void addHead(File* file); // Добавление в начало списка
    void add(int pos, File* file); // Вставка элемента

    void del(int pos = 0); // Удаление элемента
    void delAll(); // Удалить весь список

    int getCount(); // Получить количество
    int getFreeSize(); // Получить количество свободной памяти
    Node* get(int); // Получить элемент списка

    int checkFile(string fileName); // Проверяет есть ли файл с таким именем
    void filesList(); // Печать списка всех файлов

    void print(int pos); // Печать определенного элемента
    File* copy(string fileName); // Копировать файл

};

int autotest();
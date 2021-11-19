#include "Header.h"


FileSystem::FileSystem() // Инициализируем
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

    // Голова списка, из которого копируем
    Node* temp = L.head;
    while (temp != NULL) { // Пока не конец списка
        // Копируем данные
        addTail(temp->file);
        temp = temp->next;
    }
}

FileSystem::~FileSystem() //Деструктор
{
    delAll(); // Удаляем все элементы
}

void FileSystem::addHead(File* file)
{
    Node* temp = new Node; // Создаем новый элемент

    temp->prev = NULL; // Предыдущего нет
    temp->file = file; // Заполняем данные
    temp->next = head; // Следующий - бывшая голова

    if (head != NULL) { // Если элементы есть
        head->prev = temp;
    }

    // Если элемент первый, то он одновременно и голова и хвост
    if (nodesCount == 0) {
        head = tail = temp;
    }
    else { // Иначе новый элемент - головной
        head = temp;
    }

    size -= file->fileSize;
    nodesCount++;
}

void FileSystem::addTail(File* file)
{
    Node* temp = new Node; // Создаем новый элемент
    temp->next = NULL; // Следующего нет
    temp->file = file; // Заполняем данные
    temp->prev = tail; // Предыдущий - бывший хвост

    if (tail != NULL) { // Если элементы есть?
        tail->next = temp;
    }

    // Если элемент первый, то он одновременно и голова и хвост
    if (nodesCount == 0) {
        head = tail = temp;
    }
    else { // Иначе новый элемент - хвостовой
        tail = temp;
    }

    size -= file->fileSize;
    nodesCount++;
}

void FileSystem::add(int pos, File* file)
{
    if (pos < 1 || pos > nodesCount + 1) { // Позиция от 1 до nodesCount?
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    if (pos == nodesCount + 1) { // Если вставка в конец списка
        addTail(file);
        return;
    }
    else if (pos == 1) { // Если вставка в начало списка
        addHead(file);
        return;
    }


    // Отсчитываем от головы n - 1 элементов
    Node* ins = head;
    int i = 1; // Счетчик
    while (i < pos) { // Доходим до элемента, перед которым вставляемся
        ins = ins->next;
        i++;
    }

    // Доходим до элемента, который предшествует
    Node* prevIns = ins->prev;

    Node* temp = new Node; // Создаем новый элемент
    temp->file = file;

    // настройка связей
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

    int i = 1; // Счетчик
    while (i < pos) { // Доходим до элемента, который удаляется
        del = del->next;
        i++;
    }

    // Доходим до элемента, который предшествует удаляемому
    Node* prevDel = del->prev;
    // Доходим до элемента, который следует за удаляемым
    Node* afterDel = del->next;

    // Если удаляем не голову
    if (prevDel != NULL && nodesCount != 1)
        prevDel->next = afterDel;
    // Если удаляем не хвост
    if (afterDel != NULL && nodesCount != 1)
        afterDel->prev = prevDel;

    // Удаляются крайние?
    if (pos == 1) {
        head = afterDel;
    }
    if (pos == nodesCount) {
        tail = prevDel;
    }
    
    size += del->file->fileSize;

    delete del; // Удаление элемента
    nodesCount--;
}

void FileSystem::delAll()
{
    // Пока остаются элементы, удаляем по одному с головы
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
    if (pos < 1 || pos > nodesCount) { // Позиция от 1 до nodesCount?
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return 0;
    }

    Node* temp = head;

    int i = 1;
    while (i < pos && temp != 0) { // Ищем нужный нам элемент
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
    if (pos < 1 || pos > nodesCount) { // Позиция от 1 до nodesCount?
        // Неверная позиция
        cout << "Incorrect position !!!\n";
        return;
    }

    Node* temp;

    // Определяем с какой стороны быстрее двигаться
    if (pos <= nodesCount / 2) { // Отсчет с головы
        temp = head;
        int i = 1;

        while (i < pos) {
            // Двигаемся до нужного элемента
            temp = temp->next;
            i++;
        }
    }
    else { // Отсчет с хвоста
        temp = tail;
        int i = 1;

        while (i <= nodesCount - pos) {
            // Двигаемся до нужного элемента
            temp = temp->prev;
            i++;
        }
    }
    // Вывод элемента
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
    // Если в списке присутствуют элементы, то пробегаемся по нему
    // и печатаем элементы, начиная с первого
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
    int pos = 1; // Позиция файла
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

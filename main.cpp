#include "Header.h"


void menu() {
    cout << endl;
    cout << "______________________" << endl;
    cout << endl;
    cout << "Vyberite deystvie:" << endl;
    cout << "1 - sozdat' fail" << endl;          // Создать файл
    cout << "2 - udalit' fail" << endl;          // Удалить файл
    cout << "3 - kopirovat' fail" << endl;       // Копировать файл
    cout << "4 - pereimenovat' fail" << endl;    // Переименовать файл
    cout << "5 - poluchit' dlinu faila" << endl; // Получить длину файла
    cout << "6 - poluchit' spisok vseh failov" << endl; // Получить список всех файлов
    cout << "7 - prochitat' fayl" << endl;       // Прочитать файл
    cout << "8 - zapisat' v fayl" << endl;       // Записать в файл
    cout << "0 - exit" << endl; // Завершим программу
    cout << "______________________" << endl;
    cout << endl;
}


int main()
{
    if (autotest() == 0) {

        FileSystem fileSystem;
        int a = -1; // Команда, которую надо выполнить

        while (a != 0) { // Будем требовать ввод команды пока не встретим команду выхода - 0
            menu();
            cout << "Your choose: ";
            cin >> a;
            cout << endl;

            // Нужно для того, чтобы корректно работал getline(cin, fileName) :
            // cin.clear();
            cin.ignore(32767, '\n'); // Игнорируем символы перевода строки "\n" 
                
            if (a == 0) break;
            while (a != 1 && a != 2 && a != 3 && a != 4 && a != 5 && a != 6 && a != 7 && a != 8) {
                cout << "Incorrect! Your choose: ";
                cin >> a;
            }

            if (a == 1) { // Создать файл
                File* file = new File;
                int size;
                char* data;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, file->fileName); // Получение названия файла

                if (fileSystem.checkFile(file->fileName) == 0) {
                    cout << "Vvedite razmer fayla v bitah (kolichestvo simvolov):" << endl;
                    cin >> size;
                    cin.ignore();

                    if (size <= fileSystem.getFreeSize()) {
                        file->data = new char[size];
                        cout << "Vvedite dannye fayla:" << endl;
                       
                        
                        //for (int i = 0; i < size; i++) {
                        //    cin >> file->data[i];
                        //}
                        //cin >> file->data;
                        // getline(cin, file->data);
                        cin.getline(file->data, 10000);

                        int dataSize = 0; // длина введенной строки
                        while (file->data[dataSize] != '\0') {
                            dataSize++;
                        }

                        if (dataSize > size) {
                            cout << "Sliskom dlinnaya stroka!" << endl;
                            continue;
                        }
                        if (dataSize < size) {
                           cout << "Preduprezhdenie - vvedeno menshe simvolow, chem mozno" << endl;
                           continue;
                        }


                        file->fileSize = size;
                        fileSystem.addTail(file);
                    }
                    else {
                        cout << "Nedostatochno mesta na diske!" << endl;
                        continue;
                    }
                }
                else {
                    cout << "Fayl s takim imenem yze sozdan!" << endl;
                    continue;
                }

            }

            if (a == 2) { // Удалить файл
                string fileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); 

                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    fileSystem.del(filePos);
                    cout << "Fayl uspeshno udalen!" << endl;
                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

            if (a == 3) { // Копировать файл
                string fileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); 
                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    File* copyFile = fileSystem.copy(fileName);
                    cout << "Fayl uspeshno skopirovan! Noviy fayl: " << copyFile->fileName << endl;
                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

            if (a == 4) { // Переименовать файл
                string fileName;
                string newFileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); 

                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    cout << "Vvedite novoe nazvanie:" << endl;
                    getline(cin, newFileName);
                    File* f = fileSystem.get(filePos)->file;
                    f->fileName = newFileName;
                    cout << "Fayl uspeshno pereimenovan!" << endl;
                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

            if (a == 5) { // Получить длину файла
                string fileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); 

                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    File* f = fileSystem.get(filePos)->file;
                    cout << "Razmer faila - " << f->fileSize << endl;
                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

            if (a == 6) { // Получить список всех файлов
                fileSystem.filesList();
            }

            if (a == 7) { 
                string fileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); 

                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    File* f = fileSystem.get(filePos)->file;

                    int count;
                    int offset;

                    cout << "Skol'ko simvolov prochitat' - ";
                    cin >> count;
                    cout << "Smeshenie (nachinaya s 0) - ";
                    cin >> offset;

                    if (offset >= 0 && offset < f->fileSize && count <= f->fileSize) {
                        int offsetCount = count + offset;
                        if (offsetCount > f->fileSize) {
                            offsetCount = f->fileSize;
                        }
                        cout << "Dannye faila " << f->fileName << ":" << endl;

                  

                        for (int i = offset; i < offsetCount; i++) {
                            if (f->data[i] == '\0') break;
                            cout << f->data[i];
                        }
                    }
                    else {
                        cout << "Nevernie dannye!" << endl;
                        continue;
                    }


                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

            if (a == 8) { // Записать в файл
                string fileName;
                cout << "Vvedite nazvanie fayla:" << endl;
                getline(cin, fileName); // Получение названия файла

                int filePos = fileSystem.checkFile(fileName);
                if (filePos != 0) {
                    File* f = fileSystem.get(filePos)->file;
                    int count;
                    int offset;

                    cout << "Skol'ko simvolov zapisat' - ";
                    cin >> count;
                    cout << "Smeshenie (nachinaya s 0) - ";
                    cin >> offset;

                    if (offset >= 0 && offset < f->fileSize && count <= fileSystem.getFreeSize()) {
                        int offsetCount = count + offset;
   
                        cout << "Vvedite " << count << " simvolov (po odnomu, cherez enter):" << endl;
                        
                        if (offsetCount <= f->fileSize) {
                            for (int i = offset; i < offsetCount; i++) {
                                cin >> f->data[i];
                            }
                        }
                        else {

                            if ((offsetCount - f->fileSize) > fileSystem.getFreeSize()) {
                                cout << "Nedosatochno mesta na diske!" << endl;
                                continue;
                            }

                            char* oldData = new char[f->fileSize]; // старые данные файла
                            for (int i = 0; i < f->fileSize; i++) {
                                oldData[i] = f->data[i];
                            }

                            f->fileSize = offsetCount;
                            f->data = new char[offsetCount];
                            for (int i = 0; i < offsetCount; i++) {
                                if (i >= offset) {
                                    cin >> f->data[i];
                                }
                                else {
                                    f->data[i] = oldData[i];
                                }
                                
                            }
                        }
                        
                    }
                    else {
                        cout << "Nevernie dannye!" << endl;
                        continue;
                    }
                }
                else {
                    cout << "Fayl ne nayden!" << endl;
                    continue;
                }
            }

        }
    } else {
         cout << endl << "Something went wrong!" << endl;
    }

    return 0;
}





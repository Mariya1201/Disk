#include"Header.h"


int autotest1() {
    bool boolean = false;
    FileSystem fileSystem;
    File* file = new File;
    string fileName = "file1.txt";

    file->fileName = fileName;
    file->fileSize = 10;
    file->data = new unsigned char[10] ;
    unsigned char a[10] = "qwer";
    file->data = a;

    fileSystem.addTail(file);

    if (fileSystem.checkFile(fileName) == 0) {
        boolean = true;
    }

     fileSystem.copy(fileName);

    if (fileSystem.checkFile(string("copy_") + fileName) == 0) {
        boolean = true;
    }

    // cout << file->data << endl;

    return boolean;
}

int autotest2() {
    bool boolean = false;
    FileSystem fileSystem;
    File* file1 = new File;
    File* file2 = new File;
    string fileName1 = "file1.txt";
    string fileName2 = "file2.txt";

    file1->fileName = fileName1;
    file1->fileSize = 10;
    file1->data = new unsigned char[10];
    unsigned char a1[10] = "qwer";
    file1->data = a1;

    file2->fileName = fileName2;
    file2->fileSize = 10;
    file2->data = new unsigned char[10];
    unsigned char a2[10] = "trewq";
    file2->data = a2;

    fileSystem.addTail(file1);
    fileSystem.addTail(file2);

    if (fileSystem.checkFile(fileName1) == 0 || fileSystem.checkFile(fileName2) == 0) {
        boolean = true;
    }

    fileSystem.del(1);

    if (fileSystem.checkFile(fileName1) != 0 || fileSystem.checkFile(fileName2) == 0) {
        boolean = true;
    }

    int filePos = fileSystem.checkFile(fileName2);
    if (filePos != 0) {
        File* f = fileSystem.get(filePos)->file;
        if (f->fileSize != 10) {
            boolean = true;
        }
    }
    else {
        boolean = true;
    }
     

    return boolean;
}

int autotest3() {
    bool boolean = false;
    FileSystem fileSystem;
    File* file1 = new File;
    File* file2 = new File;
    string fileName1 = "file1.txt";
    string fileName2 = "file2.txt";

    file1->fileName = fileName1;
    file1->fileSize = 10;
    file1->data = new unsigned char[10];
    unsigned char a1[10] = "qwer";
    file1->data = a1;

    file2->fileName = fileName2;
    file2->fileSize = 10;
    file2->data = new unsigned char[10];
    unsigned char a2[10] = "trewq";
    file2->data = a2;

    fileSystem.addTail(file1);
    fileSystem.addTail(file2);

    if (fileSystem.checkFile(fileName1) == 0 || fileSystem.checkFile(fileName2) == 0) {
        boolean = true;
    }


    int filePos1 = fileSystem.checkFile(fileName1);
    if (filePos1 != 0) {
        File* f = fileSystem.get(filePos1)->file;
        if (f->data[0] != 'q' || f->data[1] != 'w' || f->data[2] != 'e' || f->data[3] != 'r') {
            boolean = true;
        }
    } else {
        boolean = true;
    }


    return boolean;
}

int autotest() {
    if (autotest1() == 0 && autotest2() == 0 && autotest3() == 0) {
        printf("Autotests passed!\n\n");
        return 0;
    }
    else {
        printf("Autotests is not passed!\n\n");
        return 1;
    }
}
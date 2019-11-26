#ifndef CCNY_PRINTING_SYSTEM_STUDENT_H
#define CCNY_PRINTING_SYSTEM_STUDENT_H

using namespace std;

class student {
public:
    int emplID;
    int studentPageLimit = 1000;
    int printerPicked;
    string name;
    string username;
    string password;

    student(int empldID, string name, string username, string password);
    void print(printer &p, int printOrder, string nameOfFile);
    void cancelPrint(printer &p, string fileName);
    void checkPosition(printer &p);
};


#endif //CCNY_PRINTING_SYSTEM_STUDENT_H

#ifndef CCNY_PRINTING_SYSTEM_STUDENT_H
#define CCNY_PRINTING_SYSTEM_STUDENT_H

using namespace std;

class student {
public:
    int emplID;
    int pageLimit = 500;
    string name;
    string username;
    string password;

    student(int emplID);
    student(int empldID, string name, string username, string password);
    void print(printer &p, int paper);
    void cancelPrint(printer &p);
    int checkPosition(printer p);
};


#endif //CCNY_PRINTING_SYSTEM_STUDENT_H

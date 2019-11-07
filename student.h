#ifndef CCNY_PRINTING_SYSTEM_STUDENT_H
#define CCNY_PRINTING_SYSTEM_STUDENT_H

using namespace std;

class student {
public:
    int emplID;
    string firstName;
    string lastName;
    string password;

    student(int emplID);
    student(int empldID, string firstName, string lastName, string password);
    void print(printer &p);
    void cancelPrint(printer &p);
    int checkPosition(printer p);
};


#endif //CCNY_PRINTING_SYSTEM_STUDENT_H

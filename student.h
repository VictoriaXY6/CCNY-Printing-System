#ifndef CCNY_PRINTING_SYSTEM_STUDENT_H
#define CCNY_PRINTING_SYSTEM_STUDENT_H

#include <map>
#include <string>
#include "printer.h"

using namespace std;

class student {
public:
    int emplID;
    int studentPageLimit;
    int printerPicked;
    string name;
    string username;
    string password;
    map<string,int> printersUsed;

    student(int empldID=0, string name="", string username="", string password="", int studentPageLimit=1000);
    void print(printer &p, int printOrder, string nameOfFile);
    void cancelPrint(printer &p, string fileName);
    void checkPosition(printer &p, string fileName);
};


#endif //CCNY_PRINTING_SYSTEM_STUDENT_H

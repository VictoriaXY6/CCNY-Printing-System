#ifndef CCNY_PRINTING_SYSTEM_HASHTABLE_H
#define CCNY_PRINTING_SYSTEM_HASHTABLE_H

#include "student.h"
#include <string>
using namespace std;

class hashTable {
    static const int tableSize=750;
public:
    struct item {
        student s;
        item *next= nullptr;
    };
    item *table[tableSize];
    hashTable();
    int getIndex(string key);
    void addItem(student sTemp);
    bool getStudentInfo(string username, string password, student &sTemp);
    bool getStudentInfoByUsername(string username, student &sTemp);
    void printTable();
};


#endif //CCNY_PRINTING_SYSTEM_HASHTABLE_H

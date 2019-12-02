#include "hashTable.h"
#include "student.h"
#include <iostream>
#include <string>
using namespace std;

hashTable::hashTable() {
    for (int i = 0; i < tableSize; ++i) {
        table[i] = new item;
    }
}

int hashTable::getIndex(string key) {
    int hashValue=0;
    for (int i = 0; i < key.length(); ++i) {
        hashValue+=(int)key[i];
    }
    return (hashValue % tableSize);
}

void hashTable::addItem(student sTemp) {
    int index=getIndex(sTemp.username);
    if (table[index]->s.username=="") {
        table[index]->s=sTemp;
    } else {
        item *curr=table[index];
        item *n=new item;
        n->s=sTemp;
        while (curr->next!= nullptr) {
            curr=curr->next;
        }
        curr->next=n;
    }
}

bool hashTable::getStudentInfo(string username, string password, student &sTemp) {
    int index=getIndex(username);
    item *curr=table[index];
    while (curr!=nullptr) {
        if (curr->s.username==username && curr->s.password==password) {
            sTemp=curr->s;
            return true;
        }
        curr=curr->next;
    }
    return false;
}

bool hashTable::getStudentInfoByUsername(string username, student &sTemp) {
    int index=getIndex(username);
    item *curr=table[index];
    while (curr!=nullptr) {
        if (curr->s.username==username) {
            sTemp=curr->s;
            return true;
        }
        curr=curr->next;
    }
    return false;
}

void hashTable::printTable() {
    for (int i = 0; i < tableSize; ++i) {
        if (table[i]->next==nullptr) {
            cout<<"index "<<i<<": "<<table[i]->s.emplID<<","<<table[i]->s.name<<","<<table[i]->s.username<<","<<table[i]->s.password<<","<<table[i]->s.studentPageLimit<<endl;
        } else {
            cout<<"index "<<i<<": "<<table[i]->s.emplID<<","<<table[i]->s.name<<","<<table[i]->s.username<<","<<table[i]->s.password<<","<<table[i]->s.studentPageLimit<<endl;
            item *curr=table[i]->next;
            while (curr!=nullptr) {
                cout<<"index "<<i<<": "<<table[i]->s.emplID<<","<<table[i]->s.name<<","<<table[i]->s.username<<","<<table[i]->s.password<<","<<table[i]->s.studentPageLimit<<endl;
                curr=curr->next;
            }
        }
    }
}





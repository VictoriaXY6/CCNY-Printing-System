#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

//constructor to only initialize emplID (for testing purpose, not intended to put in final code)
student::student(int emplID) : emplID(emplID) {}

//constructor to initialize all the information about student
student::student(int empldID, string name, string username, string password)
        : emplID(empldID), name(name), username(username), password(password) {}

//pushes student's print job to whatever printer they select and prints n = printOrder pages
void student::print(printer &p, int printOrder) {
    if(studentPageLimit >= printOrder) {
        studentPageLimit -= printOrder;
        p.enqueue(emplID, printOrder);
    } else {
        cout << "Sorry you have used all of your papers for this semester." << endl;
    }
}

//takes the students print job out of the queue.
void student::cancelPrint(printer &p) {
    node *prev = new node;
    node *curr = p.head;

    if (curr->id == emplID) {
        studentPageLimit += curr->printOrder;
        p.printerPageLimit += curr->printOrder;
        p.head = p.head->next;
    } else {
        while (curr->id != emplID) {
            prev = curr;
            curr = curr->next;
        }
        node *temp = curr;
        studentPageLimit += temp->printOrder;
        p.printerPageLimit += temp->printOrder;
        prev->next = curr->next;
    }
}

//checks what position the student is in the queue
int student::checkPosition(printer p) {
    int pos = 1;
    node *curr = p.head;
    while (curr->id != this->emplID) {
        curr = curr->next;
        pos++;
    }
    return pos;
}

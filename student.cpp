#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

//constructor to initialize all the information about student
student::student(int empldID, string name, string username, string password)
        : emplID(empldID), name(name), username(username), password(password) {}

//pushes student's print job to whatever printer they select and prints n = printOrder pages
void student::print(printer &p, int printOrder, string nameOfFile) {
    if(studentPageLimit >= printOrder) {
        studentPageLimit -= printOrder;
        p.enqueue(emplID, printOrder, nameOfFile);
    } else {
        cout << "Sorry you have used all of your papers for this semester." << endl;
    }
}

//takes the students print job out of the queue.
void student::cancelPrint(printer &p, string fileName) {
    node *prev = new node;
    node *curr = p.head;

    while (curr->fileName != fileName) {
        prev = curr;
        curr = curr->next;
    }
    node *temp = curr;
    studentPageLimit += temp->printOrder;
    p.printerPageLimit += temp->printOrder;
    prev->next = curr->next;
    delete(temp);
}

//checks what position the student is in the queue
void student::checkPosition(printer &p) {
    node *curr = p.head;
    int index = 0, occurence = 1;

    cout<<p.head->id; // HEAD IS NULL WHICH MEANS THAT LINKED LIST WAS NEVER CREATED?

    while (curr != nullptr) {
        if (curr->id == this->emplID) {
            cout << "Print job " << occurence << " has " << index << " jobs ahead." << endl;
            occurence++;
        }
        index++;
        curr = curr->next;
    }
}

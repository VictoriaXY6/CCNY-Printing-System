#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

//constructor to only initialize emplID (for testing purpose, not intended to put in final code)
student::student(int emplID) : emplID(emplID) {}

//constructor to initialize all the information about student
student::student(int empldID, string firstName, string lastName, string password)
        : emplID(empldID), firstName(firstName), lastName(lastName), password(password) {}

//pushes student's print job to whatever printer they select
void student::print(printer &p) {
    p.enqueue(emplID);
}

//takes the students print job out of the queue.
void student::cancelPrint(printer &p) {
    node *prev = new node;
    node *curr = new node;
    node *temp = new node;
    curr = p.head;
    while (this->emplID != curr->id) {
        prev = curr;
        curr = curr->next;
    }
    temp = curr;
    prev->next = curr->next;
}

//checks what position the student is in the queue
int student::checkPosition(printer p) {
    int counter = 1;
    node *curr = p.head;
    while (this->emplID != curr->id) {
        curr = curr->next;
        counter++;
    }
    return counter;
}
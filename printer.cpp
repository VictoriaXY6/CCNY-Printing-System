#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

void printer::enqueue(int userID) {
    node *temp = new node(userID);

    if (head==NULL) {
        head=temp;
        tail=temp;
    }
    else {
        tail->next=temp;
        tail=temp;
    }

    length++;
}

int printer::dequeue() {
    if (head!=NULL) {
        node *temp = head;
        head = head->next;
        int id_to_remove = temp->id;
        delete(temp);
        return id_to_remove;
    }
    else {
        return 0;
    }
}

void printer::display() {
    node *curr = head;
    while(curr != NULL) {
        cout<<curr->id;
        curr = curr->next;
    }
}
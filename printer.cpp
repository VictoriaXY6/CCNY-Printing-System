#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

void printer::enqueue(int userID, int printOrder, string nameOfFile) {
    node *temp = new node(userID, printOrder, nameOfFile);
    if (printerPageLimit >= printOrder) {
        if (head==NULL) {
            head=temp;
            tail=temp;
        }
        else {
            tail->next=temp;
            tail=temp;
        }
        printerPageLimit -= printOrder;
        length++;
    } else {
        cout << "Not enough papers to process print job. Contact Admin." << endl;
    }
}

int printer::dequeue() {
    if (head!=NULL) {
        node *temp = head;
        head = head->next;
        int id = temp->id;
        delete(temp);
        length--;
        return id;
    }
    else {
        length--;
        return 0;
    }
}

void printer::display() {
    node *curr = head;
    if (head == NULL) {
        cout << "No print jobs in printer" << endl;
    } 
    else {
        while(curr != NULL) {
            cout<<curr->id << " ";
            curr = curr->next;
        }
        cout << endl;
    }
}

bool printer::isStillInQueue(string nameOfFile) {
    node *curr = head;
    bool isAvailable=false;
    if (head != NULL) {
        while(curr != NULL) {
            if (curr->fileName==nameOfFile) {
                isAvailable=true;
                break;
            }
            curr = curr->next;
        }
    }
    
    return isAvailable;
}


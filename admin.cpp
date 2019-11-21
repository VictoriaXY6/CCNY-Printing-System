#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

void admin::clearPrinter(printer &p){
	while(p.head != NULL){
		p.dequeue();
	}
}

void admin::deletePrintJob(printer &p, student &s){
	// delete node at position associated with ID
	node *prev = new node;
    node *curr = p.head;

    if (curr->id == s.emplID) {
        s.studentPageLimit += curr->printOrder;
        p.printerPageLimit += curr->printOrder;
        p.head = p.head->next;
    } 
    else {
        while (curr->id != s.emplID) {
            prev = curr;
            curr = curr->next;
        }
        node *temp = curr;
        s.studentPageLimit += temp->printOrder;
        p.printerPageLimit += temp->printOrder;
        prev->next = curr->next;
    }


}

void admin::addpaper(printer &p){
	p.printerPageLimit = 500;
}
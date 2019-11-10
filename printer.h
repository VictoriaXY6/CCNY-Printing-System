#ifndef CCNY_PRINTING_SYSTEM_PRINTER_H
#define CCNY_PRINTING_SYSTEM_PRINTER_H

struct node {
    int id;
    node *next;

    node(int userID) {
        this->id=userID;
        this->next=NULL;
    }
};

class printer {
public:
    node *head = NULL;
    node *tail = NULL;
    int length = 0;

    void enqueue(int userID);
    int dequeue();
    void display();
    int length();

};

#endif //CCNY_PRINTING_SYSTEM_PRINTER_H

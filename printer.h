#ifndef CCNY_PRINTING_SYSTEM_PRINTER_H
#define CCNY_PRINTING_SYSTEM_PRINTER_H
using namespace std;

struct node {
    int id;
    int printOrder;
    string fileName;
    node *next;

    node(int userID = 0, int printOrder = 0, string fileName = "") {
        this->id=userID;
        this->printOrder = printOrder;
        this->fileName = fileName;
        this->next=NULL;
    }
};

class printer {
public:
    node *head = NULL;
    node *tail = NULL;
    int length = 0;
    int printerPageLimit = 500;

    void enqueue(int userID, int printOrder, string nameOfFile);
    int dequeue();
    void display();
};

#endif //CCNY_PRINTING_SYSTEM_PRINTER_H

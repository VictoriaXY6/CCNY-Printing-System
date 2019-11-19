#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include <vector>
#include <string>

using namespace std;

printer p1, p2, p3, p4, p5, p6, p7;
vector<student*> studentInfo;
vector<printer> nacPrinters = {p1, p2, p3, p4, p5, p6, p7};

student s1(1111, "John Doe","johnD","john");

int fastestPrinter() {
    int quickestPrinterPos = 0;
    printer quickestPrinter = nacPrinters.at(0);
    for (int i = 0; i < nacPrinters.size(); i++) {
        if (quickestPrinter.length > nacPrinters.at(i).length) {
            quickestPrinter = nacPrinters.at(i);
            quickestPrinterPos = i;
        }
    }
    return quickestPrinterPos;
}

int main() {
    studentInfo.push_back(&s1);
    int key1, key2, key3;
    string name, username, password;
    int emplID;

    do {
        cout<<"Welcome to the Nac Printing System!"<<endl;
        cout<<"Press 1 if you are a student."<<endl;
        cout<<"Press 2 if you are an admin."<<endl;
        cout<<"Press 3 to quit."<<endl;
        cout<<"Enter option: ";
        cin>>key1;
        cout << "\n------------------------------\n";
        if (key1==1) {
            do {
                cout<<"Press 1 if you are an existing student."<<endl;
                cout<<"Press 2 if you are a new student."<<endl;
                cout<<"Press 3 to go back."<<endl;
                cout<<"Enter option: ";
                cin>>key2;
                if (key2==1) {
                    cout<<"Enter username: ";
                    cin>>username;
                    cout<<"Enter password: ";
                    cin>>password;
                    for(int i=0; i<studentInfo.size(); i++) { // authentication
                        if (studentInfo.at(i)->username==username && studentInfo.at(i)->password==password) { // if user crendentials match, complete print job
                            int fastestPos=fastestPrinter();
                            cout << "Account verified." << endl << endl;
                            cout<<"Enter number of pages to print: ";
                            int numOfPages;
                            cin>>numOfPages;
                            studentInfo.at(i)->print(nacPrinters.at(fastestPos),numOfPages);
                            cout<<"Hi "<<studentInfo.at(i)->name<<". Print job has been added to printer number " << fastestPos << endl;
                            cout << "Paper Left in printer: " << nacPrinters.at(fastestPos).printerPageLimit << endl;
                            cout << studentInfo.at(i)->name <<" has " << studentInfo.at(i)->studentPageLimit << " papers left." << endl;
                            cout << "\n------------------------------\n";
                            break;
                        }
                        else {
                            cout<<"Invalid username or password.";
                        }
                    }
                }
                else if (key2==2) {
                    cout<<"Enter emplID: ";
                    cin>>emplID;
                    cout<<"Enter name: ";
                    cin>>name;
                    cout<<"Enter username: ";
                    cin>>username;
                    cout<<"Enter password: ";
                    cin>>password;
                    student *newStudent = new student(emplID,name,username,password);
                    studentInfo.push_back(newStudent);
                    cout<<"New Account Created for "<<name<<"!"<<endl;
                }
            } while (key2!=3);
        }
    } while (key1!=3);






    return 0;
}

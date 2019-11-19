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
    int key1, key2, key3;
    string name, username, password;
    int emplID;

    do {
        cout<<"Welcome to the Nac Printing System! Press 1 if Student, 2 if Admin, and 3 to quit."<<endl;
        cin>>key1;
        if (key1==1) {
            do {
                cout<<"Existing students press 1. New students press 2. Press 3 to go back."<<endl;
                cin>>key2;
                if (key2==1) {
                    cout<<"Enter username";
                    cin>>username;
                    cout<<"Enter password";
                    cin>>password;
                    vector<student>::iterator itr;
                    for(itr=studentInfo.begin(); itr<studentInfo.end(); itr++) { // authentication
                        if (itr->username==username && itr->password==password) { // if user crendentials match, complete print job
                            int fastestPos=fastestPrinter();
                            cout<<"Enter number of pages to print.";
                            int numOfPages;
                            cin>>numOfPages;
                            itr->print(nacPrinters.at(fastestPos),numOfPages);
                            cout<<"Hi "<<itr->name<<". Print job has been added.";
                            break;
                        }
                        else {
                            cout<<"Invalid username or password.";
                        }
                    }
                }
                else if (key2==2) {
                    cout<<"Enter name";
                    cin>>name;
                    cout<<"Enter username";
                    cin>>username;
                    cout<<"Enter password";
                    cin>>password;
                    cout<<"Enter emplID";
                    cin>>emplID;
                    student *newStudent = new student(emplID,name,username,password);
                    studentInfo.push_back(newStudent);
                    cout<<"New Account Created for "<<name<<"!";
                }
            } while (key2!=3);
        }
    } while (key1!=3);






    return 0;
}

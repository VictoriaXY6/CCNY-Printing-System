#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include <vector>
#include <string>
#include <unistd.h>


using namespace std;

printer p1, p2, p3, p4, p5, p6, p7;
vector<student*> studentInfo;
//vector<printer> nacPrinters = {p1, p2, p3, p4, p5, p6, p7};
vector<printer> nacPrinters;

student s1(1111, "john","john","john");

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
    nacPrinters.push_back(p1);
    nacPrinters.push_back(p2);
    nacPrinters.push_back(p3);
    nacPrinters.push_back(p4);
    nacPrinters.push_back(p5);
    nacPrinters.push_back(p6);
    nacPrinters.push_back(p7);
    int key1, key2, key3;
    string name, username, password;
    int emplID;

    do {
        system("clear");
        cout<<"\x1b[42m Home Screen \x1b[0m"<<endl<<endl;
        cout<<"Welcome to the Nac Printing System!"<<endl;
        cout<<"Press 1 if you are a student."<<endl;
        cout<<"Press 2 if you are an admin."<<endl;
        cout<<"Press 3 to quit."<<endl;
        cout<<"Enter option: ";
        cin>>key1;
        if (key1==1) {
            do {
                system("clear");
                cout<<"\x1b[46m Student Screen \x1b[0m"<<endl<<endl;
                cout<<"Press 1 if you are an existing student."<<endl;
                cout<<"Press 2 if you are a new student."<<endl;
                cout<<"Press 3 to go back."<<endl;
                cout<<"Enter option: ";
                cin>>key2;
                if (key2==1) {
                    system("clear");
                    bool studentInSystem=false;
                    cout<<"Enter username: ";
                    cin>>username;
                    cout<<"Enter password: ";
                    cin>>password;
                    int i;
                    for(i=0; i<studentInfo.size(); i++) { // authentication
                        if (studentInfo.at(i)->username==username && studentInfo.at(i)->password==password) { // if user crendentials match, set studentInSystem to true
                            studentInSystem=true;
                            break;
                        }
                    }
                    if (studentInSystem==true) {
                        do {
                            system("clear");
                            cout<<"\x1b[45m Printing Screen \x1b[0m"<<endl<<endl;
                            cout<<"Welcome "<<studentInfo.at(i)->name<<"!"<<endl;
                            cout<<"Press 1 if add print job."<<endl;
                            cout<<"Press 2 to check status of print job."<<endl;
                            cout<<"Press 3 to remove print job."<<endl;
                            cout<<"Press 4 to log out."<<endl;
                            cout<<"Enter option: ";
                            cin>>key3;
                            if (key3==1) {
                                system("clear");
                                int fastestPos=fastestPrinter();
                                cout<<"Enter number of pages to print: ";
                                int numOfPages;
                                cin>>numOfPages;
                                studentInfo.at(i)->print(nacPrinters.at(fastestPos),numOfPages);
                                studentInfo.at(i)->printerPicked=fastestPos;
                                cout<<"Print job has been added to printer number "<<fastestPos<<endl;
                                cout<<"Paper Left in printer: "<<nacPrinters.at(fastestPos).printerPageLimit<<endl;
                                cout<<studentInfo.at(i)->name<<" has "<<studentInfo.at(i)->studentPageLimit<<" papers left." << endl;
                                usleep(5000000); 
                            }
                            else if (key3==2) {
                                int printerStudentPicked = studentInfo.at(i)->printerPicked;
                                int positionInQueue = studentInfo.at(i)->checkPosition(nacPrinters.at(printerStudentPicked));
                                cout<<"There are "<<positionInQueue<< "students ahead of you.";
                            }
                            else if (key3==3) {
                                int printerStudentPicked = studentInfo.at(i)->printerPicked;
                                studentInfo.at(i)->cancelPrint(nacPrinters.at(printerStudentPicked));
                                cout<<"Print job succesfully cancelled.";
                            }
                        } while (key3!=4);
                    }
                    else {
                        cout<<"Invalid username or password."<<endl;
                        usleep(5000000); // pause for 5 sec
                    }
                }
                else if (key2==2) {
                    system("clear");
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
                    usleep(5000000); // pause for 5 sec
                }
            } while (key2!=3);
        }
    } while (key1!=3);






    return 0;
}

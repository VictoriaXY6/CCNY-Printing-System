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
    string key1, key2, key3, key4;
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
        if (key1=="1") {
            do {
                system("clear");
                cout<<"\x1b[46m Student Screen \x1b[0m"<<endl<<endl;
                cout<<"Press 1 if you are an existing student."<<endl;
                cout<<"Press 2 if you are a new student."<<endl;
                cout<<"Press 3 to go back."<<endl;
                cout<<"Enter option: ";
                cin>>key2;
                if (key2=="1") {
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
                            if (key3=="1") {
                                system("clear");
                                int fastestPos=fastestPrinter();
                                cout<<"Enter file name: ";
                                string fileName;
                                cin>>fileName;
                                cout<<"Enter number of pages to print: ";
                                int numOfPages;
                                cin>>numOfPages;
                                cout<<"Enter printer you want to use: ";
                                cout<<"Recommended printer: "<<fastestPos<<endl;
                                int printerToUse;
                                cin>>printerToUse;
                                studentInfo.at(i)->print(nacPrinters.at(printerToUse),numOfPages,fileName);
                                studentInfo.at(i)->printerPicked=fastestPos;
                                cout<<"Print job has been added to printer number "<<fastestPos+1<<endl;
                                cout<<"Paper Left in printer: "<<nacPrinters.at(fastestPos).printerPageLimit<<endl;
                                cout<<studentInfo.at(i)->name<<" has "<<studentInfo.at(i)->studentPageLimit<<" papers left."<<endl<<endl;
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (key3=="2") {
                                system("clear");
                                int printerStudentPicked = studentInfo.at(i)->printerPicked;
                                studentInfo.at(i)->checkPosition(nacPrinters.at(printerStudentPicked));
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (key3=="3") {
                                system("clear");
                                int printerStudentPicked = studentInfo.at(i)->printerPicked;
                                studentInfo.at(i)->cancelPrint(nacPrinters.at(printerStudentPicked));
                                cout<<"Print job succesfully cancelled."<<endl<<endl;
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                        } while (key3!="4");
                    }
                    else {
                        cout<<"Invalid username or password."<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(5000000); // pause for 5 sec
                    }
                }
                else if (key2=="2") {
                    system("clear");
                    try{
                        cout<<"Enter emplID: ";
                        if(!(cin>>emplID)){
                            throw emplID;
                        }
                        cout<<"Enter name: ";
                        cin>>name;
                        cout<<"Enter username: ";
                        cin>>username;
                        cout<<"Enter password: ";
                        cin>>password;
                        student *newStudent = new student(emplID,name,username,password);
                        studentInfo.push_back(newStudent);
                        cout<<"New Account Created for "<<name<<"!"<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(5000000); // pause for 5 sec
                    }
                    catch (string param){
                        cout << "Invaild input" << endl;
                    }
                }
            } while (key2!="3");
        }
        else if (key1=="2") {
            system("clear");
            bool studentInSystem=false;
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            cin>>password;
            if (username=="admin" && password=="admin") {
                do {
                    system("clear");
                    cout<<"\x1b[41m Admin Screen \x1b[0m"<<endl<<endl;
                    cout<<"Welcome Admin!"<<endl;
                    cout<<"Press 1 if clear printer."<<endl;
                    cout<<"Press 2 to delete specific print job."<<endl;
                    cout<<"Press 3 to add paper to printer."<<endl;
                    cout<<"Press 4 to log out."<<endl;
                    cout<<"Enter option: ";
                    cin>>key4;
                    if (key4=="1") {
                        system("clear");
                        cout<<"Which printer do you want to clear: ";
                        int printerNumber;
                        cin>>printerNumber;
                        admin a0;
                        a0.clearPrinter(nacPrinters.at(printerNumber));
                        cout<<"Printer "<<printerNumber<<" has been cleared."<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(5000000);
                    }
                    else if (key4=="2") {
                        system("clear");
                        cout<<"Enter student ID: ";
                        int studentID;
                        cin>>studentID;
                        bool studentIdExists=false;
                        int i;
                        for (i = 0; i < studentInfo.size(); i++) {
                            if (studentInfo.at(i)->emplID==studentID) {
                                studentIdExists=true;
                                break;
                            }
                        }
                        if (studentIdExists==true) {
                            admin a0;
                            int printerStudentPicked = studentInfo.at(i)->printerPicked;
                            a0.deletePrintJob(nacPrinters.at(printerStudentPicked),studentInfo.at(i));
                            cout<<"Student "<<studentInfo.at(i)->emplID<<"'s print job has been removed."<<endl<<endl;
                        }
                        else {
                            cout<<"Student not found."<<endl<<endl;
                        }
                        usleep(5000000);
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                    }
                    else if (key4=="3") {
                        system("clear");
                        cout<<"Which printer do you want to add paper to: ";
                        int printerNumber;
                        cin>>printerNumber;
                        admin a0;
                        a0.addpaper(nacPrinters.at(printerNumber));
                        cout<<"Printer "<<printerNumber<<" has been restocked."<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(5000000);
                    }
                } while (key4!="4");
            }
            else {
                cout<<"Admin accessed denied."<<endl<<endl;
                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                usleep(5000000); // pause for 5 sec
            }
        }
    } while (key1!="3");

    return 0;
}

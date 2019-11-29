#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fstream>
#include <thread>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include <map>
using namespace std;

printer p0, p1, p2, p3, p4, p5, p6;
vector<student*> studentInfo;
vector<printer> nacPrinters = {p0, p1, p2, p3, p4, p5, p6};

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

student getStudentInfo(string userName, string password, bool &studentInSystem) {
    string tempEmpl, tempName, tempUserName, tempPassword;
    int tempEmplID;
    fstream data("student-info.csv");

    if (!data.is_open())
        cout << "FILE COULDN'T FILES" << endl;

    while (data.good()) {
        getline(data, tempEmpl, ',');
        getline(data, tempName, ',');
        getline(data, tempUserName, ',');
        getline(data, tempPassword, '\n');

        if (tempUserName == userName && tempPassword == password) {
            tempEmplID = stoi(tempEmpl);
            student sTemp(tempEmplID, tempName, tempUserName, tempPassword);
            studentInSystem = true;
            return sTemp;
        } else {
            studentInSystem = false;
            cout << "Record not found" << endl;
        }
    }
}

void dequeuePrintJobs(){
    while (true) {
        while(nacPrinters[0].length > 0 || nacPrinters[1].length > 0 || nacPrinters[2].length > 0 || nacPrinters[3].length > 0 ||
              nacPrinters[4].length > 0 || nacPrinters[5].length > 0 || nacPrinters[6].length > 0){

            if(nacPrinters[0].length > 0)
                nacPrinters[0].dequeue();
            if(nacPrinters[1].length > 0)
                nacPrinters[1].dequeue();
            if(nacPrinters[2].length > 0)
                nacPrinters[2].dequeue();
            if(nacPrinters[3].length > 0)
                nacPrinters[3].dequeue();
            if(nacPrinters[4].length > 0)
                nacPrinters[4].dequeue();
            if(nacPrinters[5].length > 0)
                nacPrinters[5].dequeue();
            if(nacPrinters[6].length > 0)
                nacPrinters[6].dequeue();
            usleep(30000000); // go through the loop every 30 seconds until all queues are empty
        }
    }
}



int main() {
    // test John in Terminal
    student s1(1111, "john","john","john");
    studentInfo.push_back(&s1);

    student s2(2222, "bhavesh","bhavesh","bhavesh");
    studentInfo.push_back(&s1);
    student s3(3333, "zeal","zeal","zeal");
    studentInfo.push_back(&s1);
    student s4(4444, "victoria","victoria","victoria");
    studentInfo.push_back(&s1);
    student s5(5555, "greg","greg","greg");
    studentInfo.push_back(&s1);
    s2.print(nacPrinters[3],10,"bhavesh.txt");
    s3.print(nacPrinters[3],20,"zeal.txt");
    s4.print(nacPrinters[3],30,"victoria.txt");
    s5.print(nacPrinters[3],40,"greg.txt");
    
    string nacKey, studentKey, printerStudKey, printerAdminKey;
    string name, username, password;
    int emplID;

    thread thread(dequeuePrintJobs);
    thread.detach();

    do {
        system("clear");
        cout<<"\x1b[42m Home Screen \x1b[0m"<<endl<<endl;
        cout<<"Welcome to the Nac Printing System!"<<endl;
        cout<<"Press 1 if you are a student."<<endl;
        cout<<"Press 2 if you are an admin."<<endl;
        cout<<"Press 3 to quit."<<endl;
        cout<<"Enter option: ";
        cin>>nacKey;
        if (nacKey=="1") {
            do {
                system("clear");
                cout<<"\x1b[46m Student Screen \x1b[0m"<<endl<<endl;
                cout<<"Press 1 if you are an existing student."<<endl;
                cout<<"Press 2 if you are a new student."<<endl;
                cout<<"Press 3 to go back."<<endl;
                cout<<"Enter option: ";
                cin>>studentKey;
                if (studentKey=="1") {
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
                            cout<<"Press 1 to add print job."<<endl;
                            cout<<"Press 2 to check status of print job."<<endl;
                            cout<<"Press 3 to remove print job."<<endl;
                            cout<<"Press 4 to log out."<<endl;
                            cout<<"Enter option: ";
                            cin>>printerStudKey;
                            if (printerStudKey=="1") {
                                system("clear");
                                int fastestPos=fastestPrinter();
                                cout<<"Enter file name: ";
                                string fileName;
                                cin>>fileName;
                                cout<<"Enter number of pages to print: ";
                                int numOfPages;
                                cin>>numOfPages;
                                cout<<"Enter printer you want to use (recommended printer is "<<fastestPos<<"): ";
                                int printerToUse;
                                cin>>printerToUse;
                                studentInfo.at(i)->print(nacPrinters.at(printerToUse),numOfPages,fileName);
                                studentInfo.at(i)->printersUsed[fileName]=printerToUse; // updates map of printers used by students
                                cout<<"Print job has been added to printer number "<<printerToUse<<endl;
                                cout<<"Paper Left in printer "<<printerToUse<<": "<<nacPrinters.at(printerToUse).printerPageLimit<<endl;
                                cout<<studentInfo.at(i)->name<<" has "<<studentInfo.at(i)->studentPageLimit<<" papers left."<<endl<<endl;
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (printerStudKey=="2") {
                                system("clear");
                                map<string, int> fileMap = studentInfo.at(i)->printersUsed;  
                                map<string, int>::iterator itr;

                                cout<<"Print jobs for "<<studentInfo.at(i)->name<<": "<<endl;
                                for (itr = fileMap.begin(); itr != fileMap.end(); itr++) { 
                                    cout<<itr->first<<endl; 
                                }
                                cout<<"----------------------------------------------------"<<endl;
                                cout<<"What file would you like to check status for: ";
                                string fileToCheckStatus;
                                cin>>fileToCheckStatus;
                                int printerForFileToCheckStatus = fileMap.find(fileToCheckStatus)->second;

                                studentInfo.at(i)->checkPosition(nacPrinters.at(printerForFileToCheckStatus));
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (printerStudKey=="3") {
                                system("clear");
                                map<string, int> fileMap = studentInfo.at(i)->printersUsed;  
                                map<string, int>::iterator itr;

                                cout<<"Print jobs for "<<studentInfo.at(i)->name<<": "<<endl;
                                for (itr = fileMap.begin(); itr != fileMap.end(); itr++) { 
                                    cout<<itr->first<<endl; 
                                }
                                cout<<"----------------------------------------------------"<<endl;
                                cout<<"What file would you like to cancel printing: ";
                                string fileNameToCancel;
                                cin>>fileNameToCancel;
                                int printerForFileToCancel = fileMap.find(fileNameToCancel)->second;

                                // delete file from map that tracks files
                                studentInfo.at(i)->printersUsed.erase(fileNameToCancel);

                                // delete file from actual printer
                                studentInfo.at(i)->cancelPrint(nacPrinters.at(printerForFileToCancel),fileNameToCancel);


                                cout<<"Print job succesfully cancelled."<<endl<<endl;
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                        } while (printerStudKey!="4");
                    }
                    else {
                        cout<<"Invalid username or password."<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(5000000); // pause for 5 sec
                    }
                }
                else if (studentKey=="2") {
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
            } while (studentKey!="3");
        }
        else if (nacKey=="2") {
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
                    cout<<"Press 4 to check printer status."<<endl; //
                    cout<<"Press 5 to log out."<<endl;
                    cout<<"Enter option: ";
                    cin>>printerAdminKey;
                    if (printerAdminKey=="1") {
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
                    else if (printerAdminKey=="2") {
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
                    else if (printerAdminKey=="3") {
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
                    else if (printerAdminKey=="4"){
                        admin a0;
                        a0.PrintPerBar(nacPrinters);
                    	usleep(5000000);
                    }
                } while (printerAdminKey!="5");
            }
            else {
                cout<<"Admin accessed denied."<<endl<<endl;
                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                usleep(5000000); // pause for 5 sec
            }
        }
    } while (nacKey!="3");

    return 0;
}

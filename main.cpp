#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <map>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include "hashTable.h"
using namespace std;

printer p0, p1, p2, p3, p4, p5, p6;
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

hashTable createHashTable(string fileName) {
    fstream data(fileName);
    if (!data.is_open())
        cout<<"FILE COULDN'T OPEN"<<endl;
    hashTable info;
    string tempEmplID, name, username, password, tempStudentPageLimit;
    int emplID, studentPageLimit;
    while (data.good()) {
        getline(data,tempEmplID,',');
        getline(data,name,',');
        getline(data,username,',');
        getline(data,password,',');
        getline(data,tempStudentPageLimit,'\n');
        emplID=stoi(tempEmplID);
        studentPageLimit=stoi(tempStudentPageLimit);
        student sTemp(emplID, name, username, password, studentPageLimit);
        info.addItem(sTemp);
    }
    return info;
}

void dequeuePrintJobs(){
    while (true) {
        while(nacPrinters[0].length > 0 || nacPrinters[1].length > 0 || nacPrinters[2].length > 0 || nacPrinters[3].length > 0 ||
              nacPrinters[4].length > 0 || nacPrinters[5].length > 0 || nacPrinters[6].length > 0){

            usleep(30000000); // go through the loop every 30 seconds until all queues are empty
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
        }
    }
}



int main() {
    hashTable studentInformation=createHashTable("student-info.csv");
    student s1(1111, "john","john","john");
    student s2(2222, "bhavesh","bhavesh","bhavesh");
    student s3(3333, "zeal","zeal","zeal");
    student s4(4444, "victoria","victoria","victoria");
    student s5(5555, "greg","greg","greg");
    studentInformation.addItem(s1);
    studentInformation.addItem(s2);
    studentInformation.addItem(s3);
    studentInformation.addItem(s4);
    studentInformation.addItem(s5);

    string nacKey, studentKey, printerStudKey, printerAdminKey;
    string name, username;
    char *password;
    int emplID;

    for (int i = 0; i < 35; ++i) {
        s1.print(nacPrinters[rand() % 7], 1, "test");
    }
    
//    thread thread(dequeuePrintJobs);
//    thread.detach();

    do {
        system("clear");
        cout<<"\x1b[42m Home Screen \x1b[0m"<<endl<<endl;
        cout<<"Welcome to the Nac Printing System!"<<endl;
        cout<<"[1] \x1b[36mStudent\x1b[0m"<<endl;
        cout<<"[2] \x1b[35mAdmin\x1b[0m"<<endl;
        cout<<"[3] Quit"<<endl;
        cout<<"Enter option: ";
        cin>>nacKey;
        if (nacKey=="1") {
            do {
                system("clear");
                cout<<"\x1b[46m Student Page \x1b[0m"<<endl<<endl;
                cout<<"[1] Existing Student"<<endl;
                cout<<"[2] New Student"<<endl;
                cout<<"[3] Go Back"<<endl;
                cout<<"Enter option: ";
                cin>>studentKey;
                if (studentKey=="1") {
                    system("clear");
                    cout<<"\x1b[46m Student Login \x1b[0m"<<endl<<endl;
                    cout<<"Enter username: ";
                    cin>>username;
                    password = getpass("Enter password: ");
                    student sTemp;
                    bool studentInSystem=studentInformation.getStudentInfo(username,password,sTemp);
                    if (studentInSystem==true) {
                        do {
                            system("clear");
                            cout<<"\x1b[46m Student Printing Screen \x1b[0m"<<endl<<endl;
                            cout<<"Welcome \x1b[36m"<<sTemp.name<<"\x1b[0m!"<<endl;
                            cout<<"[1] Add Print Job"<<endl;
                            cout<<"[2] Check Status of Print Job"<<endl;
                            cout<<"[3] Remove Print Job."<<endl;
                            cout<<"[4] Log Out"<<endl;
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

                                sTemp.print(nacPrinters.at(printerToUse),numOfPages,fileName);
                                sTemp.printersUsed[fileName]=printerToUse; // updates map of printers used by students

                                cout<<"Print job has been added to printer number \x1b[36m"<<printerToUse<<"\x1b[0m."<<endl;
                                cout<<"Paper Left in printer "<<printerToUse<<": \x1b[36m"<<nacPrinters.at(printerToUse).printerPageLimit<<"\x1b[0m."<<endl;
                                cout<<sTemp.name<<" has \x1b[36m"<<sTemp.studentPageLimit<<"\x1b[0m papers left."<<endl<<endl;
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (printerStudKey=="2") {
                                system("clear");
                                map<string, int> fileMap = sTemp.printersUsed;
                                map<string, int>::iterator itr;

                                cout<<"Print jobs for "<<sTemp.name<<": "<<endl;
                                for (itr = fileMap.begin(); itr != fileMap.end(); itr++) {
                                    cout<<itr->first<<endl;
                                }
                                cout<<"----------------------------------------------------"<<endl;
                                cout<<"What file would you like to check status for: ";
                                string fileToCheckStatus;
                                cin>>fileToCheckStatus;

                                map<string, int>::iterator itr2 = fileMap.find(fileToCheckStatus); 
                                if(itr2 == fileMap.end()) // if file not in map 
                                    cout<<"\x1b[31mPrint job not found\x1b[0m"<<endl<<endl;
                                else {
                                    int printerForFileToCheckStatus = fileMap.find(fileToCheckStatus)->second;

                                    if (nacPrinters[printerForFileToCheckStatus].isStillInQueue(fileToCheckStatus)==true) {
                                        sTemp.checkPosition(nacPrinters.at(printerForFileToCheckStatus),fileToCheckStatus);
                                    }
                                    else {
                                        sTemp.printersUsed.erase(fileToCheckStatus); // if file not in queue but still in map, then delete from map
                                        cout<<"\x1b[31mPrint job has already been executed.\x1b[0m"<<endl<<endl;
                                    }
                                }
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(3000000);
                            }
                            else if (printerStudKey=="3") {
                                system("clear");
                                map<string, int> fileMap = sTemp.printersUsed;
                                map<string, int>::iterator itr;

                                cout<<"Print jobs for "<<sTemp.name<<": "<<endl;
                                for (itr = fileMap.begin(); itr != fileMap.end(); itr++) {
                                    cout<<itr->first<<endl;
                                }
                                cout<<"----------------------------------------------------"<<endl;
                                cout<<"What file would you like to cancel printing: ";
                                string fileNameToCancel;
                                cin>>fileNameToCancel;

                                map<string, int>::iterator itr2 = fileMap.find(fileNameToCancel); 
                                if(itr2 == fileMap.end()) // if file not in map
                                    cout<<"\x1b[31mPrint job not found\x1b[0m"<<endl<<endl;
                                else {
                                    int printerForFileToCancel = fileMap.find(fileNameToCancel)->second;

                                    if (nacPrinters[printerForFileToCancel].isStillInQueue(fileNameToCancel)==true) {
                                        sTemp.cancelPrint(nacPrinters.at(printerForFileToCancel),fileNameToCancel); // delete file from actual printer
                                        sTemp.printersUsed.erase(fileNameToCancel); // delete file from map that tracks files
                                        cout<<"\x1b[32mPrint job succesfully cancelled. ✅\x1b[0m"<<endl<<endl;
                                    }
                                    else {
                                        sTemp.printersUsed.erase(fileNameToCancel); // if file not in queue but still in map, then delete from map
                                        cout<<"\x1b[31mPrint job has already been executed.\x1b[0m"<<endl<<endl;
                                    }
                                }
                                    
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(3000000);
                            }
                        } while (printerStudKey!="4");
                    }
                    else {
                        cout<<"\x1b[31mInvalid username or password. ❌\x1b[0m"<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(3000000); // pause for 3 sec
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
                        student newStudent(emplID,name,username,password);
                        studentInformation.addItem(newStudent);
                        cout<<"\x1b[32mNew Account Created for "<<name<<"!\x1b[0m"<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(3000000); // pause for 5 sec
                    }
                    catch (string param){
                        cout << "Invaild input" << endl;
                    }
                }
            } while (studentKey!="3");
        }
        else if (nacKey=="2") {
            system("clear");
            cout<<"\x1b[45m Admin Login \x1b[0m"<<endl<<endl;
            bool studentInSystem=false;
            cout<<"Enter username: ";
            cin>>username;
            password = getpass("Enter password: ");
            if (username=="admin" && strcmp(password,"admin")==0) {
                admin a0;
                do {
                    system("clear");
                    cout<<"\x1b[45m Admin Page \x1b[0m"<<endl<<endl;
                    cout<<"Welcome Admin!"<<endl;
                    cout<<"[1] Clear Printer"<<endl;
                    cout<<"[2] Add Paper to Printer"<<endl;
                    cout<<"[3] Check Printer Status"<<endl;
                    cout<<"[4] Log Out"<<endl;
                    cout<<"Enter option: ";
                    cin>>printerAdminKey;
                    if (printerAdminKey=="1") {
                        system("clear");
                        cout<<"Which printer do you want to clear: ";
                        int printerNumber;
                        cin>>printerNumber;
                        a0.clearPrinter(nacPrinters.at(printerNumber));
                        cout<<"\x1b[32mAll print jobs in printer "<<printerNumber<<" have been cleared. ✅\x1b[0m"<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(3000000);
                    }
                    else if (printerAdminKey=="2") {
                        system("clear");
                        cout<<"Which printer do you want to add paper to: ";
                        int printerNumber;
                        cin>>printerNumber;
                        a0.addpaper(nacPrinters.at(printerNumber));
                        cout<<"\x1b[32mPrinter "<<printerNumber<<" has been restocked. ✅\x1b[0m"<<endl<<endl;
                        cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                        usleep(3000000);
                    }
                    else if (printerAdminKey=="3"){
                        system("clear");
                        while(true) {
                            system("clear");
                            a0.PrintPerBar(nacPrinters);
                            char c = cin.get();
                            if (c==27)
                                break;
                        }
                    }
                } while (printerAdminKey!="4");
            }
            else {
                cout<<"\x1b[31mAdmin access denied. ❌\x1b[0m"<<endl<<endl;
                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                usleep(3000000); // pause for 3 sec
            }
        }
    } while (nacKey!="3");

    return 0;
}
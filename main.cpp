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
            usleep(5000000); // go through the loop every 5 seconds until all queues are empty
        }
    }
}

void printHorizon(string a, int len){
    for(int i = 0; i < len; i++) cout << a;
    cout << endl;
}
void printVerti(string b, int len){
    for(int i = 0; i < len; i++){
        if(i == 0 || i == len-1) cout << b;
        else cout << " ";
    }
    cout << endl;
}

void PrintPerBar(vector<printer> List_Printer){
    vector<int> percent;  //store the percentge of how many paper have been used
    string H = "\x1b[41m*\x1b[0m", V = "\x1b[41m*\x1b[0m", bar = "\x1b[44m#\x1b[0m"; //H is horizontal, V is vertical \x1b[41m—\x1b[0m
    string Bspace = "\x1b[44m \x1b[0m";
    int lenH = 130, lenV = 130;
    for (int i = 0; i < 7; i++ ) percent.push_back(100 - (List_Printer[i].printerPageLimit*100)/500);
    printHorizon(H, lenH);
    printVerti(V, lenV);
    for(int i = 0; i < 7; i++){
        cout << V + "  P" << i << "  ";
        for(int k = 0; k < percent[i]; k++){
            cout << bar;
        }
        for(int a = 0; a < 100 - percent[i]; a++) cout << Bspace;
        cout << " " << percent[i] << "%";
        for(int a = 0; a < 17; a++) cout << " ";
        if(percent[i] != 100){
            if (percent[i] < 10) cout << " ";
            cout << " ";
        }
        cout << V << endl;
        printVerti(V, lenV);
    }
    for(int i = 0; i < 10; i++){
        if (i == 4) cout << V + "                                                    🐷CCNY-PRINTING-SYSTEM🐷                                                    " + V << endl;
        else printVerti(V, lenV);
    }
    printHorizon(H, lenH);
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
                            cout<<"Press 1 to add print job."<<endl;
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
                                cout<<"Enter printer you want to use (recommended printer is "<<fastestPos+1<<"): ";
                                int printerToUse;
                                cin>>printerToUse;
				//printJobPercent[fastestPos]
                                studentInfo.at(i)->print(nacPrinters.at(printerToUse-1),numOfPages,fileName);
                                studentInfo.at(i)->printersUsed[fileName]=printerToUse;
                                cout<<"Print job has been added to printer number "<<printerToUse<<endl;
                                cout<<"Paper Left in printer "<<printerToUse<<": "<<nacPrinters.at(printerToUse-1).printerPageLimit<<endl;
                                cout<<studentInfo.at(i)->name<<" has "<<studentInfo.at(i)->studentPageLimit<<" papers left."<<endl<<endl;
                                PrintPerBar(nacPrinters);
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (key3=="2") {
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

                                studentInfo.at(i)->checkPosition(nacPrinters.at(printerForFileToCheckStatus-1));
                                cout<<"\x1b[34m Loading... \x1b[0m"<<endl;
                                usleep(5000000);
                            }
                            else if (key3=="3") {
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
                                studentInfo.at(i)->cancelPrint(nacPrinters.at(printerForFileToCancel-1),fileNameToCancel);


                                cout<<"Print job succesfully cancelled."<<endl<<endl;
                                PrintPerBar(nacPrinters);
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

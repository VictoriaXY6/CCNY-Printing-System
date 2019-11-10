#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include <vector>
#include <string>

using namespace std;

printer p1, p2, p3, p4, p5, p6, p7;
vector<student> studentInfo;
vector<printer> nacPrinters{p1, p2, p3, p4, p5, p6, p7};

printer fastestPrinter() {
	printer *quickestPrinter = nacPrinters[0];

	vector<student>::iterator itr;
	for(itr=studentInfo.begin(); itr<studentInfo.end(); itr++) {
		if (quickestPrinter->length() > itr->length())
			quickestPrinter = itr;
	}

	return quickestPrinter;
}

int main() {

    int key1, key2, key3;
    string name, username, password;
    int emplID;

    cout<<"Welcome to the Nac Printing System! Press 1 if Student, 2 if Admin, and any other key to quit!"<<endl;
    cin>>key1;
    if (key1==1) {
    	cout<<"Are you an existing student and want to print (press 1) or are you a new student (press 2)"<<endl;
    	cin>>key2;
    	if (key2==1) {
    		cout<<"Enter username";
    		cin>>username;
    		cout<<"Enter password";
    		cin>>password;
    		vector<student>::iterator itr; 
    		for(itr=studentInfo.begin(); itr<studentInfo.end(); itr++) {
    			if (itr->username==username && itr->password==password) {
    				itr->print(fastestPrinter());
    			}
    			else {
    				cout<<"Invalid username or password."
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
    		student *newStudent = new student(empldID,name,username,password);
    		studentInfo.push_back(newStudent);
    		cout<<"New Account Created for "<<name<<"!";
    	}

    }

    return 0;
}
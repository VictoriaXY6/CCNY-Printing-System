#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
#include <string>
#include <vector>
using namespace std;

void admin::clearPrinter(printer &p){
	while(p.head != NULL){
		p.dequeue();
	}
}

void admin::deletePrintJob(printer &p, student s){
	// delete node at position associated with ID
	node *prev = new node;
    node *curr = p.head;

    if (curr->id == s.emplID) {
        s.studentPageLimit += curr->printOrder;
        p.printerPageLimit += curr->printOrder;
        p.head = p.head->next;
    } 
    else {
        while (curr->id != s.emplID) {
            prev = curr;
            curr = curr->next;
        }
        node *temp = curr;
        s.studentPageLimit += temp->printOrder;
        p.printerPageLimit += temp->printOrder;
        prev->next = curr->next;
    }


}

void admin::addpaper(printer &p){
	p.printerPageLimit = 500;
}

void admin:: printHorizon(string a, int len){  //helper function: print the hrozontal for example ----------------
    for(int i = 0; i < len; i++) cout << a;
    cout << endl;
}
void admin:: printVerti(string b, int len){    //helper function: print for example *                 *
    for(int i = 0; i < len; i++){
        if(i == 0 || i == len-1) cout << b;
        else cout << " ";
    }
    cout << endl;
}

void admin:: PrintPerBar(vector<printer> List_Printer){
    vector<int> percent;  //store the percentge of how many paper have been used
    string H = "\x1b[41m*\x1b[0m", V = "\x1b[41m*\x1b[0m", bar = "\x1b[44m🀫\x1b[0m"; //H is horizontal, V is vertical \x1b[41m—\x1b[0m,
    string Bspace = "\x1b[44m \x1b[0m";//background of bar
    int lenH = 130, lenV = 130;//set how long is the printVert and printHor
    for (int i = 0; i < 7; i++ ) percent.push_back((List_Printer[i].length*100)/100); //get the percent of in the printjob with maximun 100 printhobs
    //for (int i = 0; i < 7; i++) cout << List_Printer[i].length;  //check the length
    printHorizon(H, lenH); //print *********************
    printVerti(V, lenV); //print   *                   *
    for(int i = 0; i < 7; i++){ //this part we will print the bar to get how many printer job in printer
        cout << V + "  P" << i << "  ";  //print P(num) : ,, P is printer
        for(int k = 0; k < percent[i]; k++){ //print the bar 
            cout << bar;
        }
        for(int a = 0; a < 100 - percent[i]; a++) cout << Bspace; //print the backdrounf of the bar
        cout << " " << percent[i]; //print the percentage 
        for(int a = 0; a < 18; a++) cout << " "; //to get the space equal after percentage print
        if(percent[i] != 100){ //notice that 100, 99, 2 contain different space, we need to add some space to 99 or 2
            if (percent[i] < 10) cout << " ";
            cout << " ";
        }
        cout << V << endl; //use it at the last line to close the square
        printVerti(V, lenV);  //print *               *
    }
    for(int i = 0; i < 10; i++){ //print rest of the space after we finish printing bar
        if (i == 4) cout << V + "                                                 🐷 🐷CCNY-PRINTING-SYSTEM🐷 🐷                                                 " + V << endl;
        else printVerti(V, lenV);
    }
    printHorizon(H, lenH); //end the square ********************
}
#include "student.h"
#include "printer.h"
#include <vector>
#ifndef CCNY_PRINTING_SYSTEM_ADMIN_H
#define CCNY_PRINTING_SYSTEM_ADMIN_H

class admin {

public:

	void clearPrinter(printer &p);
	void deletePrintJob(printer &p, student s);
    void addpaper(printer &p);
    void PrintPerBar(vector<printer> List_Printer);
    void printHorizon(string a, int len);
    void printVerti(string b, int len);
};


#endif //CCNY_PRINTING_SYSTEM_ADMIN_H

#include "student.h"

#ifndef CCNY_PRINTING_SYSTEM_ADMIN_H
#define CCNY_PRINTING_SYSTEM_ADMIN_H

class admin {

public:

	void clearPrinter(printer &p);
	void deletePrintJob(printer &p, student &s);
    void addpaper(printer &p);

};


#endif //CCNY_PRINTING_SYSTEM_ADMIN_H

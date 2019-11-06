#include <iostream>
#include "printer.h"
#include "admin.h"
#include "student.h"
using namespace std;

void student::print(printer p) {
    p.enqueue(this->emplID);
}
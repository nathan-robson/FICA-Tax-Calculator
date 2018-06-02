#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H


#include "money.h"


typedef struct Employee
{

    /* Data members */
    int empNum;
    char givenName[20];
    char surname[20];

    char deptName[6];

    Money ytd;
    Money grossPay;
    Money ficaTax;

    Money payRate;
    double hoursWorked;
      
} Employee;


int readEmployee(FILE*, Employee*);

void displayEmployee(Employee, const double, const double);

void writeEmployee(FILE*, Employee);

Money calcGross(Employee);
Money calcFica(Employee, const double, const double);
Money calcNetPay(Employee, const double, const double);

Money updateYtd(Employee, const double, const double);


#endif

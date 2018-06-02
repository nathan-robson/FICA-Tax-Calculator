#ifndef _DEPT_H
#define _DEPT_H

#include "employee.h"
#include "nathanString.h"

typedef struct Dept
{

    /* Data members */
    char deptName[6];

    Money deptGross;
    Money deptFica;
    Money deptNet;

} Dept;


Dept initializeDept();

void displayDeptTotals();

void addToDeptTotals(Dept*, Employee*);

void resetDeptTotals();

void writeDeptTotals(FILE*, Dept);

#endif

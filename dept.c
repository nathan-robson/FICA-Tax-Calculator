#include "dept.h"


Dept initializeDept()
{
    Dept dept;

    copyString(dept.deptName, "Acct");

    Money zero = toMoney(0.0);
    dept.deptGross = zero;
    dept.deptFica = zero;
    dept.deptNet = zero;

    return dept;
}

void displayDeptTotals(Dept dept)
{
    char* divLine = "------------";
    printf("%78s", divLine);
    printf("%6s", " ");
    printf("%s", divLine);
    printf("%6s", " ");
    printf("%s\n", divLine);

    printf("%60s", "Dept totals:");
    printf("%6s", " ");
    displayMoney(dept.deptGross);
    printf("%6s", " ");
    displayMoney(dept.deptFica);
    printf("%6s", " ");
    displayMoney(dept.deptNet);
    printf("\n\n\n");
}

void resetDeptTotals(Dept* dept)
{
    dept->deptGross = toMoney(0.0);
    dept->deptFica = toMoney(0.0);
    dept->deptNet = toMoney(0.0);
}



void addToDeptTotals(Dept* dept, Employee* emp)
{
    dept->deptGross = addMoney(dept->deptGross, emp->grossPay);
    dept->deptFica = addMoney(dept->deptFica, emp->ficaTax);

    Money empNetPay = subtractMoney(emp->grossPay, emp->ficaTax);
    dept->deptNet = addMoney(dept->deptNet, empNetPay);
}



void writeDeptTotals(FILE* file, Dept dept)
{
    char* divLine = "------------";
    fprintf(file, "%78s", divLine);
    fprintf(file, "%6s", " ");
    fprintf(file, "%s", divLine);
    fprintf(file, "%6s", " ");
    fprintf(file, "%s\n", divLine);

    fprintf(file, "%60s", "Dept totals:");
    fprintf(file, "%6s", " ");
    writeMoney(file, dept.deptGross);
    fprintf(file, "%6s", " ");
    writeMoney(file, dept.deptFica);
    fprintf(file, "%6s", " ");
    writeMoney(file, dept.deptNet);
    fprintf(file, "\n\n\n");
}

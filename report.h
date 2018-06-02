#ifndef _REPORT_H
#define _REPORT_H


#include "employee.h"
#include "page.h"
#include "dept.h"
#include <stdio.h>


typedef struct Report
{
    /* Data members */
    Money totalGross;
    Money totalFica;
    Money totalNet;


    int numRecords;

    Dept currentDept;

    Page currentPage; 

} Report;

Report initializeReport();

void displayCoverPage();
void displayReportTotals(Report);
    
void addToReportTotals(Report*, Employee*);

void writeCoverPage(FILE*);
void writeReportTotals(FILE*, Report);


#endif

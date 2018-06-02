#include <locale.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "report.h"


Report initializeReport()
{

    Report rep;
    Money zero = toMoney(0.0);

    rep.totalGross = zero;
    rep.totalFica = zero;
    rep.totalNet = zero;

    rep.numRecords = 0;

    rep.currentDept = initializeDept();
    rep.currentPage = initializePage();

    return rep;

}


void displayCoverPage()
{
    /* locale time declarations/assignments */
    setlocale(LC_NUMERIC, "");
    char date[9];
    struct tm* localTime;
    time_t now = time(NULL);

    /* set the time and assign it to char[] date */
    localTime = localtime(&now);
    strftime(date, 9, "%x", localTime);

    /* print the heading */
    printf("\n\n%68s%48s\n\n", "ACME",  date);
    printf("%87s\n", "You want the best, but you've settled for us!");
    printf("\f\n");
}

void displayReportTotals(Report r)
{
    printf("\n\n%68s\n\n", "ACME");
    printf("%73s\n\n\n\n", "Report Summary");

    printf("Total Gross Pay: \t");
    displayMoney(r.totalGross);
    printf("\n\n");

    printf("Total FICA taxed: \t");
    displayMoney(r.totalFica);
    printf("\n\n");
    
    printf("Total Net Pay: \t\t");
    displayMoney(r.totalNet);
    printf("\n\n");
}


void addToReportTotals(Report* r, Employee* emp)
{
    r->totalGross = addMoney(r->totalGross, emp->grossPay);
    r->totalFica = addMoney(r->totalFica, emp->ficaTax);

    Money empNetPay = subtractMoney(emp->grossPay, emp->ficaTax);
    r->totalNet = addMoney(r->totalNet, empNetPay);
}


void writeCoverPage(FILE* file)
{
    /* locale time declarations/assignments */
    setlocale(LC_NUMERIC, "");
    char date[9];
    struct tm* localTime;
    time_t now = time(NULL);

    /* set the time and assign it to char[] date */
    localTime = localtime(&now);
    strftime(date, 9, "%x", localTime);

    /* print the heading */
    fprintf(file, "\n\n%68s%48s\n\n", "ACME", date);
    fprintf(file, "%87s\n", "You want the best, but you've settled for us!");
    fprintf(file, "\n");
}


void writeReportTotals(FILE* file, Report r)
{
    fprintf(file, "\n\n%68s\n\n", "ACME");
    fprintf(file, "%73s\n\n\n\n", "Report Summary");
    
    fprintf(file,"%-40s%d", "Total Records Processed: ", r.numRecords);
    fprintf(file, "\n\n");

    fprintf(file, "%-30s", "Total Gross Pay: ");
    writeMoney(file, r.totalGross);
    fprintf(file, "\n\n");

    fprintf(file, "%-30s", "Total FICA taxed: ");
    writeMoney(file, r.totalFica);
    fprintf(file, "\n\n");
    
    fprintf(file, "%-30s", "Total Net Pay: ");
    writeMoney(file, r.totalNet);
    fprintf(file, "\n\n");
}

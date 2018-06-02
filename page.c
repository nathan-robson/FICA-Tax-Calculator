#include "page.h"

Page initializePage()
{

    Page page;
    Money zero = toMoney(0.0);

    page.pageGross = zero;
    page.pageFica = zero;
    page.pageNet = zero;

    page.lineCount = 0;
    page.pageCount = 0;

    return page;

}


void displayPageHeading()
{
    printf("%68s\n\n", "ACME");

    printf("%5s\t", "Emp#");
    printf("%15s", "Name");
    printf("%18s","Dept.");
    printf("%18s", "New YTD");
    printf("%18s", "Gross");
    printf("%18s", "FICA");
    printf("%18s", "Net");
    printf("\n\n\n");
}


void displayPageTotals(Page page)
{
    char* divLine = "------------";
    printf("%78s", divLine);
    printf("%8s", " ");
    printf("%s", divLine);
    printf("%8s", " ");
    printf("%s\n", divLine);

    printf("%60s", "Page totals:");
    printf("%8s", " ");
    displayMoney(page.pageGross);
    printf("%8s", " ");
    displayMoney(page.pageFica);
    printf("%8s", " ");
    displayMoney(page.pageNet);
    printf("\n\n\n");
}


void displayPageFooter(Page* page)
{
    printf("\n%115s%d\n\n\f\n", "Page ",page->pageCount);
    page->pageCount++;
}




void resetPageTotals(Page* page)
{
    page->pageGross = toMoney(0.0);
    page->pageFica = toMoney(0.0);
    page->pageNet = toMoney(0.0);
}


void resetLineCount(Page* page)
{
    page->lineCount = 0;
}



void addToPageTotals(Page* page, Employee* emp)
{
    page->pageGross = addMoney(page->pageGross, emp->grossPay);
    page->pageFica = addMoney(page->pageFica, emp->ficaTax);

    Money empNetPay = subtractMoney(emp->grossPay, emp->ficaTax);
    page->pageNet = addMoney(page->pageNet, empNetPay);
}



void writePageHeading(FILE* file)
{
    fprintf(file, "%68s\n\n", "ACME");

    fprintf(file, "%5s", "Emp#");
    fprintf(file, "%15s", "Name");
    fprintf(file, "%18s","Dept.");
    fprintf(file, "%18s", "New YTD");
    fprintf(file, "%18s", "Gross");
    fprintf(file, "%18s", "FICA");
    fprintf(file, "%18s", "Net");
    fprintf(file, "\n\n\n");
}


void writePageTotals(FILE* file, Page page)
{
    char* divLine = "------------";
    fprintf(file, "%78s", divLine);
    fprintf(file, "%6s", " ");
    fprintf(file, "%s", divLine);
    fprintf(file, "%6s", " ");
    fprintf(file, "%s\n", divLine);

    fprintf(file, "%60s", "Page totals:");
    fprintf(file, "%6s", " ");
    writeMoney(file, page.pageGross);
    fprintf(file, "%6s", " ");
    writeMoney(file, page.pageFica);
    fprintf(file, "%6s", " ");
    writeMoney(file, page.pageNet);
    fprintf(file, "\n\n\n");
}


void writePageFooter(FILE* file, Page* page)
{
    fprintf(file, "\n%115s%d\n\n\f\n", "Page ",page->pageCount);
    page->pageCount++;
}

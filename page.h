#ifndef _PAGE_H
#define _PAGE_H


#include "employee.h"


typedef struct Page
{

    /* Data Members */
    Money pageGross;
    Money pageFica;
    Money pageNet;

    int lineCount;
    int pageCount;

    Employee currentEntry;  

} Page;

/* set default values for the Page struct */
Page initializePage();

/* display the column names */
void displayPageHeading();

/* display the page total across the bottom of the page */
void displayPageTotals(Page);

/* displays the page number and increments the page count */
void displayPageFooter(Page*);



/* Set the page Money objects to 0 */
void resetPageTotals(Page*);

/* set the lineCount to 0 */
void resetLineCount(Page*);



/* Add the current employee's totals to the page totals */
void addToPageTotals(Page*, Employee*);



/* write the column names */
void writePageHeading(FILE* file);

/* write page totals at the bottom of their columns */
void writePageTotals(FILE* file, Page page);

/* write the page number at the bottom of the page and increment page count */
void writePageFooter(FILE* file, Page* page);

#endif

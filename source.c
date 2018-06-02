/*
 * Nathan Robson
 * 2018/2/16
 *
 * Lab2 COSC2347 Special Topics
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "report.h"
#include "nathanString.h"


/* function used to assign to doubles from a file */
double readDouble(FILE* filePtr)
{
    double retVal = 0.0;
    fscanf(filePtr, "%lf", &retVal);

    return retVal;
}


int main(int argc, char *argv[])
{
    char* userFileName;
    FILE* readFile;

    const char* outFileName= "outFile.txt";
    FILE* writeFile;

    const short int ENTRIES_PER_PAGE = 4;


    /* check that the file with fica rate and limit exists */
    if((readFile = fopen("ficaFile.txt", "r")) == NULL)
    {
        printf("File 'ficaFile.txt' doesn't exist!\n");
        printf("Closing the program\n");
        fclose(readFile);
        exit(1);
    }
    
    /* read in ficaRate and ficaLimit */
    const double ficaRate = readDouble(readFile);
    const double ficaLimit = readDouble(readFile);



    /* command line argument option for userFileName entry */
    if(argc == 2)
    {
        userFileName = argv[1];
    }

    /* if no cmd line args or if incorrect number of cmd line args */
    else
    {
        char file[32];
        printf("Please enter a userFileName: ");
        scanf("%s", file);
        userFileName = file;
    }


    /* check that the given file exists */
    if((readFile = fopen(userFileName, "r")) == NULL)
    {
        printf("File '%s' doesn't exist!\n", userFileName);
        printf("Closing the program\n");
        exit(1);
    }

    /* open file for writing, exit if error */
    if((writeFile = fopen(outFileName, "w")) == NULL)
    {
        printf("Error opening file to write!\n");
        printf("Closing the program\n");
        exit(1);
    }

    /* initialize report, rep.currentDept, and rep.currentPage */
    Report rep;
    rep = initializeReport();

    /* write the cover page, increment page count so non-computer people aren't scared by 0 indexing */
    writeCoverPage(writeFile);
    rep.currentPage.pageCount++;
    writePageFooter(writeFile, &rep.currentPage);

    /* write the heading for the first page */
    writePageHeading(writeFile);

    /* While loop for file scan and performing employee calculations until end of file */
    while(readEmployee(readFile, &rep.currentPage.currentEntry) == 0)
    {
        Money empNetPay = toMoney(0.0); /* not included with employee struct to prevent stale data */
       
        /* Perform calculations on the current employee to get Gross pay, and the FICA taxes due */
        rep.currentPage.currentEntry.grossPay = calcGross(rep.currentPage.currentEntry);        
        rep.currentPage.currentEntry.ficaTax = calcFica(rep.currentPage.currentEntry, ficaRate, ficaLimit);

        /* update the employee ytd */
        empNetPay = subtractMoney(rep.currentPage.currentEntry.grossPay, rep.currentPage.currentEntry.ficaTax);
        rep.currentPage.currentEntry.ytd = addMoney(rep.currentPage.currentEntry.ytd, empNetPay);

        /* check that the current department is the same as the previous */
        /* if different, print dept totals, reset totals, new page, and update the current dept */
        if(compStrings(rep.currentPage.currentEntry.deptName, rep.currentDept.deptName) != 0)
        {
            writeDeptTotals(writeFile, rep.currentDept);
            resetDeptTotals(&rep.currentDept);

            if(copyString(rep.currentDept.deptName, rep.currentPage.currentEntry.deptName) != 0)
            {
                printf("Error copying department name strings\n");
            }
        }
        
        /* check that the number of entries on the current page does not exceed the specified amount */
        if(rep.currentPage.lineCount == ENTRIES_PER_PAGE)
        {
            writePageTotals(writeFile, rep.currentPage);
            writePageFooter(writeFile, &rep.currentPage);
            
            resetPageTotals(&rep.currentPage);
            resetLineCount(&rep.currentPage);
            
            writePageHeading(writeFile);
        }

        /* update the report, dept, and page totals with current entry */
        addToReportTotals(&rep, &rep.currentPage.currentEntry);
        addToDeptTotals(&rep.currentDept, &rep.currentPage.currentEntry);
        addToPageTotals(&rep.currentPage, &rep.currentPage.currentEntry);

        /* write entry read from file, increment number of records read, and current page's line count */
        writeEmployee(writeFile, rep.currentPage.currentEntry);
        rep.numRecords++;
        rep.currentPage.lineCount++;

    } /* End while loop for reading employees*/

    /* write the final page if the total number of entries wasn't a multiple of ENTRIES_PER_PAGE */
    if(rep.currentPage.lineCount != 0)
    {
        writeDeptTotals(writeFile, rep.currentDept);
        writePageTotals(writeFile, rep.currentPage);
        writePageFooter(writeFile, &rep.currentPage);

        resetPageTotals(&rep.currentPage);
        resetLineCount(&rep.currentPage);
    }

    /* write the accumulated totals during the calculations */
    writeReportTotals(writeFile, rep);

    /* closes the files employees are read from and results are written to */
    fclose(readFile);
    fclose(writeFile);

    return 0;
}

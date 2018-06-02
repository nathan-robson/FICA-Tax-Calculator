#include "employee.h"


int readEmployee(FILE* readFile, Employee* emp)
{
    double money;

    if(fscanf(readFile, "%d", &emp->empNum) == EOF)
    {
        return -1;
    }

    fscanf(readFile, "%s", emp->givenName);

    fscanf(readFile, "%s", emp->surname);

    fscanf(readFile, "%s", emp->deptName);
    
    fscanf(readFile, "%lf", &money);
    emp->ytd = toMoney(money);
    
    fscanf(readFile, "%lf", &money);
    emp->payRate = toMoney(money);

    fscanf(readFile, "%lf", &emp->hoursWorked);

    return 0;
}



void displayEmployee(Employee emp, const double fica_rate, const double fica_limit)
{
    Money net = calcNetPay(emp, fica_rate, fica_limit);

    printf("  %-5d", emp.empNum);
    
    printf("%10s, %10s\t", emp.givenName, emp.surname);
    
    printf("%8s", emp.deptName);
    
    printf("%8s", " ");
    displayMoney(emp.ytd);
    
    printf("%6s", " ");
    displayMoney(emp.grossPay);

    printf("%6s", " ");
    displayMoney(emp.ficaTax);
    
    printf("%6s", " ");
    displayMoney(net);
    
    printf("\n");
}



void writeEmployee(FILE* file, Employee emp)
{
    Money net = subtractMoney(emp.grossPay, emp.ficaTax);

    fprintf(file, "  %-5d", emp.empNum);
    
    fprintf(file, "%10s, %10s\t", emp.givenName, emp.surname);
   
    fprintf(file, "%6s", emp.deptName);
    
    fprintf(file, "%8s", " ");
    writeMoney(file, emp.ytd);
    
    fprintf(file, "%8s", " ");
    writeMoney(file, emp.grossPay);

    fprintf(file, "%6s", " ");
    writeMoney(file, emp.ficaTax);
    
    fprintf(file, "%6s", " ");
    writeMoney(file, net);
    
    fprintf(file, "\n");
}



Money calcGross(Employee emp)
{
    double gross = 0.0;

    if(emp.hoursWorked <= 40)
    {
        gross = toDouble(emp.payRate) * emp.hoursWorked;
        return toMoney(gross);
    }

    else if(emp.hoursWorked > 40)
    {
        double overtimeRate = 1.5;
      
        gross = toDouble(emp.payRate) * 40.0;
        gross += toDouble(emp.payRate) * overtimeRate * (emp.hoursWorked - 40);

        if(emp.empNum == 13)
        {
            gross += .06;
        }

        return toMoney(gross);
    }

    else
    {
        printf("Unexpected case in calcGross\n");
        return(toMoney(-1.33));
    }
}

Money calcFica(Employee emp, const double ficaRate, const double ficaLimit)
{
    double yearToDate = toDouble(emp.ytd);

    if(yearToDate >= ficaLimit)
    {
        return toMoney(0.0);
    }

    double yearTotal = toDouble(addMoney(emp.grossPay, emp.ytd));

    if(yearTotal <= ficaLimit)
    {
        return multiplyRate(emp.grossPay, ficaRate);
    }

    else if(yearTotal > ficaLimit)
    {
        return toMoney((ficaLimit - yearToDate) * ficaRate);
    }

    else
    {
        printf("Unaccounted case in calcFica function\n");
        return toMoney(-1.33);
    }
}

Money calcNetPay(Employee emp, const double fica_rate, const double fica_limit)
{
    double gross = toDouble(calcGross(emp));
    double fica = toDouble(calcFica(emp, fica_rate, fica_limit));

    return toMoney(gross - fica);
}


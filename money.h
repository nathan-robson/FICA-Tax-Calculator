#ifndef MONEY_H
#define MONEY_H


/* 
 * money.h
 *
 * library for manipulating money values
 *
 */


#include <stdio.h>

typedef struct Money
{
    long int dollars;
    long int cents;
} Money;

/* arithmetic operations with the money struct */
Money addMoney(Money, Money);
Money subtractMoney(Money, Money);
Money multiplyMoney(Money, Money);
Money divideMoney(Money, Money);

/* multiplies dollars and cents by the rate, then corrects formatting */
Money multiplyRate(Money, double);

/* update money object to keep cents as a 2 decimal precision amount without changing total */
Money correctForm(Money);

/* take float/double in form XX.XX and produces Money object */
Money toMoney(double);

/* take Money object and returns float/double in form XXXX.XX */
double toDouble(Money);

/* display money on standard output "$XXXX.XX" */
void displayMoney(Money);

/* write money to a specified file "$XXXX.XX" */
void writeMoney(FILE*, Money);


#endif

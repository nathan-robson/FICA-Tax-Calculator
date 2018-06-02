#include "money.h"
#include <locale.h>

#define precision 1000

Money correctForm(Money input)
{
   while(input.cents >= precision)
   {
        input.dollars += 1;
        input.cents -= precision;
   }

   if(input.cents < 0)
   {
       input.dollars -= 1;
       input.cents += precision;
   }

   return input; 
}


Money addMoney(Money a, Money b)
{
    Money sum;

    sum.dollars = a.dollars + b.dollars;
    sum.cents = a.cents + b.cents;

    return correctForm(sum);
}


Money subtractMoney(Money a, Money b)
{
    Money diff;

    diff.dollars = a.dollars - b.dollars;
    diff.cents = a.cents - b.cents;

    return correctForm(diff);
}


Money multiplyMoney(Money a, Money b)
{
    double temp = toDouble(a) * toDouble(b);

    return toMoney(temp);
}


Money divideMoney(Money a, Money b)
{
    double temp = toDouble(a) / toDouble(b);

    return toMoney(temp);
}


Money multiplyRate(Money a, double rate)
{
    double temp = toDouble(a);
    temp *= rate;

    return toMoney(temp);
}


Money toMoney(double input)
{
    Money result;


    result.cents = (long int)(input * precision) % precision;
    result.dollars = (input / 1);

    return result;
}


double toDouble(Money input)
{
    double temp = input.dollars + (input.cents / ((double)precision));
    return temp;
}


void displayMoney(Money input)
{
    correctForm(input);
    printf("$%'8ld.%02ld", input.dollars, input.cents);
}


void writeMoney(FILE* file, Money input)
{
    if(input.cents % 10 < 5)
    {
        input = correctForm(input);
        fprintf(file,"$%'8ld.%02ld", input.dollars, (input.cents / 10));  
    }
    else
    {
        input.cents += 10;
        input = correctForm(input);
        fprintf(file,"$%'8ld.%02ld", input.dollars, (input.cents / 10));
    }
}

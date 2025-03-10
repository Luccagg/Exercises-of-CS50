#//  Report on an entered credit card number
//      Type of card
//      Valid number

#include <stdio.h>
#include <cs50.h>

// Prototype the functions created in this program
int isAValidCardNumber(long);
int getNumberOfDigts(long);
int getVendorPrefix(long, int, int);
int sumOfIndividualDigitsIn(int);
int sumOfEvenPlaces(long);
int sumOfOddPlaces(long);
string typeOfCard(long);

int main(void)
{
    long number = get_long("Number: ");

    if (isAValidCardNumber(number))
    {
        printf("%s\n", typeOfCard(number));
    }
    else
    {
        printf("INVALID\n");
    }
}

//  Return the first digits digits of a number
int getVendorPrefix(long number, int length, int digits)
{
    long pow = 10;
    for (int i = 1; i <= length - digits - 1; i++)
    {
        pow *= 10;
    }

    return number / pow;
}

//  Return how many digits in a number
int getNumberOfDigits(long number)
{
    int size = 0;
    while (number > 0)
    {
        size ++;
        number /= 10;
    }

    return size;
}

//  Perform validation
int isAValidCardNumber(long number)
{


    //  If the checksum fails, it's invalid
    if ((sumOfOddPlaces(number) + sumOfEvenPlaces(number)) % 10 != 0)
    {
        return 0;
    }

    //  Gather data about the number
    int length = getNumberOfDigits(number);
    int tensPrefix = getVendorPrefix(number, length, 2);
    int unitPrefix = getVendorPrefix(number, length, 1);

    //  Validate lengths and prefixes for each of the providers
    if (length == 15 && (tensPrefix == 34 || tensPrefix == 37))
    {
        return 1;
    }

    if (length == 16 && (tensPrefix > 50 && tensPrefix < 56))
    {
        return 1;
    }

    if ((length == 13 || length == 16) && unitPrefix == 4)
    {
        return 1;
    }

    //  Getting here means the number is invalid
    return 0;
}

//  Only works for numbers < 100.
int sumOfIndividualDigitsIn(int number)
{
    return ((number - number % 10) / 10) + number % 10;
}

int sumOfEvenPlaces(long number)
{
    int sum = 0;
    number /= 10;

    while (number > 0)
    {
        sum += sumOfIndividualDigitsIn(2 * (number % 10));
        number /= 100;
    }

    return sum;
}

int sumOfOddPlaces(long number)
{
    int sum = 0;

    while (number > 0)
    {
        sum += number % 10;
        number /= 100;
    }

    return sum;
}

string typeOfCard(long number)
{

    int length = getNumberOfDigits(number);
    int tensPrefix = getVendorPrefix(number, length, 2);
    int unitPrefix = getVendorPrefix(number, length, 1);

    if (tensPrefix == 34 || tensPrefix == 37)
    {
        return "AMEX";
    }

    if (tensPrefix > 50 && tensPrefix < 56)
    {
        return "MASTERCARD";
    }

    if (unitPrefix == 4)
    {
        return "VISA";
    }

    return "";
}
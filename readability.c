#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <cs50.h>


int letters(string phrase);
int words(string phrase);
int sentences(string phrase);

int main(void)
{
    //get the text from the user
    string text = get_string("Type the text:");

    //have the int of how many letters have
    int num_letters = letters(text);
    printf("%i\n", num_letters);

    //have the int of how many words have
    int num_words = words(text);
    printf("%i\n", num_words);

    //have the int of how many sentences have
    int num_sentences = sentences(text);
    printf("%i\n", num_sentences);

    //THE CALCULATIONS
    //the average of letters per words
    float l = 100.0 * num_letters / num_words;

    //the average of sentences per words
    float s = 100.0 * num_sentences / num_words;

    //the grade:
    float grade = 0.0588 * l - 0.296 * s - 15.8;
    printf("%f\n", grade);
    int rounder = round(grade);

    if (rounder > 16)
    {
        printf("Grade 16+\n");
    }
    else if (rounder < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", rounder);
    }
}

//letters function
int letters(string phrase)
{
    int count = 0;
    int length_phrase = strlen(phrase);

    //count how many letters (without the points neither spaces)
    for (int i = 0; i < length_phrase; i++)
    {
        if (isalpha(phrase[i]) != 0)
        {
            count++;
        }
        else
        {
            ;
        }
    }
    return count;
}


int words(string phrase)
{
    int count = 0;
    int length = strlen(phrase);

    for (int i = 0; i < length; i++)
    {
        if (phrase[i] == ' ')
        {
            count++;
        }
    }

    return count + 1;
}


int sentences(string phrase)
{
    int count = 0;
    int length = strlen(phrase);

    for (int i = 0; i < length; i++)
    {
        if (phrase[i] == '.' || phrase[i] == '!' || phrase[i] == '?')
        {
            count++;
        }
    }

    return count;
}


#include <stdio.h>

int main()
{
    int age = 20;
    float marks = 95.5f;
    char grade = 'A';

    // Calculate result
    age = age + 5;

    /*
       This is a
       multi-line comment
    */

    if (marks >= 50.0)
    {
        printf("Age = %d\n", age);
        printf("Grade = %c\n", grade);
    }

    return 0;
}
#include <iostream>

// pass by reference
void swap(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
    printf("a=%d, b=%d\n", a, b);
}

// pass by value
// void swap(int a, int b)
// {
//     int temp;
//     temp = a;
//     a = b;
//     b = temp;
//     printf("a=%d, b=%d\n", a, b);
// }

// use pointer
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    printf("a=%d, b=%d\n", *a, *b);
    std::cout << "invoke:swap(int *a, int *b)" << std::endl;
}

int main(int argc, char * argv[])
{
    int a = 10;
    int b = 5;
    swap(a, b);
    printf("a=%d, b=%d\n", a, b);

    return 0;
}
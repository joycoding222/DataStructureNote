/*
递归
*/
#include <iostream>

using namespace std;

// 计算1~n 的和（非递归）
int fun(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += i;
    }
    return sum;
}

// 计算1~n 的和（递归方式）
int fun_recursive(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return fun_recursive(n-1) + n;
    }
}

// 斐波那契数列
int Fib(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    else
    {
        return Fib(n-1) + Fib(n-2);
    }
}

int main(int argc, char *argv[])
{
    cout << fun(10) << endl;
    cout << fun_recursive(10) << endl;
    cout << Fib(10) << endl;

    return 0;
}
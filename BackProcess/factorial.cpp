#include "factorial.h"

Factorial::Factorial(int number)
{
    n = number;
}

void Factorial::run(){
    int res[MAX];

    res[0] = 1;
    int res_size = 1;

    for (int x=2; x<=n; x++){
        while(locked){}
        res_size = multiply(x, res, res_size);
        msleep(sleepTimeInMs);
        emit UpdateBar((double)x/(double)n*100);
    }

    QString result = "";
    for (int i=res_size-1; i>=0; i--)
    {
        result += QString::fromStdString(std::to_string(res[i]));
    }
    emit CalculationDone(result);
}

int Factorial::multiply(int x, int res[], int res_size)
{
    int carry = 0;
    for (int i=0; i<res_size; i++)
    {
        int prod = res[i] * x + carry;
        res[i] = prod % 10;
        carry  = prod/10;
    }
    while (carry)
    {
        res[res_size] = carry%10;
        carry = carry/10;
        res_size++;
    }
    return res_size;
}

bool Factorial::isLocked(){
    return locked;
}

void Factorial::Lock(){
    locked = true;
}

void Factorial::Unlock(){
    locked = false;
}

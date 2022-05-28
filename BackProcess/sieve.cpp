#include "sieve.h"

Sieve::Sieve(int number)
{
    n = number;
}

void Sieve::run()
{
    QList<int> results;

    QVector<bool> prime(n+1,true);

    for (int p=2; p*p<=n; p++)
    {
        if (prime[p] == true)
        {
            for (int i=p*2; i<=n; i += p){
                while(locked){}
                prime[i] = false;
            }
        }
        msleep(sleepTimeInMs);
        emit UpdateBar((double)(p*p)/(double)n*100);
    }

    for (int p=2; p<=n; p++)
       if (prime[p])
          results.append(p);

    emit UpdateBar(100);
    emit CalculationDone(results);
}

bool Sieve::isLocked(){
    return locked;
}

void Sieve::Lock(){
    locked = true;
}

void Sieve::Unlock(){
    locked = false;
}


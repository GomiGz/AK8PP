#ifndef FACTORIAL_H
#define FACTORIAL_H
#include <QThread>

class Factorial : public QThread
{
    Q_OBJECT
public:
    Factorial(int number);
    bool isLocked();
    void Unlock();
    void Lock();


protected:
    void run() override;
signals:
    void CalculationDone(QString result);
    void UpdateBar(double percentage);

private:
    int multiply(int x, int res[], int res_size);
    int n;
    bool locked = false;
    #define MAX 500
    int sleepTimeInMs= 50;
};

#endif // FACTORIAL_H

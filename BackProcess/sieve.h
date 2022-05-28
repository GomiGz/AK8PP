#ifndef SIEVE_H
#define SIEVE_H
#include <QThread>

class Sieve :public QThread
{
    Q_OBJECT
public:
    Sieve(int Number);
    bool isLocked();
    void Unlock();
    void Lock();

protected:
    void run() override;

signals:
    void CalculationDone(QList<int> values);
    void UpdateBar(double percentage);

private:
    int n;
    bool locked = false;
    int sleepTimeInMs= 50;
};

#endif // SIEVE_H

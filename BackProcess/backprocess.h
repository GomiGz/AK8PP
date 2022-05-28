#ifndef BACKPROCESS_H
#define BACKPROCESS_H

#include <QMainWindow>
#include <factorial.h>
#include <sieve.h>

QT_BEGIN_NAMESPACE
namespace Ui { class BackProcess; }
QT_END_NAMESPACE

class BackProcess : public QMainWindow
{
    Q_OBJECT

public:
    BackProcess(QWidget *parent = nullptr);
    ~BackProcess();

private slots:
    void on_factButton_clicked();
    void on_factStop_clicked();

    void CalculationDoneFac(QString);
    void SetProgressFac(double);

    void on_sieveButton_clicked();
    void on_sieveStop_clicked();

    void CalculationDoneSieve(QList<int> values);
    void SetProgressSieve(double);

private:
    Ui::BackProcess *ui;
    bool factRunning = false;
    Factorial *factorial;

    bool sieveRunning = false;
    Sieve *sieve;

};
#endif // BACKPROCESS_H

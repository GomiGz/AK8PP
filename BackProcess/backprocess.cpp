#include "backprocess.h"
#include "ui_backprocess.h"

BackProcess::BackProcess(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BackProcess)
{
    ui->setupUi(this);

    ui->factBar->setValue(0);
    ui->sieveBar->setValue(0);
    ui->factResult->setText("");
    ui->sieveResult->clear();
    ui->factStop->setEnabled(false);
    ui->sieveStop->setEnabled(false);
}

BackProcess::~BackProcess()
{
    delete ui;
}

void BackProcess::on_factButton_clicked()
{
    if(!factRunning){
        ui->factBar->setValue(0);
        ui->factResult->setText("");
        factorial = new Factorial(ui->factInput->text().toInt());
        connect(factorial, &Factorial::CalculationDone, this, &BackProcess::CalculationDoneFac);
        connect(factorial, &Factorial::UpdateBar, this, &BackProcess::SetProgressFac);
        factorial->start();
        factRunning = true;
        ui->factStop->setEnabled(true);
        ui->factButton->setText("Pozastavit");
    }else{
        if(factorial->isLocked()){
            factorial->Unlock();
            ui->factButton->setText("Pozastavit");
        }else{
            factorial->Lock();
            ui->factButton->setText("Pokračovat");
        }
    }
}

void BackProcess::on_factStop_clicked()
{
    factRunning = false;
    ui->factBar->setValue(0);
    ui->factButton->setText("Spustit");
    ui->factStop->setEnabled(false);
    factorial->terminate();
}

void BackProcess::CalculationDoneFac(QString value)
{
    ui->factResult->setText(value);
    factRunning = false;
    ui->factButton->setText("Spustit");
    ui->factStop->setEnabled(false);
    factorial->terminate();
}

void BackProcess::SetProgressFac(double percentage)
{
    ui->factBar->setValue((int)percentage);
}

void BackProcess::on_sieveButton_clicked()
{
    if(!sieveRunning){
        ui->sieveBar->setValue(0);
        sieve = new Sieve(ui->sieveInput->text().toInt());
        connect(sieve, &Sieve::CalculationDone, this, &BackProcess::CalculationDoneSieve);
        connect(sieve, &Sieve::UpdateBar, this, &BackProcess::SetProgressSieve);
        sieve->start();
        sieveRunning = true;
        ui->sieveStop->setEnabled(true);
        ui->sieveButton->setText("Pozastavit");
    }else{
        if(sieve->isLocked()){
            sieve->Unlock();
            ui->sieveButton->setText("Pozastavit");
        }else{
            sieve->Lock();
            ui->sieveButton->setText("Pokračovat");
        }
    }
}

void BackProcess::on_sieveStop_clicked()
{
    sieveRunning = false;
    ui->sieveBar->setValue(0);
    ui->sieveButton->setText("Spustit");
    ui->sieveStop->setEnabled(false);
    sieve->terminate();
}

void BackProcess::CalculationDoneSieve(QList<int> values)
{
    for(unsigned int x : values){
        ui->sieveResult->append(QString::number(x) + " ");
    }
    sieveRunning = false;
    ui->sieveButton->setText("Spustit");
    ui->sieveStop->setEnabled(false);
    sieve->terminate();
}

void BackProcess::SetProgressSieve(double percentage)
{
    ui->sieveBar->setValue((int)percentage);
}

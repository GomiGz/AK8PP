#ifndef PONG_H
#define PONG_H

#include <QMainWindow>

#include "ball.h"
#include "paddle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Pong; }
QT_END_NAMESPACE

class Pong : public QMainWindow
{
    Q_OBJECT

public:
    Pong(QWidget *parent = nullptr);
    ~Pong();

signals:
    void draw(QPainter &painter);

private:
    Ui::Pong *ui;
    BallPtr ball;
    PaddlePtr userPaddle;
    PaddlePtr aiPaddle;


protected:
    virtual void paintEvent(QPaintEvent *);

};
#endif // PONG_H

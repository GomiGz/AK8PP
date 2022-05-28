#ifndef PONG_H
#define PONG_H

#include <QMainWindow>
#include <QKeyEvent>


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

public slots:
        void CountScore(bool AI);

signals:
    void draw(QPainter &painter);

private:
    Ui::Pong *ui;
    BallPtr ball;
    PaddlePtr userPaddle;
    PaddlePtr aiPaddle;
    int userScore = 0;
    int AIScore = 0;
    bool paused = false;


protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *);

};
#endif // PONG_H

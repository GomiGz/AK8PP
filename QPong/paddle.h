#ifndef PADDLE_H
#define PADDLE_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include "ball.h"

class Paddle: public QTimer
{
    Q_OBJECT
public:
    Paddle(QWidget *p,BallPtr b,bool aiPaddle);

public slots:
    void draw(QPainter &painter);

protected:
    QWidget *parent = NULL;
    QRect *rect;
    bool aiPaddle;
    BallPtr ball;

    virtual void timerEvent(QTimerEvent *);
};
typedef std::shared_ptr<Paddle> PaddlePtr;

#endif // PADDLE_H

#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QPainter>
#include <QGraphicsItem>

class Ball : public QTimer
{
    Q_OBJECT

public:
    Ball(QWidget *p);
    float x = 0;
    float y = 0;
    bool turn = false;
    void Reset();

public slots:
    void draw(QPainter &painter);
    void hit();

protected:
    QWidget *parent = NULL;
    float vx = 1;
    float vy = 1;

    virtual void timerEvent(QTimerEvent *);
};

typedef std::shared_ptr<Ball> BallPtr;
#endif // BALL_H

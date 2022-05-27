#ifndef BALL_H
#define BALL_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QPainter>

class Ball : public QTimer
{
    Q_OBJECT

public:
    Ball(QWidget *p);
    int x = 0;
    int y = 0;

public slots:
    void draw(QPainter &painter);

protected:
    QWidget *parent = NULL;
    float vx = 1;
    float vy = 1;

    virtual void timerEvent(QTimerEvent *);
};

typedef std::shared_ptr<Ball> BallPtr;
#endif // BALL_H

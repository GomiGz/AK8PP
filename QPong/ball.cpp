#include "ball.h"

Ball::Ball(QWidget *p)
{
    parent = p;

    QRect rct = parent->rect();
    x = rct.width()/2;
    y = rct.height()/2;
    vx = 5;

    start(10);
}

void Ball::Reset(){
    QRect rct = parent->rect();
    x = rct.width()/2;
    y = rct.height()/2;
    vx = 5;
    vy = 1;

    start(10);
}

void Ball::draw(QPainter &painter)
{
    painter.drawEllipse(x, y, 15, 15);
}

void Ball::timerEvent(QTimerEvent *)
{
    QRect rct = parent->rect();

    if(turn)
    {
        turn = false;
        vx *= -1;
        vy = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2)))-1.0;
    }
    if(y<0 || y>rct.height()) vy *= -1;

    x += vx;
    y += vy;

    parent->update();
}

void Ball::hit(){
    turn = true;
}


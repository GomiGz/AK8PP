#include "ball.h"

Ball::Ball(QWidget *p)
{
    parent = p;

    QRect rct = parent->rect();
    x = rct.width()/2;
    y = rct.height()/2;
    vx = rand() % 10;
    vy = rand() % 10;

    start(10);
}

void Ball::draw(QPainter &painter)
{
    painter.drawEllipse(x, y, 15, 15);
}

void Ball::timerEvent(QTimerEvent *)
{
    QRect rct = parent->rect();

    if(x<0 || x>rct.width()) vx *= -1;
    if(y<0 || y>rct.height()) vy *= -1;

    x += vx;
    y += vy;

    parent->update();
}


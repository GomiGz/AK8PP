#include "paddle.h"

Paddle::Paddle(QWidget *p,BallPtr b,bool aiPaddle)
{
    parent = p;
    ball = b;
    this->aiPaddle = aiPaddle;

    QRect rct = parent->rect();
    if(aiPaddle){
            rect = new QRect(rct.width()-10,rct.height()/2,10,80);
    }else{
            rect = new QRect(10,rct.height()/2,10,80);
    }
    start(1);
}

void Paddle::draw(QPainter &painter)
{
    if(aiPaddle){
        painter.fillRect(*rect,QBrush(QColor(Qt::red)));
    }else{
        painter.fillRect(*rect,QBrush(QColor(Qt::green)));
    }
}

void Paddle::timerEvent(QTimerEvent *)
{
    QRect par = parent->rect();

    if(aiPaddle){
        if(ball->y <= (rect->y() + rect->height()/2))
        {
            rect->setY((rect->y() - 1 < 0) ? 0 : rect->y() - 1);
        }else{
            rect->setY((rect->y() + 1 > par.height()) ? par.height() : rect->y() + 1);
        }
    }else{
        QPoint p = parent->mapFromGlobal(QCursor::pos());
        if(p.y() > rect->y()){
            rect->setY(rect->y() + 1);
        }else{
            rect->setY(rect->y() - 1);
        }
    }
    rect->setHeight(80);
    parent->update();
}

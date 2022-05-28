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

    float decideValue;
    if(aiPaddle){
        decideValue = ball->y;
    }else{
        QPoint p = parent->mapFromGlobal(QCursor::pos());
        decideValue = p.y();
    }
    float position = rect->y() + rect->height()/2;

    if(decideValue > position){
        rect->moveTop((rect->y() + rect->height() + 1 > par.height()) ? par.height() - rect->height() : rect->y() + 1);
    }else if (decideValue < position){
        rect->moveTop((rect->y() - 1 < 0) ? 0 : rect->y() - 1);
    }

    if(aiPaddle){
        if(ball->x >= rect->left()){
            //qDebug()<<"Ball Y :"<< ball->y << ", Paddle top: "<<rect->top() << ", Paddle bottom: " << rect->bottom();
            if(ball->y >= rect->top() && ball->y <= rect->bottom()){
                qDebug() << "Parry";
                emit Parry();
            }else{
                qDebug() << "Score";
                emit Score(false);
            }
        }
    }else{
        if(ball->x <= rect->right()){
            if(ball->y >= rect->top() && ball->y <= rect->bottom()){
                emit Parry();
            }else{
                emit Score(true);
            }
        }
    }
    parent->update();
}

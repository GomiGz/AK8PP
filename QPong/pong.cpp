#include "pong.h"
#include "ui_pong.h"

Pong::Pong(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pong)
{
    ui->setupUi(this);

    ball = BallPtr(new Ball(this));
    userPaddle = PaddlePtr(new Paddle(this,ball,false));
    aiPaddle = PaddlePtr(new Paddle(this,ball,true));

    connect(this, &Pong::draw, ball.get(), &Ball::draw);
    connect(this, &Pong::draw, userPaddle.get(), &Paddle::draw);
    connect(this, &Pong::draw, aiPaddle.get(), &Paddle::draw);
    connect(aiPaddle.get(), &Paddle::Parry,ball.get(),&Ball::hit);
    connect(userPaddle.get(), &Paddle::Parry,ball.get(),&Ball::hit);
    connect(aiPaddle.get(),&Paddle::Score,this,&Pong::CountScore);
    connect(userPaddle.get(),&Paddle::Score,this,&Pong::CountScore);
}

Pong::~Pong()
{
    delete ui;
}

void Pong::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), QBrush(QColor(Qt::darkGray)));

    QFont font = painter.font();
    font.setPixelSize(48);
    painter.setFont(font);

    painter.drawText(QPoint(rect().center().x()/2,60),QString::fromStdString(std::to_string(userScore)));
    painter.drawText(QPoint(rect().width() - rect().center().x()/2,60),QString::fromStdString(std::to_string(AIScore)));

    if(paused){
        painter.drawText(QPoint(rect().center().x()-80,rect().center().y()),"Resume by pressing P");
    }else{
        painter.drawText(QPoint(rect().center().x()-80,rect().bottom() - 30),"Pause by pressing P");
    }

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QColor(Qt::white)));

    emit draw(painter);
}

void Pong::CountScore(bool AI)
{
    qDebug()<< "Counting";
    if(AI){
        AIScore += 1;
    }else{
        userScore +=1;
    }
    ball->Reset();
}

void Pong::keyPressEvent(QKeyEvent *press)
{
    if(press->text() == 'p')
    {
        if(!paused)
        {
            ball->stop();
            aiPaddle->stop();
            userPaddle->stop();
        }else
        {
            ball->start();
            aiPaddle->start();
            userPaddle->start();
        }
        paused = !paused;
    }
}

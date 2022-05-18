#include "pong.h"
#include "ui_pong.h"

Pong::Pong(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Pong)
{
    ui->setupUi(this);

    ball = BallPtr(new Ball(this));

    connect(this, &Pong::draw, ball.get(), &Ball::draw);

}

Pong::~Pong()
{
    delete ui;
}

void Pong::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(rect(), QBrush(QColor(Qt::darkGray)));

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(QColor(Qt::white)));

    emit draw(painter);
}

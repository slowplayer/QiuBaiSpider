#include "widget.h"
#include "ui_widget.h"
#include <QNetworkReply>
#include <QRegExp>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    content=new QString();
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    mgr=new QNetworkAccessManager(this);
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(query(QNetworkReply*)));
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showtime()));
    timer->start(1000);
    showtime();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::query(QNetworkReply *reply)
{
    QString buffer=reply->readAll();
    QRegExp exp("<div class=\"content\" title=\"(.*)\">(.*)</div>");
    exp.setMinimal(true);
    int pos=0;
    while((pos = exp.indexIn(buffer,pos))!= -1)
    {
        content->append(exp.cap(1));
        content->append(exp.cap(2));
        pos+=exp.matchedLength();
       qDebug(QString::number(pos).toUtf8());
    }
    qDebug(QString::number(pos).toUtf8());
    ui->contentEdit->setText(*content);

}
void Widget::on_goButton_clicked()
{
    QString uri="http://www.qiushibaike.com/hot/page/";
    qDebug("下面开始爬");
    int i;
    for(i=0;i<10;i++)
    {
        QString url2(uri);
        url2.append(QString::number(i,10));
           qDebug(url2.toUtf8());
        mgr->get(QNetworkRequest(QUrl(url2)));
    }
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm:ss");
    ui->lcdNumber->display(text);
}
void Widget::showtime()
{
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm:ss");
    ui->lcdNumber2->display(text);
}

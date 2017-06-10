#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer();
    ui->setupUi(this);
    //connect(ui->sldRotationZ,SIGNAL(valueChanged(int)),ui->widget,SLOT(receiveRotationZ(int)));
    connect(ui->widget,SIGNAL(sendTranslateZ(int)),ui->sbxTranslateZ,SLOT(setValue(int)));
    connect(timer,SIGNAL(timeout()),ui->widget,SLOT(update()));
    timer->start(1000/60);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <string>
#include <QLabel>
#include <QLayout>

#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QSettings>
#include <QLayout>
#include <QObject>
#include <QWidget>
#include <vector>
#include <QDebug>
#include <QIcon>

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* testnumb = new QWidget(this);
    qDebug() << QString(QString::fromStdString(test.get_large_string()));

    while(std::string("1") < test.get_large_string())
    {
        test = test-biOne;
        //BigInt
        qDebug() << QString(QString::fromStdString(test.get_large_string()));
    }

    QLabel* testlabel = new QLabel(QString(QString::fromStdString(test.get_large_string())), testnumb);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "bigint.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //BigInt* test = new BigInt("123456789654321456789123456789123456789");
    //BigInt* biOne = new BigInt("1");

    BigInt test = BigInt("123456789123456789123456789123456789123456789123456789");
    BigInt biOne= BigInt("1234567896543214567891234567891231231231231456789123");
};

#endif // MAINWINDOW_H

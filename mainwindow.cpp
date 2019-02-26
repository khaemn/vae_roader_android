// http://www.amin-ahmadi.com

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_btn_pressed()
{
    QString file_name = QFileDialog::getOpenFileName(this);
    if(QFile(file_name).exists())
        return;
    Mat img = imread(file_name.toStdString());
    imshow("Mat", img);

    //QMessageBox::information(this, "info", "Image Size: " + QString::number(img.cols) + " x " + QString::number(img.rows));
}

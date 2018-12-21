#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    icon = new QIcon("/Icons/Open.bmp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStandardItem* MainWindow::createTree(int begin, int end) {

    QStandardItem* createditem;
    int step = 0, size = end-begin;

    if (begin == end) return new QStandardItem(QString::number(end)); //usar setIcon(icon)

    createditem = new QStandardItem(QString::number(begin)+".."+QString::number(end-1));

    if (end - begin <= 100){
        for (int i = begin; i < end; ++i) {
            createditem->appendRow(createTree(i,i));
        }
         return createditem;
    }

    while (size/=10) step++;
    step -= 1;
    step = int (pow(10,step));
    for (int i = begin; i < end; i+=step) {
        if (i+step < end)
            createditem->appendRow(createTree(i,i+step));
        else
            createditem->appendRow(createTree(i,end));
    }

    return createditem;
}

void MainWindow::on_pushButton_clicked()
{
    int number = ui->lineEdit->text().toInt();
    int step = 0, size = number;
    std::cout << "valor: " << number << std::endl;

    QStandardItemModel* model = new QStandardItemModel;
    if (number <= 100)
        for (int i = 0; i < number; ++i){
            model->appendRow(new QStandardItem(QString::number(i)));
    } else {
        while (size/=10) step++;
        step -= 1;
        step = int (pow(10,step));
        for (int i = 0; i < number; i+=step) {
            if (i+step < number)
                model->appendRow(createTree(i,i+step));
            else
                model->appendRow(createTree(i,number));
        }
    }

    ui->treeView->setModel(model);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}


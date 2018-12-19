#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<vector>

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

QStandardItemModel* MainWindow::createTreeViewModel(int itens){
    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *dad, *son;
    int step = 0, next_step = 0;
    while(step < itens){
        next_step += 100;
        if(next_step > itens){
            dad = new QStandardItem(QString::number(step)+".."+QString::number(itens));
        } else {
            dad = new QStandardItem(QString::number(step)+".."+QString::number(step+100));
        }

        model->appendRow(dad);
        for (; step < next_step && step < itens; ++step){
            son = new QStandardItem(QString::number(step));
            dad->appendRow(son);
        }
    }

    return model;
}

void MainWindow::on_pushButton_clicked()
{
    int number = ui->lineEdit->text().toInt();
    std::cout << "valor: " << number << std::endl;
    QStandardItemModel* model = createTreeViewModel(number);
    ui->treeView->setModel(model);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

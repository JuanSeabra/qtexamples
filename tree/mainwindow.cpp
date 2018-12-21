#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include<vector>
#include <QTreeWidget>
#include <QList>

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
    QStandardItem *dad, *son, *aux;
    QList<QStandardItem*> itemList;
    int begin = 0, end = 10;


    for (int i = 0; i < itens  && end <= itens; ++i) {
        if (end >= itens) end = itens - 1;
        dad = new QStandardItem(QString::number(begin)+".."+QString::number(end));
        for (int j = begin; j <= end; j++){
            son = new  QStandardItem(QString::number(j));
            dad->appendRow(son);
        }
        itemList.append(dad);
        begin = end;
        end += 10;
    }
    for (int i = 0; i < itemList.size(); ++i) {
        model->appendRow(itemList[i]);
    }

    return model;
}

QStandardItem* MainWindow::createTree(int begin, int end) {

    QStandardItem* createditem;
    int step = 0, size = end-begin;

    if (begin == end) return new QStandardItem(QString::number(end));

    createditem = new QStandardItem(QString::number(begin)+".."+QString::number(end));

    if (end - begin <= 10){
        for (int i = begin; i < end; ++i) {
            createditem->appendRow(createTree(i,i));
        }
         return createditem;
    }

    while (size/=10) step++;
    step -= 1;
    step = pow(10,step);
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
    std::cout << "valor: " << number << std::endl;

    QStandardItemModel* model = new QStandardItemModel;
    model->appendRow(createTree(0,number));
    ui->treeView->setModel(model);
}

void MainWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

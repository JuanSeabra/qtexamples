#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "open the file");
    QFile file(filename);
    currentFile = filename;
    currentFileInfo = new QFileInfo (filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "cannot open file" );
        return;
    }
    setWindowTitle(filename);
    QTextStream in(&file);
    //QString text = in.readAll();
    //ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"Warning", "cannot save file" );
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionFile_info_triggered()
{
    QMessageBox *message = new QMessageBox;
    message->setWindowTitle(QString("File info"));
    QString info = "File Path: " + currentFileInfo->absoluteFilePath() + "\n"
            + "File Size: " + QString::number(currentFileInfo->size()) + " bytes \n"
            + "Last Modified: " + currentFileInfo->lastModified().toString("yyyy-MM-dd hh:mm:ss t");
    message->setText(info);
    message->show();
}

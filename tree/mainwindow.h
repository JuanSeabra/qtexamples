#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    QStandardItem* createTree(int begin, int end);

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QIcon *icon;
};

#endif // MAINWINDOW_H

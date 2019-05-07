#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QTableWidgetItem>
#include<QDateTime>
#include<QThread>
#include<QQueue>
#include<QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void revolve();
    void acomode(QStringList orders);

    void on_tableWidget_itemClicked(QTableWidgetItem *item);

    void on_solve_clicked();
    void aboutQt();
    void aboutUs();

private:
    Ui::MainWindow *ui;
    QString getCurrentState();
};

#endif // MAINWINDOW_H

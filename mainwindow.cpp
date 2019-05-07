#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"deepsearchfirst.h"
#include"breadthsearchfirst.h"
#include"deeplimitedsearch.h"
#include"astar.h"
#include"idastar.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->revolve,SIGNAL(clicked()),this,SLOT(revolve()));
    QObject::connect(ui->actionAbout_Qt,SIGNAL(triggered()),this,SLOT(aboutQt()));
    QObject::connect(ui->actionAbout_us,SIGNAL(triggered()),this,SLOT(aboutUs()));






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::revolve()
{
    qDebug() << "revolve";
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int row,col;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(ui->tableWidget->item(i,j)->text().compare("") == 0){
                row = i;
                col = j;
                break;
            }

    for(int i=0;i<10;i++){
        this->repaint();
        QThread::msleep(300);
        int mov = qrand()%4;
        qDebug() << mov;
        if(mov == 0){//Para arriba
            if(row==0){i--;continue;
            }else{
                ui->tableWidget->item(row,col)->setText(ui->tableWidget->item(row-1,col)->text());
                ui->tableWidget->item(row-1,col)->setText("");
                row--;
                continue;
            }

        }
        if(mov == 1){//Para der
            if(col==3){i--;continue;
            }else{
                ui->tableWidget->item(row,col)->setText(ui->tableWidget->item(row,col+1)->text());
                ui->tableWidget->item(row,col+1)->setText("");
                col++;
                continue;
            }
        }
        if(mov == 2){//Para abajo
            if(row==3){i--;continue;
            }else{
                ui->tableWidget->item(row,col)->setText(ui->tableWidget->item(row+1,col)->text());
                ui->tableWidget->item(row+1,col)->setText("");
                row++;
                continue;
            }
        }
        if(mov == 3){//Para izq
            if(col==0){i--;continue;
            }else{
                ui->tableWidget->item(row,col)->setText(ui->tableWidget->item(row,col-1)->text());
                ui->tableWidget->item(row,col-1)->setText("");
                col--;
                continue;
            }
        }


    }

}







void MainWindow::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    QString text = item->text();
    if(text.compare("")==0)
        return;
    int col = item->column();
    int row = item->row();
    if(row!=0)
        if(ui->tableWidget->item(row-1,col)->text().compare("") == 0){
            ui->tableWidget->item(row-1,col)->setText(text);
            item->setText("");
            return;
        }
    if(row!=3)
        if(ui->tableWidget->item(row+1,col)->text().compare("") == 0){
            ui->tableWidget->item(row+1,col)->setText(text);
            item->setText("");
            return;
        }
    if(col!=3)
        if(ui->tableWidget->item(row,col+1)->text().compare("") == 0){
            ui->tableWidget->item(row,col+1)->setText(text);
            item->setText("");
            return;
        }
    if(col!=0)
        if(ui->tableWidget->item(row,col-1)->text().compare("") == 0){
            ui->tableWidget->item(row,col-1)->setText(text);
            item->setText("");
            return;
        }
}
void MainWindow::acomode(QStringList orders){
    bool ok;
    foreach (QString a, orders) {
        int i=0;
        for(int row=0;row<4;row++)
            for(int col=0;col<4;col++){
                if(a.at(i)=='0')
                    ui->tableWidget->item(row,col)->setText("");
                else
                    ui->tableWidget->item(row,col)->setText(QString::number(QString(a.at(i)).toInt(&ok,16)));
                i++;
            }
        this->repaint();
        QThread::msleep(500);
    }
}
void MainWindow::on_solve_clicked()
{

    if(ui->dfs->isChecked()){
        DeepSearchFirst *dfs = new DeepSearchFirst(getCurrentState(), QString("123456789ABCDEF0"));
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList result = dfs->findSolution();
        if(result.at(0).compare("TAKING TOO MUCH") == 0)
            QMessageBox::warning(this,"Taking too much time","The solution seems so far from this point",QMessageBox::Ok);
        else
            acomode(result);
        ui->steps->setText(QString::number(result.size()-1));
        ui->size->setText(QString::number(dfs->getAgenda()->size()));
        QApplication::restoreOverrideCursor();
        return;
    }
    if(ui->bfs->isChecked()){
        BreadthSearchFirst *bfs = new BreadthSearchFirst(getCurrentState(), QString("123456789ABCDEF0"));
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList result = bfs->findSolution();
        if(result.at(0).compare("TAKING TOO MUCH") == 0)
            QMessageBox::warning(this,"Taking too much time","The solution seems so far from this point",QMessageBox::Ok);
        else
            acomode(result);
        ui->steps->setText(QString::number(result.size()-1));
        QApplication::restoreOverrideCursor();
        return;
    }
    if(ui->dls->isChecked()){
        DeepLimitedSearch *dls = new DeepLimitedSearch(getCurrentState(), QString("123456789ABCDEF0"),ui->maxDeep->value());
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList result = dls->findSolution();
        if(result.at(0).compare("NO SOLUTION") == 0)
            QMessageBox::warning(this,"Theres no solution","Theres no solution at provided deep",QMessageBox::Ok);
        else
            acomode(result);
        ui->steps->setText(QString::number(result.size()-1));
        QApplication::restoreOverrideCursor();
        return;
    }
    if(ui->a->isChecked()){
        AStar *a = new AStar(getCurrentState(), QString("123456789ABCDEF0"));
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList result = a->findSolution();
        if(result.at(0).compare("NO SOLUTION") == 0)
            QMessageBox::warning(this,"Theres no solution","Theres no solution at provided deep",QMessageBox::Ok);
        else
            acomode(result);
        ui->steps->setText(QString::number(result.size()-1));
        QApplication::restoreOverrideCursor();
        return;
    }
    if(ui->ida->isChecked()){
        IDAStar *ida = new IDAStar(getCurrentState(), QString("123456789ABCDEF0"));
        QApplication::setOverrideCursor(Qt::WaitCursor);
        QStringList result = ida->findSolution();
        if(result.at(0).compare("NO SOLUTION") == 0)
            QMessageBox::warning(this,"Theres no solution","Theres no solution at provided deep",QMessageBox::Ok);
        else
            acomode(result);
        ui->steps->setText(QString::number(result.size()-1));
        QApplication::restoreOverrideCursor();
        return;
    }



}

void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this,QString("Problem Solving"));
}

void MainWindow::aboutUs()
{
    QMessageBox::about(this,tr("Artificial Intelligence"),tr("Problem solving algorithms implementation for IA subject. \nFI UNAM 2015."));
}

QString MainWindow::getCurrentState(){
    QString ret("");
    bool ok;
    for(int row=0;row<4;row++)
        for(int col=0;col<4;col++)
            ret.append(QString::number(ui->tableWidget->item(row,col)->text().toInt(&ok,10),16).toUpper());
    return ret;


}

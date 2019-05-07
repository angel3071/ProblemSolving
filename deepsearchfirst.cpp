#include "deepsearchfirst.h"

DeepSearchFirst::DeepSearchFirst(QString initialState,QString goal){
    qDebug() << "Constructor";
    this->agenda = new QStack<QString>();
    agenda->push(initialState);

    this->goal = goal;


}

DeepSearchFirst::~DeepSearchFirst(){

}


QStringList DeepSearchFirst::findSolution() {
    if(agenda->size()>50000)
        return QStringList() << "TAKING TOO MUCH";
    QString node = agenda->pop();
    qDebug() << "Node pop: " << node;
    if(node.compare(this->goal) == 0){
        qDebug() << "Solution found: " << node << " steps: " << expandeds.size();
        this->expandeds << node;
        return getExpandeds();
    }

    this->expandNode(node);
    return findSolution();



}

void DeepSearchFirst::expandNode(QString node) {

    if(this->agenda == NULL)
        return;
    if(this->expandeds.contains(node)){
        qDebug() << "Node previously expanded: " << node;
        return;
    }

    this->expandeds << node;
    int i = node.indexOf('0');
    QChar *dat = node.data();
    if(i%4 != 0){
        qSwap(dat[i],dat[i-1]);
        agenda->push(QString(dat));
        qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i-1]);
    }
    if((i-3)%4 != 0){
        qSwap(dat[i],dat[i+1]);
        agenda->push(QString(dat));
        qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i+1]);
    }
    if(i>3){
        qSwap(dat[i],dat[i-4]);
        agenda->push(QString(dat));
        qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i-4]);
    }
    if(i<12){
        qSwap(dat[i],dat[i+4]);
        agenda->push(QString(dat));
        qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i+4]);
    }


}
QStack<QString> *DeepSearchFirst::getAgenda() const
{
    return agenda;
}

void DeepSearchFirst::setAgenda(QStack<QString> *value)
{
    agenda = value;
}

QStringList DeepSearchFirst::getExpandeds() const
{
    return expandeds;
}

void DeepSearchFirst::setExpandeds(const QStringList &value)
{
    expandeds = value;
}




#include "breadthsearchfirst.h"

BreadthSearchFirst::BreadthSearchFirst(QString initialState, QString goal)
{
    qDebug() << "Constructor";
    this->agenda = new QQueue<QString>();
    agenda->enqueue(initialState);

    this->goal = goal;

}

BreadthSearchFirst::~BreadthSearchFirst()
{

}

QStringList BreadthSearchFirst::findSolution()
{
    if(agenda->size()>50000)
        return QStringList() << "TAKING TOO MUCH";
    QString node = agenda->dequeue();
    qDebug() << "Node dequeued: " << node;
    if(node.compare(this->goal) == 0){
        qDebug() << "Solution found: " << node << " steps: " << expandeds.size();
        this->expandeds << node;
        return getExpandeds();
    }

    this->expandNode(node);
    return findSolution();
}

QStringList BreadthSearchFirst::getExpandeds() const
{
    return this->expandeds;

}

void BreadthSearchFirst::expandNode(QString node)
{

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
        agenda->enqueue(QString(dat));
        qDebug() << "Agenda enqueued: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i-1]);
    }
    if((i-3)%4 != 0){
        qSwap(dat[i],dat[i+1]);
        agenda->enqueue(QString(dat));
        qDebug() << "Agenda enqueued: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i+1]);
    }
    if(i>3){
        qSwap(dat[i],dat[i-4]);
        agenda->enqueue(QString(dat));
        qDebug() << "Agenda enqueued: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i-4]);
    }
    if(i<12){
        qSwap(dat[i],dat[i+4]);
        agenda->enqueue(QString(dat));
        qDebug() << "Agenda enqueued: " << QString(dat) << " size: " << agenda->size();
        qSwap(dat[i],dat[i+4]);
    }
}


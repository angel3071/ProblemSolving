#include "deeplimitedsearch.h"

DeepLimitedSearch::DeepLimitedSearch(QString initialState,QString goal, int maxDeep)
{

    qDebug() << "Constructor";
    this->agenda = new QStack<QString>();
    agenda->push(initialState);
    this->maxDeep = maxDeep;
    this->goal = goal;
}

DeepLimitedSearch::~DeepLimitedSearch()
{

}

QStringList DeepLimitedSearch::findSolution()
{
    if(agenda->size() == 0)
        return QStringList() << "NO SOLUTION";
    QString node = agenda->pop();
    qDebug() << "Node pop: " << node;
    if(node.compare(this->goal) == 0){
        qDebug() << "Solution found: " << node << " steps: " << expandeds.size();
        this->expandeds << node;
        return getExpandeds();
    }
    if(expandeds.size()<=maxDeep)
        this->expandNode(node);
    return findSolution();

}
QStringList DeepLimitedSearch::getExpandeds() const
{
    return expandeds;
}

void DeepLimitedSearch::setExpandeds(const QStringList &value)
{
    expandeds = value;
}

void DeepLimitedSearch::expandNode(QString node)
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




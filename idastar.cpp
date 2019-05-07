#include "idastar.h"

IDAStar::IDAStar(QString initialState, QString goal)
{
    qDebug() << "Constructor";
    this->agenda = new QHash<QString,int>();
    agenda->insert(initialState,getHeuristic(initialState));
    qDebug() << getHeuristic(initialState);
    this->goal = goal;
    this->limitDeepening = 1;
}

IDAStar::~IDAStar()
{

}

QStringList IDAStar::findSolution()
{
    if(agenda->size()>50000)
        return QStringList() << "TAKING TOO MUCH";
    qDebug() << agenda->size();

    QList<int> vals = agenda->values();
    qSort(vals.begin(),vals.end());
    QString node = agenda->key(vals.first());
    agenda->remove(node);
//    qDebug() << node;
    qDebug() << "Node pop: " << node;
    if(node.compare(this->goal) == 0){
        qDebug() << "Solution found: " << node << " steps: " << expandeds.size();
        this->expandeds << node;
        return getExpandeds();
    }

    this->expandNode(node);
    this->limitDeepening++;
    return findSolution();
}
QStringList IDAStar::getExpandeds() const
{
    return expandeds;
}

void IDAStar::setExpandeds(const QStringList &value)
{
    expandeds = value;
}

void IDAStar::expandNode(QString node)
{
    if(this->agenda == NULL)
        return;
    if(this->expandeds.contains(node)){
        qDebug() << "Node previously expanded: " << node;
        return;
    }
    int cost = 0;
    this->expandeds << node;
    int i = node.indexOf('0');
    QChar *dat = node.data();
    if(i%4 != 0){
        qSwap(dat[i],dat[i-1]);
        cost = getHeuristic(QString(dat));
        if (cost <= limitDeepening){
            agenda->insert(QString(dat),getHeuristic(QString(dat)));
            qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        }
        qSwap(dat[i],dat[i-1]);
    }
    if((i-3)%4 != 0){
        qSwap(dat[i],dat[i+1]);
        cost = getHeuristic(QString(dat));
        if (cost <= limitDeepening){
            agenda->insert(QString(dat),getHeuristic(QString(dat)));
            qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        }
        qSwap(dat[i],dat[i+1]);
    }
    if(i>3){
        qSwap(dat[i],dat[i-4]);
        cost = getHeuristic(QString(dat));
        if (cost <= limitDeepening){
            agenda->insert(QString(dat),getHeuristic(QString(dat)));
            qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        }
        qSwap(dat[i],dat[i-4]);
    }
    if(i<12){
        qSwap(dat[i],dat[i+4]);
        cost = getHeuristic(QString(dat));
        if (cost <= limitDeepening){
            agenda->insert(QString(dat),getHeuristic(QString(dat)));
            qDebug() << "Agenda push: " << QString(dat) << " size: " << agenda->size();
        }
        qSwap(dat[i],dat[i+4]);
    }
    if(agenda->size()==0){
        limitDeepening++;
        this->expandNode(node);
    }
}

int IDAStar::getHeuristic(QString node)
{
    int ret=0;
    bool ok;
    for(int i=0; i<node.size();i++)
        if(node.at(i)!='0')
            if(QString(node.at(i)).toInt(&ok,16)-1 - i != 0)
                ret++;



    return ret;
}



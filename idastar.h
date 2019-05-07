#ifndef IDASTAR_H
#define IDASTAR_H
#include <QString>
#include <QStack>
#include <QDebug>
#include<QTime>

class IDAStar
{
public:
    IDAStar(QString initialState, QString goal);
    ~IDAStar();
     QStringList findSolution();
     QStringList getExpandeds() const;
     void setExpandeds(const QStringList &value);

private:
     void expandNode(QString node);
     int getHeuristic(QString node);
     int limitDeepening;
     QString goal;
    QHash<QString,int> *agenda;
    QStringList expandeds;
};

#endif // IDASTAR_H

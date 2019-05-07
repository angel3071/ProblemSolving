#ifndef ASTAR_H
#define ASTAR_H
#include <QString>
#include <QStack>
#include <QDebug>
#include<QTime>

class AStar
{
public:
    AStar(QString initialState, QString goal);
    ~AStar();
    QStringList findSolution();
    QStringList getExpandeds() const;
    void setExpandeds(const QStringList &value);

private:
    void expandNode(QString node);
    int getHeuristic(QString node);
    QString goal;
    QHash<QString,int> *agenda;
    QStringList expandeds;
};

#endif // ASTAR_H



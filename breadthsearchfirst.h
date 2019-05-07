#ifndef BREADTHSEARCHFIRST_H
#define BREADTHSEARCHFIRST_H
#include <QString>
#include <QQueue>
#include <QDebug>

class BreadthSearchFirst
{
public:
    BreadthSearchFirst(QString initialState, QString goal);
    ~BreadthSearchFirst();
    QStringList findSolution();
    QStringList getExpandeds() const;
private:
    void expandNode(QString node);
    QString goal;
    QQueue<QString> *agenda;
    QStringList expandeds;
};

#endif // BREADTHSEARCHFIRST_H

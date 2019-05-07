#ifndef DEEPSEARCHFIRST_H
#define DEEPSEARCHFIRST_H
#include <QString>
#include <QStack>
#include <QDebug>
#include<QTime>

class DeepSearchFirst
{
public:
    DeepSearchFirst(QString initialState, QString goal);
    ~DeepSearchFirst();
    QStringList findSolution();
    QStringList getExpandeds() const;
    void setExpandeds(const QStringList &value);

    QStack<QString> *getAgenda() const;
    void setAgenda(QStack<QString> *value);

private:
    void expandNode(QString node);
    QString goal;
    QStack<QString> *agenda;
    QStringList expandeds;
};

#endif // DEEPSEARCHFIRST_H

#ifndef DEEPLIMITEDSEARCH_H
#define DEEPLIMITEDSEARCH_H
#include <QString>
#include <QStack>
#include <QDebug>

class DeepLimitedSearch
{
public:
    DeepLimitedSearch(QString initialState, QString goal, int maxDeep);
    ~DeepLimitedSearch();
    QStringList findSolution();
    QStringList getExpandeds() const;
    void setExpandeds(const QStringList &value);

private:
    void expandNode(QString node);
    int maxDeep;
    QString goal;
    QStack<QString> *agenda;
    QStringList expandeds;
};

#endif // DEEPLIMITEDSEARCH_H

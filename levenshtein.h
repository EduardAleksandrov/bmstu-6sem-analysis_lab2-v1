#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <QObject>

class Levenshtein : public QObject
{
public:
    explicit Levenshtein(QObject *parent = nullptr);
    int distance_matrix(QString s1, QString s2, bool print_flag = false);
    int distance_recursion(QString s1, int n1, QString s2, int n2);
    unsigned int ReplaceCost(QChar a, QChar b);
    int distance_tail_recursion(QString s1, int n1, QString s2, int n2, QVector<QVector<int>>& dp);
    int distance_massive(QString s1, QString s2);
signals:

};

#endif // LEVENSHTEIN_H

#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <QObject>

class Levenshtein : public QObject
{
public:
    explicit Levenshtein(QObject *parent = nullptr);
    int distance(QString s1, QString s2, bool print_flag = false);
    int distance_damer(QString s1, QString s2, bool print_flag = false);

signals:

};

#endif // LEVENSHTEIN_H

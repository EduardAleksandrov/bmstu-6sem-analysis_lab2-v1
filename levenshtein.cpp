#include "levenshtein.h"
#include <QVector>
#include <cmath>
#include <QDebug>

Levenshtein::Levenshtein(QObject *parent) : QObject(parent)
{

}
int Levenshtein::distance(QString s1, QString s2, bool print_flag)
{
    int len_s1 = s1.length();
    int len_s2 = s2.length();
    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;

    QVector<QVector<int>> matrix(len_s1 + 1, QVector<int>(len_s2 + 1));
    // init
    for (int i = 0; i <= len_s1; i++)
    {
        for (int j = 0; j <= len_s2; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i <= len_s1; i++)
    {
        for (int j = 0; j <= len_s2; j++)
        {
            if (i == 0)
                matrix[i][j] = j;
            if (j == 0)
                matrix[i][j] = i;
        }
    }

    int cost;
    for (int i = 1; i < len_s1 + 1; i++)
    {
        for (int j = 1; j < len_s2 + 1; j++)
        {
            cost = s1[i-1] == s2[j-1] ? 0 : 1;
            matrix[i][j] = std::min(std::min(matrix[i-1][j] + 1,
                matrix[i][j-1] + 1), matrix[i-1][j-1] + cost);
        }
    }
    if(print_flag)
    {
        QDebug dbg = qDebug().nospace().noquote();
        for (int i = 0; i <= len_s1; i++)
        {
            for (int j = 0; j <= len_s2; j++)
            {
                dbg << matrix[i][j] << " ";
            }
            dbg << "\n";
        }
    }

    int res = matrix[len_s1][len_s2];
    return res;
}

int Levenshtein::distance_damer(QString s1, QString s2, bool print_flag)
{
    int len_s1 = s1.length(); //столбец
    int len_s2 = s2.length();

    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;

    QVector<QVector<int>> matrix(len_s1 + 1, QVector<int>(len_s2 + 1));
    // init
    for (int i = 0; i <= len_s1; i++)
    {
        for (int j = 0; j <= len_s2; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i <= len_s1; i++)
    {
        for (int j = 0; j <= len_s2; j++)
        {
            if (i == 0)
                matrix[i][j] = j;
            if (j == 0)
                matrix[i][j] = i;
        }
    }

    int cost, buf;
    for (int i = 1; i < len_s1 + 1; i++)
    {
        for (int j = 1; j < len_s2 + 1; j++)
        {
            cost = s1[i - 1] == s2[j - 1] ? 0 : 1;
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
            {
                buf = matrix[i - 2][j - 2] + 1;
                matrix[i][j] = std::min(std::min(std::min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + cost), buf);
            }
            else
            {
                matrix[i][j] = std::min(std::min(matrix[i - 1][j] + 1,
                    matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + cost);
            }
        }
    }
    if(print_flag)
    {
        QDebug dbg = qDebug().nospace().noquote();
        for (int i = 0; i <= len_s1; i++)
        {
            for (int j = 0; j <= len_s2; j++)
            {
                dbg << matrix[i][j] << " ";
            }
            dbg << "\n";
        }
    }

    int res = matrix[len_s1][len_s2];
    return res;
}

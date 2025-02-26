#include "levenshtein.h"
#include <QVector>
#include <QDebug>
#include <algorithm>

Levenshtein::Levenshtein(QObject *parent) : QObject(parent)
{

}
int Levenshtein::distance_matrix(QString s1, QString s2, bool print_flag)
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
            matrix[i][j] = std::min({matrix[i-1][j] + 1, matrix[i][j-1] + 1, matrix[i-1][j-1] + cost});
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

unsigned int Levenshtein::ReplaceCost(QChar a, QChar b)
{
    return (a != b);
}

int Levenshtein::distance_recursion(QString& s1, int n1, QString& s2, int n2)
{
    if (n1 == 0)
        return n2;
    if (n2 == 0)
        return n1;

    int insertCost = distance_recursion(s1, n1, s2, n2 - 1) + 1;
    int deleteCost = distance_recursion(s1, n1 - 1, s2, n2) + 1;
    int replaceCost = distance_recursion(s1, n1 - 1, s2, n2 - 1) + ReplaceCost(s1[n1 - 1], s2[n2 - 1]);

    return std::min({insertCost, deleteCost, replaceCost});
}

int Levenshtein::distance_tail_recursion(QString& s1, int n1, QString& s2, int n2, QVector<QVector<int>>& dp)
{
    if (dp[n1][n2] != -1) {
        return dp[n1][n2]; // Возвращаем уже вычисленное значение
    }

    if (n1 == 0) {
        return dp[n1][n2] = n2; // Если первая строка пустая
    }
    if (n2 == 0) {
        return dp[n1][n2] = n1; // Если вторая строка пустая
    }

    int insert_cost = distance_tail_recursion(s1, n1, s2, n2 - 1, dp) + 1; // Вставка
    int delete_cost = distance_tail_recursion(s1, n1 - 1, s2, n2, dp) + 1; // Удаление
    int replace_cost = distance_tail_recursion(s1, n1 - 1, s2, n2 - 1, dp) + ReplaceCost(s1[n1 - 1], s2[n2 - 1]); // Замена

    return dp[n1][n2] = std::min({insert_cost, delete_cost, replace_cost}); // Сохраняем результат в матрице

}

int Levenshtein::distance_massive(QString s1, QString s2)
{
    int len_s1 = s1.length();
    int len_s2 = s2.length();
    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;

    QVector<int> previous(len_s2 + 1);
    QVector<int> current(len_s2 + 1);

    // Инициализация первой строки
    for (int j = 0; j <= len_s2; j++)
    {
        previous[j] = j;
    }

    for (int i = 1; i <= len_s1; i++)
    {
        current[0] = i; // Инициализация первой колонки для текущей строки

        for (int j = 1; j <= len_s2; j++)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            current[j] = std::min({previous[j] + 1, current[j - 1] + 1, previous[j - 1] + cost});
        }

        // Копируем текущую строку в предыдущую для следующей итерации
        previous = current;
    }

    return previous[len_s2];
}




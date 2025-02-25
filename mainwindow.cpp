// step two
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    leven = new Levenshtein(this);
    ui->radioButton->setChecked(true);

    QString a1 = "one";
    QString b1 = "two";

    QString a2 = "oneone";
    QString b2 = "twotwo";

    QString a3 = "oneoneone";
    QString b3 = "twotwotwo";

    QString a4 = "oneoneoneoneoneoneoneone";
    QString b4 = "twotwotwotwotwotwotwotwo";

    QString a5 = "oneoneoneoneoneoneoneoneoneoneoneoneoneoneoneone";
    QString b5 = "twotwotwotwotwotwotwotwotwotwotwotwotwotwotwotwo";

    QVector <double> N {static_cast<double>(a1.length()), static_cast<double>(a2.length()), static_cast<double>(a3.length()), static_cast<double>(a4.length()), static_cast<double>(a5.length())};
    QVector <QString*> A {&a1,&a2,&a3,&a4,&a5};
    QVector <QString*> B {&b1,&b2,&b3,&b4,&b5};

// Матрица Левенштейна
    QVector <double> timer_result_leven;
    for(int i = 0; i < A.size(); i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 10; j++)
        {
            result_leven = leven->distance_matrix(*(A[i]), *(B[i]));
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 10; // microseconds
        timer_result_leven.push_back(result_one);
    }

    ui->widget_11->clearGraphs();
    ui->widget_11->addGraph();
    ui->widget_11->graph(0)->setData(N, timer_result_leven);
    ui->widget_11->graph(0)->setPen(QColor(50, 50, 50, 255));
//    ui->widget_11->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_11->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_11->xAxis->setLabel("N");
    ui->widget_11->yAxis->setLabel("t, ms");
    ui->widget_11->xAxis->setRange(0, 60);
    ui->widget_11->yAxis->setRange(0, 1500);
// ---

// Рекурсия Левенштейна
    QVector <double> timer_result_leven_rec;
    for(int i = 0; i < 3; i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 3; j++)
        {
            result_leven = leven->distance_recursion(*(A[i]), (*(A[i])).length(), *(B[i]), (*(B[i])).length());
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 3; // microseconds
        timer_result_leven_rec.push_back(result_one);
    }

//    ui->lineEdit_3->setText(QString::number(timer_result_leven_rec[2]));

    ui->widget_33->clearGraphs();
    ui->widget_33->addGraph();
    ui->widget_33->graph(0)->setData(N, timer_result_leven_rec);
    ui->widget_33->graph(0)->setPen(QColor(50, 50, 50, 255));
//    ui->widget_33->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_33->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_33->xAxis->setLabel("N");
    ui->widget_33->yAxis->setLabel("t, ms");
    ui->widget_33->xAxis->setRange(0, 60);
    ui->widget_33->yAxis->setRange(0, 140000);
// ---

// Массив Левенштейна
    QVector <double> timer_result_leven_massive;
    for(int i = 0; i < A.size(); i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 10; j++)
        {
            result_leven = leven->distance_massive(*(A[i]), *(B[i]));;
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 10; // microseconds
        timer_result_leven_massive.push_back(result_one);
    }

    ui->widget_22->clearGraphs();
    ui->widget_22->addGraph();
    ui->widget_22->graph(0)->setData(N, timer_result_leven_massive);
    ui->widget_22->graph(0)->setPen(QColor(50, 50, 50, 255));
//    ui->widget_22->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_22->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_22->xAxis->setLabel("N");
    ui->widget_22->yAxis->setLabel("t, ms");
    ui->widget_22->xAxis->setRange(0, 60);
    ui->widget_22->yAxis->setRange(0, 1500);
// ---

// Хвостовая рекурсия Левенштейна
    QVector <double> timer_result_leven_tailrec;
    for(int i = 0; i <  A.size(); i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 10; j++)
        {
            QVector<QVector<int>> dp((*(A[i])).length() + 1, QVector<int>((*(B[i])).length() + 1, -1)); // Инициализация матрицы
            result_leven = leven->distance_tail_recursion(*(A[i]), (*(A[i])).length(), *(B[i]), (*(B[i])).length(), dp);
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 10; // microseconds
        timer_result_leven_tailrec.push_back(result_one);
    }

//    ui->lineEdit_3->setText(QString::number(timer_result_leven_rec[2]));

    ui->widget_44->clearGraphs();
    ui->widget_44->addGraph();
    ui->widget_44->graph(0)->setData(N, timer_result_leven_tailrec);
    ui->widget_44->graph(0)->setPen(QColor(50, 50, 50, 255));
//    ui->widget_44->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_44->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_44->xAxis->setLabel("N");
    ui->widget_44->yAxis->setLabel("t, ms");
    ui->widget_44->xAxis->setRange(0, 60);
    ui->widget_44->yAxis->setRange(0, 1500);
// ---
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_3->clear();

    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();

    QVector<QVector<int>> dp(a.length() + 1, QVector<int>(b.length() + 1, -1)); // Инициализация матрицы

    int result;
    if(ui->radioButton->isChecked())
    {
        result = leven->distance_matrix(a, b, true);
    } else if(ui->radioButton_2->isChecked())
    {
        result = leven->distance_recursion(a, a.length(), b, b.length());
    } else if(ui->radioButton_3->isChecked())
    {
        result = leven->distance_massive(a, b);
    } else {
        result = leven->distance_tail_recursion(a, a.length(), b, b.length(), dp);
    }

    ui->lineEdit_3->setText(QString::number(result));
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}


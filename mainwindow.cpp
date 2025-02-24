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

    QString a1 = "one";
    QString b1 = "two";

    QString a2 = "oneone";
    QString b2 = "twotwo";

    QString a3 = "oneoneoneone";
    QString b3 = "twotwotwotwo";

    QString a4 = "oneoneoneoneoneoneoneone";
    QString b4 = "twotwotwotwotwotwotwotwo";

    QString a5 = "oneoneoneoneoneoneoneoneoneoneoneoneoneoneoneone";
    QString b5 = "twotwotwotwotwotwotwotwotwotwotwotwotwotwotwotwo";

    QVector <double> N {static_cast<double>(a1.length()), static_cast<double>(a2.length()), static_cast<double>(a3.length()), static_cast<double>(a4.length()), static_cast<double>(a5.length())};
    QVector <QString*> A {&a1,&a2,&a3,&a4,&a5};
    QVector <QString*> B {&b1,&b2,&b3,&b4,&b5};

    QVector <double> timer_result_leven;
    for(int i = 0; i < A.size(); i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 10; j++)
        {
            result_leven = leven->distance(*(A[i]), *(B[i]));
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 10; // microseconds
        timer_result_leven.push_back(result_one);
    }

    ui->widget_11->clearGraphs();
    ui->widget_11->addGraph();
    ui->widget_11->graph(0)->setData(N, timer_result_leven);
    ui->widget_11->graph(0)->setPen(QColor(50, 50, 50, 255));
    ui->widget_11->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_11->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_11->xAxis->setLabel("N");
    ui->widget_11->yAxis->setLabel("t, ms");
    ui->widget_11->xAxis->setRange(0, 60);
    ui->widget_11->yAxis->setRange(0, 750);

    QVector <double> timer_result_leven_damer;
    for(int i = 0; i < A.size(); i++)
    {
        int result_leven;
        clock_t start_one = clock();
        for(unsigned int j = 0; j < 10; j++)
        {
            result_leven = leven->distance_damer(*(A[i]), *(B[i]));
        }
        clock_t end_one = clock();
        double result_one = (double(end_one - start_one) / CLOCKS_PER_SEC) * 1000000 / 10; // microseconds
        timer_result_leven_damer.push_back(result_one);
    }

    ui->widget_22->clearGraphs();
    ui->widget_22->addGraph();
    ui->widget_22->graph(0)->setData(N, timer_result_leven_damer);
    ui->widget_22->graph(0)->setPen(QColor(50, 50, 50, 255));
    ui->widget_22->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget_22->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::blue, Qt::white, 5));
    ui->widget_22->xAxis->setLabel("N");
    ui->widget_22->yAxis->setLabel("t, ms");
    ui->widget_22->xAxis->setRange(0, 60);
    ui->widget_22->yAxis->setRange(0, 750);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_3->clear();
    int check_box_damerau = ui->checkBox->isChecked();

    QString a = ui->lineEdit->text();
    QString b = ui->lineEdit_2->text();

    int result;
    if(check_box_damerau)
    {
        result = leven->distance_damer(a, b, true);
    } else {
        result = leven->distance(a, b, true);
    }

    ui->lineEdit_3->setText(QString::number(result));
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}


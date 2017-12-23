#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->setHeightPercent(ui->SliderHeight->value());
    ui->widget->setDiameterPercent(ui->SliderDiameter->value());
    ui->widget->setApproximationPercent(ui->SliderApproximation->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::on_SliderScale_sliderMoved(int position)
{
    ui->widget->setScalePercent(position);
}*/

void MainWindow::on_SliderHeight_sliderMoved(int position)
{
    ui->widget->setHeightPercent(position);
}

void MainWindow::on_SliderDiameter_sliderMoved(int position)
{
    ui->widget->setDiameterPercent(position);
}

void MainWindow::on_SliderApproximation_sliderMoved(int position)
{
    ui->widget->setApproximationPercent(position);
}

void MainWindow::on_isPolyFill_stateChanged(int arg1)
{
    //qDebug() << arg1;
     ui->widget->setPolyFillState(arg1 != 0);
}

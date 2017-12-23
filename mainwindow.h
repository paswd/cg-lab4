#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SliderScale_sliderMoved(int position);

    void on_SliderHeight_sliderMoved(int position);

    void on_SliderDiameter_sliderMoved(int position);

    void on_SliderApproximation_sliderMoved(int position);

    void on_isPolyFill_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

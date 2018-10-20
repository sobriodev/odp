#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chart.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionBackground_color_triggered();
    void on_actionPlot_color_triggered();
    void on_actionGrid_color_triggered();
    void on_actionText_color_triggered();

private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *event);
    Chart *chart;
    double *dataBuffer;
};

#endif // MAINWINDOW_H

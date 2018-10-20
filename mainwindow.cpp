#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart = new Chart();
    chart->gridNumX=16;
    chart->gridNumY=10;
    chart->minValueX= 0;
    chart->maxValueX= 1024;
    chart->minValueY=-100;
    chart->maxValueY= 100;
    chart->dataSize=1024;
    dataBuffer=new double[chart->dataSize];
    chart->data = dataBuffer;
    for(uint i=0;i<chart->dataSize; i++)
        dataBuffer[i]= 0;
}

MainWindow::~MainWindow()
{
    delete [] dataBuffer;
    delete chart;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    chart->drawLinearGrid(&painter, centralWidget()->geometry());
    //painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setCompositionMode(QPainter::CompositionMode_Screen);
    chart->drawLinearData(&painter);
}

void MainWindow::on_actionNew_triggered()
{
    for(uint i=0;i<chart->dataSize; i++)
        dataBuffer[i]=0;
    repaint();
}

void MainWindow::on_actionOpen_triggered()
{
    QString FileName;
    FileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("Data (*.dat)"));
    QFile file(FileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    file.read(reinterpret_cast<char*>(chart->data),chart->dataSize*sizeof(double));
    file.close();
    repaint();
}

void MainWindow::on_actionSave_triggered()
{
    QString FileName;
    FileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("Data (*.dat)"));
    QFile file(FileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    file.write(reinterpret_cast<char*>(chart->data),chart->dataSize*sizeof(double));
    file.close();
}

void MainWindow::on_actionBackground_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if( color.isValid() )
    {
        chart->backgroundColor=color;
        repaint();
    }
}

void MainWindow::on_actionPlot_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if( color.isValid() )
    {
        chart->plotColor=color;
        repaint();
    }
}

void MainWindow::on_actionGrid_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if( color.isValid() )
    {
        chart->gridColor=color;
        repaint();
    }
}

void MainWindow::on_actionText_color_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this);
    if( color.isValid() )
    {
        chart->textColor=color;
        repaint();
    }
}

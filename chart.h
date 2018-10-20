#ifndef CHART_H
#define CHART_H

#include <QPainter>

#define MX 40 /* Left and right padding */
#define MY 40 /* Top and bottom padding */

class Chart
{
public:
    Chart();

    /* Draw plot grid */
    void drawLinearGrid(QPainter *painter, QRect geometry);
    /* Draw plot data */
    void drawLinearData(QPainter *painter);

    int gridNumX=10, gridNumY=10;
    int minValueX=-0, maxValueX=100;
    int minValueY=-100, maxValueY=100;
    double *data;
    uint dataSize;

    /* Plot colors */
    QColor backgroundColor=Qt::black;
    QColor gridColor=Qt::gray;
    QColor textColor=Qt::white;
    QColor plotColor=Qt::red;

   private:
    double dx, dy, dvx, dvy;
    int gx, gy, gw, gh, gmy;
};

#endif // CHART_H

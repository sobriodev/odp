#include "chart.h"

Chart::Chart() {}

void Chart::drawLinearGrid(QPainter *painter, QRect geometry)
{

    gx=geometry.x()+MX; // Plot starting x coordinate (Window's left edge x coordinate + left padding)
    gy=geometry.y()+MY; // Plot starting y coordinate (Window's left edge y coordinate + top padding)

    gw=geometry.width()-(2*MX); // Plot width
    gh=geometry.height()-(2*MY); // Plot height

    dx=gw/static_cast<double>(gridNumX); // X axis grid step
    dy=gh/static_cast<double>(gridNumY); // Y axis grid step

    // Draw window's frame
    QPen pen;
    pen.setWidth(1);
    pen.setColor(backgroundColor);
    painter->setPen(pen);
    painter->setBrush(backgroundColor);
    painter->drawRect(geometry);

    // Draw plot's frame
    pen.setStyle(Qt::SolidLine);
    pen.setColor(gridColor);
    pen.setWidth(2);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(pen);
    painter->drawRect(gx, gy, gw, gh);

    // Draw X,Y grid
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    painter->setPen(pen);
    for (int px=1; px<gridNumX; px++) // X axis grid
        painter->drawLine(QLineF(gx+(px*dx), gy, gx+(px*dx), gy+gh));
    for (int py=1; py<gridNumY; py++) // Y axis grid
        painter->drawLine(QLineF(gx, gy+(py*dy), gx+gw, gy+(py*dy)));

    // Draw X,Y unit labels
    QFont font;
    font.setPointSize(8);
    painter->setFont(font);
    pen.setColor(textColor);
    painter->setPen(pen);

    dvx = (maxValueX - minValueX) / gridNumX;
    dvy = (maxValueY - minValueY) / gridNumY;
    for (int px=0; px <= gridNumX; px++) // X axis
        painter->drawText(QPoint(gx+(static_cast<int>(dx)*px), gy+gh+font.pointSize() * 3),
                          QString("%1").arg(minValueX + dvx*px));
    for (int py=0; py <= gridNumY; py++) // Y axis
        painter->drawText(QPoint(gx-(font.pointSize()*4), gy+static_cast<int>(dy*py)+font.pointSize()/2),
                          QString("%1").arg(maxValueY - dvy*py));
}

void Chart::drawLinearData(QPainter *painter)
{
    dx=gw/static_cast<double>(dataSize-1);
    dy=gh/2.0;
    gmy=gy+(gh/2);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(plotColor);
    pen.setWidth(2);
    painter->setPen(pen);
    for(uint i=1; i<dataSize; i++)
        painter->drawLine(QLineF(gx+(i-1)*dx, gmy-(data[i-1]*dy), gx+i*dx, gmy-(data[i]*dy)));
}

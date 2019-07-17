#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QPointF>
#include <QSizeF>

class GraphWindow
{
public:
    GraphWindow(double width, double height);

    double totalWidth() const;
    double totalHeight() const;
    QSizeF totalSize() const;

    QPointF borderPosition() const;
    QSizeF borderSize() const;

    QPointF xAxisMarginStartPoint(const double value) const;
    QPointF xAxisMarginEndPoint(const double value) const;
    QPointF xAxisTextPoint(const double value) const;
    QPointF yAxisMarginStartPoint(const double value) const;
    QPointF yAxisMarginEndPoint(const double value) const;
    QPointF yAxisTextPoint(const double value) const;


private:
    double m_graphWidth;
    double m_graphHeight;
    const double m_xBorderPadding = 5.0;
    const double m_yBorderPadding = 5.0;
    const double m_xAxisPadding = 10.0;
    const double m_yAxisPadding = 20.0;
};

#endif // GRAPHWINDOW_H

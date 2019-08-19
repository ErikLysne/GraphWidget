#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

/*
 * Helper class to map points from within the widget to the
 * global co-ordinate system.
 *
 */

#include <QPointF>
#include <QSizeF>

#include "graphthemes.h"

class GraphWindow
{
public:
    GraphWindow(double width, double height, BasicTheme* theme);

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
    QPointF yAxisTextPoint(const double value, const int pixelShift = 0) const;

    void setTheme(BasicTheme* theme);
    void setYAxisPadding(int padding);

private:
    double m_graphWidth;
    double m_graphHeight;

    BasicTheme* m_theme;

    double m_xAxisPadding;
    double m_yAxisPadding;

    const double m_xBorderPadding = 10.0;
    const double m_yBorderPadding = 10.0;
};

#endif // GRAPHWINDOW_H

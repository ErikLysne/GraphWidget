#include "graphwindow.h"

GraphWindow::GraphWindow(double width, double height, BasicTheme* theme)
    : m_graphWidth(width)
    , m_graphHeight(height)
    , m_theme(theme)
    , m_xAxisPadding(1.25*theme->labelFontSize())
    , m_yAxisPadding(1.1*theme->labelFontSize())
{

}

double GraphWindow::totalWidth() const
{
    return  m_graphWidth +
            2*m_xBorderPadding +
            m_yAxisPadding;
}

double GraphWindow::totalHeight() const
{
    return  m_graphHeight +
            2*m_yBorderPadding +
            m_xAxisPadding;
}

QSizeF GraphWindow::totalSize() const
{
    return QSizeF(totalWidth(), totalHeight());
}

QPointF GraphWindow::borderPosition() const
{
    return QPointF(m_xBorderPadding + m_yAxisPadding,
                   m_yBorderPadding);
}

QSizeF GraphWindow::borderSize() const
{
    return QSizeF(m_graphWidth, m_graphHeight);
}

QPointF GraphWindow::xAxisMarginStartPoint(const double value) const
{
    QPointF position = borderPosition();
    QSizeF size = borderSize();

    return QPointF(position.x() + value,
                   position.y() + size.height());
}

QPointF GraphWindow::xAxisMarginEndPoint(const double value) const
{
    QPointF position = borderPosition();
    QSizeF size = borderSize();

    return QPointF(position.x() + value,
                   position.y() + size.height() + m_xBorderPadding);
}

QPointF GraphWindow::xAxisTextPoint(const double value) const
{
    QPointF xMarginEndPoint = xAxisMarginEndPoint(value);

    return QPointF(xMarginEndPoint.x() - m_xAxisPadding,
                   xMarginEndPoint.y() + m_xAxisPadding);
}

QPointF GraphWindow::yAxisMarginStartPoint(const double value) const
{
    QPointF position = borderPosition();
    QSizeF size = borderSize();

    return QPointF(position.x(),
                   position.y() + size.height() - value);
}

QPointF GraphWindow::yAxisMarginEndPoint(const double value) const
{
    QPointF position = borderPosition();
    QSizeF size = borderSize();

    return QPointF(position.x() - m_yBorderPadding,
                   position.y() + size.height() - value);
}

QPointF GraphWindow::yAxisTextPoint(const double value, const int pixelShift) const
{
    int labelFontSize = m_theme->labelFontSize();
    QPointF yMarginEndPoint = yAxisMarginEndPoint(value);

    return QPointF(yMarginEndPoint.x() - m_yAxisPadding + pixelShift,
                   yMarginEndPoint.y() + 0.5*labelFontSize);
}

void GraphWindow::setTheme(BasicTheme* theme)
{
    m_theme = theme;
    m_xAxisPadding = 1.25*theme->labelFontSize();

}

void GraphWindow::setYAxisPadding(int padding)
{
    m_yAxisPadding = 1.1*padding;
}

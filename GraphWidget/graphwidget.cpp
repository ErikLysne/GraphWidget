#include "graphwidget.h"
#include <QPainter>

#include <QtDebug>

GraphWidget::GraphWidget(int width, int height, QWidget* parent)
    : QWidget(parent)
    , m_width(width)
    , m_heigth(height)
    , m_window(width, height)
    , m_style(GraphStyler::BasicTheme)
    , m_xAxis(width, 20)
    , m_yAxis(height, 10)
    , m_xDataSet()
    , m_yDataSet()
    , m_ticksMatchData(false)
    , m_xLabelSkip(2)
    , m_yLabelSkip(2)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(false);
}

void GraphWidget::addData(double xData, double yData)
{
    m_xDataSet.addData(xData);
    m_yDataSet.addData(yData);
    update();
}

void GraphWidget::setSampleBufferSize(const int size)
{
    m_xDataSet.setMaxSize(size);
    m_yDataSet.setMaxSize(size);
    update();
}

void GraphWidget::setTheme(const GraphStyler::GraphThemeSelection theme)
{
    m_style.setTheme(theme);
    update();
}

void GraphWidget::setXTicks(const int ticks)
{
    m_xAxis.setTicks(ticks);
    update();
}

void GraphWidget::setYTicks(const int ticks)
{
    m_yAxis.setTicks(ticks);
    update();
}

void GraphWidget::setTicksToMatchData(const bool match)
{
    m_ticksMatchData = match;
    update();
}

QSize GraphWidget::minimumSizeHint() const
{
    return m_window.totalSize().toSize();
}

QSize GraphWidget::sizeHint() const
{
    return m_window.totalSize().toSize();
}

void GraphWidget::paintEvent(QPaintEvent* /*event*/)
{

    QPainter painter(this);

    drawBackground(painter);
    drawGrid(painter);
    drawBorder(painter);
    drawXAxis(painter);
    drawYAxis(painter);
    drawXLabels(painter);
    drawYLabels(painter);
    drawGraph(painter);

}

void GraphWidget::drawBackground(QPainter& painter)
{
    m_style.backgroundStyle(painter);

    QPointF borderPosition = m_window.borderPosition();
    QSizeF borderSize = m_window.borderSize();
    QRectF background(borderPosition, borderSize);

    QPainterPath path;
    path.addRect(background);

    painter.fillPath(path, m_style.backgroundColor());
}

void GraphWidget::drawGrid(QPainter& painter)
{
    m_style.gridStyle(painter);

    double borderTopYVal = m_window.borderPosition().y();

    for (auto value : m_xAxis.values()) {
        QPointF topPoint = QPointF(m_window.xAxisMarginStartPoint(value).x(),
                                   borderTopYVal);
        QPointF endPoint = m_window.xAxisMarginStartPoint(value);

        painter.drawLine(topPoint, endPoint);
    }

    double borderRightXVal = m_window.borderPosition().x() + m_window.borderSize().width();

    for (auto value : m_yAxis.values()) {
        QPointF leftPoint = m_window.yAxisMarginStartPoint(value);
        QPointF rightPoint = QPointF(borderRightXVal,
                                   m_window.yAxisMarginStartPoint(value).y());

        painter.drawLine(leftPoint, rightPoint);
    }
}

void GraphWidget::drawBorder(QPainter& painter)
{
    m_style.borderStyle(painter);

    QPointF borderPosition = m_window.borderPosition();
    QSizeF borderSize = m_window.borderSize();

    QRectF border(borderPosition, borderSize);
    painter.drawRect(border);
}

void GraphWidget::drawXAxis(QPainter& painter)
{
    m_style.axisStyle(painter);

    if (m_ticksMatchData)
        setXTicks(m_xDataSet.size());

    for(auto value : m_xAxis.values())
    {
        QPointF startPoint = m_window.xAxisMarginStartPoint(value);
        QPointF endPoint = m_window.xAxisMarginEndPoint(value);

        painter.drawLine(QLineF(startPoint, endPoint));
    }
}

void GraphWidget::drawYAxis(QPainter& painter)
{
    m_style.axisStyle(painter);

    for(auto value : m_yAxis.values())
    {
        QPointF startPoint = m_window.yAxisMarginStartPoint(value);
        QPointF endPoint = m_window.yAxisMarginEndPoint(value);

        painter.drawLine(QLineF(startPoint, endPoint));
    }
}

void GraphWidget::drawXLabels(QPainter& painter)
{
    m_style.labelStyle(painter);

    int labelCount = 0;
    for(auto value : m_xAxis.values())
    {
        if (++labelCount % m_xLabelSkip) {
            QPointF textPoint = m_window.xAxisTextPoint(value);
            std::pair<double, double> dataRange = m_xDataSet.range();

            QString label = QString::number(m_xAxis.fitAxisValueToRange(value, dataRange),
                                            'g', 3);
            painter.drawText(textPoint, label);
        }
    }
}

void GraphWidget::drawYLabels(QPainter& painter)
{
    m_style.labelStyle(painter);

    int labelCount = 0;
    for(auto value : m_yAxis.values())
    {
        if (++labelCount % m_yLabelSkip) {
            QPointF textPoint = m_window.yAxisTextPoint(value);
            std::pair<double, double> dataRange = m_yDataSet.range();

            QString label = QString::number(m_yAxis.fitAxisValueToRange(value, dataRange),
                                            'g', 3);
            painter.drawText(textPoint, label);
        }
    }
}

void GraphWidget::drawGraph(QPainter& painter)
{
    QPointF precedingPoint;
    for(int i = 0; i < m_yDataSet.size(); i++)
    {
        double yValue = m_yDataSet[i];
        double xValue = m_xDataSet[i];

        std::pair<double, double> yDataRange = m_yDataSet.range();
        std::pair<double, double> xDataRange = m_xDataSet.range();

        double y = m_yAxis.fitRangeValueToAxis(yValue, yDataRange);
        double x = m_xAxis.fitRangeValueToAxis(xValue, xDataRange);

        QPointF borderPosition = m_window.borderPosition();
        QSizeF borderSize = m_window.borderSize();
        QPointF graphPoint(borderPosition.x() + x,
                          borderPosition.y() + borderSize.height() - y);

        m_style.graphMarkerStyle(painter);
        painter.drawPoint(graphPoint);

        if (i > 0) {
            m_style.graphLineStyle(painter);
            painter.drawLine(precedingPoint, graphPoint);
        }

        precedingPoint = graphPoint;
    }
}

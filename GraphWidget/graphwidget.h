#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

#include "graphwindow.h"
#include "graphaxis.h"
#include "graphdataset.h"
#include "graphstyler.h"

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(int width = 400, int height = 200, QWidget* parent = nullptr);

    void addData(double xData, double yData);
    void setSampleBufferSize(const int size);

    void setTheme(const GraphStyler::GraphThemeSelection theme);

    void setXTicks(const int ticks);
    void setYTicks(const int ticks);
    void setTicksToMatchData(const bool match = true);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawBackground(QPainter& painter);
    void drawGrid(QPainter& painter);
    void drawBorder(QPainter& painter);
    void drawXAxis(QPainter& painter);
    void drawYAxis(QPainter& painter);
    void drawXLabels(QPainter& painter);
    void drawYLabels(QPainter& painter);
    void drawGraph(QPainter& painter);

private:
    int m_width;
    int m_heigth;

    GraphWindow m_window;
    GraphStyler m_style;
    GraphAxis m_xAxis;
    GraphAxis m_yAxis;
    GraphDataSet m_xDataSet;
    GraphDataSet m_yDataSet;

    bool m_ticksMatchData;
    int m_xLabelSkip;
    int m_yLabelSkip;
};

#endif // GRAPHWIDGET_H

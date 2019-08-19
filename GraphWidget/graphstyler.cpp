#include "graphstyler.h"

GraphStyler::GraphStyler(BasicTheme* theme)
    : m_theme(new BasicTheme)
{
    if (dynamic_cast<BasicTheme*>(theme) != nullptr)
        setTheme(theme);
}

void GraphStyler::setTheme(BasicTheme* theme)
{
    if (m_theme != nullptr)
        delete m_theme;

    m_theme = theme;
}

BasicTheme* GraphStyler::getTheme()
{
    return m_theme;
}

void GraphStyler::backgroundStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->backgroundColor());
    pen.setWidth(1);
    painter.setPen(pen);
}

QColor GraphStyler::backgroundColor() const
{
    return m_theme->backgroundColor();
}

void GraphStyler::gridStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->gridColor());
    pen.setWidth(m_theme->gridThickness());
    painter.setPen(pen);
}

void GraphStyler::borderStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->borderColor());
    pen.setWidth(m_theme->borderThickness());
    painter.setPen(pen);
}

void GraphStyler::axisStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->axisColor());
    pen.setWidth(m_theme->axisThickness());
    painter.setPen(pen);
}

void GraphStyler::labelStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->labelColor());
    painter.setPen(pen);

    QFont font(m_theme->labelFontName(),
               m_theme->labelFontSize());
    painter.setFont(font);
}

void GraphStyler::graphMarkerStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->graphMarkerColor());
    pen.setWidth(m_theme->graphMarkerSize());
    painter.setPen(pen);
}

void GraphStyler::graphLineStyle(QPainter& painter) const
{
    QPen pen;
    pen.setColor(m_theme->graphLineColor());
    pen.setWidth(m_theme->graphLineThickness());
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
}

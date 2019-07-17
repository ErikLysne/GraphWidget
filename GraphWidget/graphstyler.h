#ifndef GRAPHSTYLER_H
#define GRAPHSTYLER_H

#include <QPainter>

#include "graphthemes.h"

class GraphStyler
{
public:
    enum GraphThemeSelection {
        BasicTheme,
        DarkTheme
    };

public:
    GraphStyler(const GraphThemeSelection theme = BasicTheme);

    void setTheme(const GraphThemeSelection theme);

    void backgroundStyle(QPainter& painter) const;
    QColor backgroundColor() const;
    void gridStyle(QPainter& painter) const;
    void borderStyle(QPainter& painter) const;
    void axisStyle(QPainter& painter) const;
    void labelStyle(QPainter& painter) const;
    void graphMarkerStyle(QPainter& painter) const;
    void graphLineStyle(QPainter& painter) const;

private:
    GraphAbstractTheme* m_theme;

};

#endif // GRAPHSTYLER_H

#ifndef GRAPHABSTRACTTHEME_H
#define GRAPHABSTRACTTHEME_H

#include <QColor>

class GraphAbstractTheme
{
public:
    GraphAbstractTheme();
    virtual ~GraphAbstractTheme();

    virtual QColor  backgroundColor()   const = 0;
    virtual QColor  gridColor()         const = 0;
    virtual int     gridThickness()     const = 0;
    virtual QColor  borderColor()       const = 0;
    virtual int     borderThickness()   const = 0;
    virtual QColor  axisColor()         const = 0;
    virtual int     axisThickness()     const = 0;
    virtual QColor  labelColor()        const = 0;
    virtual int     labelFontSize()     const = 0;
    virtual QString labelFontName()     const = 0;
    virtual QColor  graphMarkerColor()  const = 0;
    virtual int     graphMarkerSize()   const = 0;
    virtual QColor  graphLineColor()    const = 0;
    virtual int     graphLineThickness()const = 0;

protected:
    const QColor transparent    = QColor(0, 0, 0, 0);
    const QColor black          = QColor(0, 0, 0);
    const QColor gray           = QColor(100, 100, 100);
    const QColor red            = QColor(255, 0, 0);
    const QColor darkGreen      = QColor(80, 100, 80);
    const QColor teal           = QColor(85, 255, 255);
};

#endif // GRAPHABSTRACTTHEME_H

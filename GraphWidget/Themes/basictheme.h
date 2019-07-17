#ifndef BASICTHEME_H
#define BASICTHEME_H

#include "graphabstracttheme.h"

class BasicTheme : public GraphAbstractTheme
{
public:
    BasicTheme();
    ~BasicTheme() override;

    QColor  backgroundColor()   const override {return transparent;}
    QColor  gridColor()         const override {return gray;}
    int     gridThickness()     const override {return 1;}
    QColor  borderColor()       const override {return black;}
    int     borderThickness()   const override {return 2;}
    QColor  axisColor()         const override {return black;}
    int     axisThickness()     const override {return 2;}
    QColor  labelColor()        const override {return black;}
    int     labelFontSize()     const override {return 10;}
    QString labelFontName()     const override {return "Areal";}
    QColor  graphMarkerColor()  const override {return red;}
    int     graphMarkerSize()   const override {return 3;}
    QColor  graphLineColor()    const override {return red;}
    int     graphLineThickness()const override {return 1;}
};

#endif // BASICTHEME_H

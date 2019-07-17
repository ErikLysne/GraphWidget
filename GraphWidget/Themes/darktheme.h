#ifndef DARKTHEME_H
#define DARKTHEME_H

#include "graphabstracttheme.h"

class DarkTheme : public GraphAbstractTheme
{
public:
    DarkTheme();
    ~DarkTheme() override;

    QColor  backgroundColor()   const override {return black;}
    QColor  gridColor()         const override {return darkGreen;}
    int     gridThickness()     const override {return 1;}
    QColor  borderColor()       const override {return black;}
    int     borderThickness()   const override {return 2;}
    QColor  axisColor()         const override {return black;}
    int     axisThickness()     const override {return 2;}
    QColor  labelColor()        const override {return black;}
    int     labelFontSize()     const override {return 10;}
    QString labelFontName()     const override {return "Areal";}
    QColor  graphMarkerColor()  const override {return teal;}
    int     graphMarkerSize()   const override {return 3;}
    QColor  graphLineColor()    const override {return teal;}
    int     graphLineThickness()const override {return 1;}
};

#endif // DARKTHEME_H

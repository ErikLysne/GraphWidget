#ifndef GRAPHAXIS_H
#define GRAPHAXIS_H

#include <QVector>

class GraphAxis
{
public:
    GraphAxis(int length, int ticks);

    QVector<double> values();
    double fitAxisValueToRange(double value, std::pair<double, double> range);
    double fitRangeValueToAxis(double value, std::pair<double, double> range);

    void setLength(const int length);
    void setTicks(const int ticks);
    int getLength() const;
    int getTicks() const;

private:
    int m_length;
    int m_ticks;
};

#endif // GRAPHAXIS_H

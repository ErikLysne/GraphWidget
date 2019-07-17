#include "graphaxis.h"

GraphAxis::GraphAxis(int length, int ticks)
    : m_length(length)
    , m_ticks(ticks)
{

}

QVector<double> GraphAxis::values()
{
    double tickSpacing = static_cast<double>(m_length)/static_cast<double>(m_ticks);
    QVector<double> values;

    double axisValue = 0;
    for (int i = 0; i < m_ticks + 1; i++) {
        values.push_back(axisValue);
        axisValue += tickSpacing;
    }

    return values;
}

double GraphAxis::fitAxisValueToRange(double value, std::pair<double, double> range)
{
    double minValue = range.first;
    double maxValue = range.second;
    double valueRange = maxValue - minValue;

    double returnValue = minValue + (valueRange)*(value/m_length);

    if (returnValue > maxValue)
        return maxValue;

    if (returnValue < minValue)
        return minValue;

    return returnValue;
}

double GraphAxis::fitRangeValueToAxis(double value, std::pair<double, double> range)
{
    double minValue = range.first;
    double maxValue = range.second;
    double valueRange = maxValue - minValue;

    double returnValue = m_length*((value - minValue)/valueRange);

    if (returnValue > m_length)
        return m_length;

    if (returnValue < 0)
        return 0;

    return returnValue;
}

void GraphAxis::setLength(const int length)
{
    m_length = length;
}

void GraphAxis::setTicks(const int ticks)
{
    m_ticks = ticks;
}

int GraphAxis::getLength() const
{
    return m_length;
}

int GraphAxis::getTicks() const
{
    return m_ticks;
}

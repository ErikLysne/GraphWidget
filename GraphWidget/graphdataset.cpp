#include "graphdataset.h"
#include <vector>
#include <algorithm>

GraphDataSet::GraphDataSet()
    : m_maxValue(0)
    , m_minValue(0)
    , m_data()
    , m_maxDataPoints(100)
{

}

void GraphDataSet::addData(double data)
{
    if (m_data.empty()) {
        m_maxValue = data;
        m_minValue = data;
    }
    else {
        if (data > m_maxValue)
            m_maxValue = data;

        if (data < m_minValue)
            m_minValue = data;
    }

    m_data.push_back(data);

    if (m_data.size() > m_maxDataPoints) {
        double removedValue = *m_data.begin();
        m_data.erase(m_data.begin());

        if (removedValue >= m_maxValue)
            m_maxValue = *std::max_element(m_data.begin(), m_data.end());
        else if (removedValue <= m_minValue)
            m_minValue = *std::min_element(m_data.begin(), m_data.end());
    }
}

std::vector<double> GraphDataSet::data() const
{
    return m_data;
}

std::pair<double, double> GraphDataSet::range() const
{
    return std::make_pair(m_minValue, m_maxValue);
}

int GraphDataSet::size() const
{
    return static_cast<int>(m_data.size());
}

void GraphDataSet::setMaxSize(const int maxSize)
{
    m_maxDataPoints = static_cast<std::size_t>(maxSize);

    int excessData = static_cast<int>(m_data.size()) - maxSize;

    if (excessData > 0) {
        for (int i = 0; i < excessData; i++) {
            m_data.pop_back();
        }

        m_maxValue = *std::max_element(m_data.begin(), m_data.end());
        m_minValue = *std::min_element(m_data.begin(), m_data.end());
    }
}

double GraphDataSet::operator[](int id) const
{
    std::size_t idVect = static_cast<std::size_t>(id);
    if (idVect < m_data.size())
        return m_data[idVect];
    else
        return 0;
}

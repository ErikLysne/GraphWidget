#ifndef GRAPHDATASET_H
#define GRAPHDATASET_H

#include <vector>

class GraphDataSet
{
public:
    GraphDataSet();

    void addData(const double data);
    std::vector<double> data() const;
    std::pair<double, double> range() const;
    int size() const;
    void setMaxSize(const int maxSize);

    double operator[](int id) const;

private:
    double m_maxValue;
    double m_minValue;

    std::vector<double> m_data;
    std::size_t m_maxDataPoints;

};

#endif // GRAPHDATASET_H

#ifndef NEAREST_NEIGHBOR_CLASSIFIER_H
#define NEAREST_NEIGHBOR_CLASSIFIER_H

#include "Point.h"
#include <vector>

class NNC {
private:
    std::vector<Point> trainingData;

public:
    void Train(const std::vector<Point>& data);
    int Test(const Point& testInstance);

private:
    double euclDistance(const std::vector<double>& a, const std::vector<double>& b);
};

#endif // NNC_H

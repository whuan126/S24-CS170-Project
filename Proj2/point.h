#ifndef POINT_H
#define POINT_H

#include <vector>

class Point {
public:
    std::vector<double> features;
    int label;

    Point(std::vector<double> features, int label);
};

#endif // POINT_H

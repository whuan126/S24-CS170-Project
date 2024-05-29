#ifndef LOOV_H
#define LOOV_H

#include "point.h"
#include "NNC.h"
#include <vector>

class LOOV {
public:
    double Validate(NNC& classifier, const std::vector<Point>& data, const std::vector<int>& featureSubset);

private:
    std::vector<double> ExtractFeatures(const std::vector<double>& features, const std::vector<int>& featureSubset);
};

#endif // LOOV_H

#include "NNC.h"
#include <cmath>
#include <limits>

// Storing the training data
void NNC::Train(const std::vector<Point>& data) {
    trainingData = data;
}

// Finds nearest neighbor and returns label
int NNC::Test(const Point& testInstance) {
    double minDistance = std::numeric_limits<double>::max();
    int nearestLabel = -1;

    for (const auto& instance : trainingData) {
        double distance = euclDistance(instance.features, testInstance.features);
        if (distance < minDistance) {
            minDistance = distance;
            nearestLabel = instance.label;
        }
    }

    return nearestLabel;
}

// Calculate euclidean distance
double NNC::euclDistance(const std::vector<double>& a, const std::vector<double>& b) {
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += std::pow(a[i] - b[i], 2);
    }
    return std::sqrt(sum);
}

#include "LOOV.h"

double LOOV::Validate(NNC& classifier, const std::vector<Point>& data, const std::vector<int>& featureSubset) {
    int correctCount = 0;

    for (std::size_t i = 0; i < data.size(); ++i) {
        std::vector<Point> trainingSet = data;  // Load all data points
        Point testInstance = data[i];           
        trainingSet.erase(trainingSet.begin() + i); // Remove test instance after

        // // Extract features for training set
        for (auto&point: trainingSet) {
            point.features = ExtractFeatures(point.features, featureSubset);
        }

        NNC tempClassifier;
        tempClassifier.Train(trainingSet);

        std::vector<double> testFeatures = ExtractFeatures(testInstance.features, featureSubset);
        Point testPoint(testFeatures, testInstance.label);
        int predictedLabel = tempClassifier.Test(testPoint);

        if (predictedLabel == testInstance.label) {
            ++correctCount;
        }
    }

    return static_cast<double>(correctCount) / data.size();
}

std::vector<double> LOOV::ExtractFeatures(const std::vector<double>& features, const std::vector<int>& featureSubset) {
    std::vector<double> subset;
    for (int index : featureSubset) {
        subset.push_back(features[index]);
    }
    return subset;
}

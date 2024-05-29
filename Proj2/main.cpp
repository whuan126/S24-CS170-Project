#include "Point.h"
#include "NNC.h"
#include "LOOV.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <chrono>

// Function to load provided datasets.
std::vector<Point> LoadDataset(const std::string& filename);

// Function to normalize provided dataset
void normalize(std::vector<Point>& dataset);

// Driver code
int main() {
    std::vector<Point> smallDataset = LoadDataset("datasets/small-test-dataset-1.txt");
    std::vector<Point> largeDataset = LoadDataset("datasets/large-test-dataset-1.txt");
    
    // Normalize the datasets
    normalize(smallDataset);
    normalize(largeDataset);

    NNC classifier;
    LOOV validator;

    std::vector<int> smallFeatureSubset = {3, 5, 7}; // Hard coding for features {3, 5, 7}
    auto start = std::chrono::high_resolution_clock::now();
    double smallAccuracy = validator.Validate(classifier, smallDataset, smallFeatureSubset);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_small = end - start;
    std::cout << "Time taken for small dataset: " << time_small.count() << " seconds" << std::endl;
    std::cout << "Small Dataset Accuracy: " << smallAccuracy << std::endl;

    std::vector<int> largeFeatureSubset = {1, 15, 27}; // Hard coding for features {1, 15, 27}
    start = std::chrono::high_resolution_clock::now();
    double largeAccuracy = validator.Validate(classifier, largeDataset, largeFeatureSubset);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_large = end - start;
    std::cout << "Time taken for large dataset: " << time_large.count() << " seconds" << std::endl;
    std::cout << "Large Dataset Accuracy: " << largeAccuracy << std::endl;

    return 0;
}

std::vector<Point> LoadDataset(const std::string& filename) {
    std::vector<Point> dataset;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int label;
            iss >> label;
            std::vector<double> features;
            double feature;
            while (iss >> feature) {
                features.push_back(feature);
            }
            dataset.emplace_back(features, label);
        }
        file.close();
    }
    return dataset;
}

void normalize(std::vector<Point> &dataset) {
    if (dataset.empty()) {
        std::cout << "Dataset is empty" << std::endl;
        return;
    }

    size_t featureCount = dataset[0].features.size();
    std::vector<double> minValues(featureCount, std::numeric_limits<double>::max());
    std::vector<double> maxValues(featureCount, std::numeric_limits<double>::lowest());

    // Find min and max values for each feature
    for (const auto& point : dataset) {
        for (size_t i = 0; i < featureCount; ++i) {
            if (point.features[i] < minValues[i]) minValues[i] = point.features[i];
            if (point.features[i] > maxValues[i]) maxValues[i] = point.features[i];
        }
    }

    // Normalize features to range [0, 1]
    for (auto& point : dataset) {
        for (size_t i = 0; i < featureCount; ++i) {
            if (maxValues[i] != minValues[i]) {
                point.features[i] = (point.features[i] - minValues[i]) / (maxValues[i] - minValues[i]);
            } else {
                point.features[i] = 0.0;
            }
        }
    }
}
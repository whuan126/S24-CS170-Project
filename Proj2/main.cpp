#include "Point.h"
#include "NNC.h"
#include "LOOV.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <chrono>
#include <cstdlib>
#include <algorithm>

// Function to load provided datasets.
std::vector<Point> LoadDataset(const std::string& filename);

// Function to normalize provided dataset
void normalize(std::vector<Point>& dataset);

// Helper function to convert vector<int> to string
std::string to_string(const std::vector<int>& vec) {
    std::string result = "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        result += std::to_string(vec[i]);
        if (i < vec.size() - 1) result += ",";
    }
    result += "}";
    return result;
}


// Evaluation function using Leave-One-Out Validation
double evaluateFeatures(const std::vector<Point>& dataset, const std::vector<int>& featureSubset) {
    NNC classifier;
    LOOV validator;
    return validator.Validate(classifier, dataset, featureSubset);
}

// Backward elimination function
std::vector<int> backwardElimination(const std::vector<Point>& dataset, int totalFeatures) {

    std::vector<int> currentFeatures;
    for (int i = 1; i <= totalFeatures; ++i) {
        currentFeatures.push_back(i);
    }

    float bestAccuracy = evaluateFeatures(dataset, currentFeatures); // Initial evaluation with all features

    std::cout << "Using all features " << to_string(currentFeatures) << ", initial accuracy is " << bestAccuracy << "%\n";

    while (currentFeatures.size() > 1) {
        int bestFeatureToRemove = -1;
        float bestTempAccuracy = 0.0;

        for (size_t i = 0; i < currentFeatures.size(); ++i) {
            std::vector<int> tempFeatures = currentFeatures;
            tempFeatures.erase(tempFeatures.begin() + i);

            float tempAccuracy = evaluateFeatures(dataset, tempFeatures);

            std::cout << "Using feature(s) " << to_string(tempFeatures) << " accuracy is " << tempAccuracy << "%\n";

            if (tempAccuracy > bestTempAccuracy) {
                bestTempAccuracy = tempAccuracy;
                bestFeatureToRemove = i;
            }
        }

        if (bestFeatureToRemove != -1 && bestTempAccuracy >= bestAccuracy) {
            currentFeatures.erase(currentFeatures.begin() + bestFeatureToRemove);
            bestAccuracy = bestTempAccuracy;
            std::cout << "Feature set " << to_string(currentFeatures) << " was best, accuracy is " << bestAccuracy << "%\n";
        } else {
            break;
        }
    }

    std::cout << "Finished search!! The best feature subset is " << to_string(currentFeatures) << ", which has an accuracy of " << bestAccuracy << "%\n";
    return currentFeatures;
}

std::vector<int> forwardSelection(const std::vector<Point>& dataset, int totalFeatures) {
    std::vector<int> currentFeatures;
    float bestAccuracy = 0.0;

    std::cout << "Beginning forward selection search." << std::endl;

    for (int i = 0; i < totalFeatures; ++i) {
        int bestFeature = -1;
        float bestTempAccuracy = 0.0;

        for (int feature = 1; feature <= totalFeatures; ++feature) {
            if (std::find(currentFeatures.begin(), currentFeatures.end(), feature) == currentFeatures.end()) {
                std::vector<int> tempFeatures = currentFeatures;
                tempFeatures.push_back(feature);

                float tempAccuracy = evaluateFeatures(dataset, tempFeatures);
                std::cout << "Using feature(s) " << to_string(tempFeatures) << " accuracy is " << tempAccuracy << "%" << std::endl;

                if (tempAccuracy > bestTempAccuracy) {
                    bestTempAccuracy = tempAccuracy;
                    bestFeature = feature;
                }
            }
        }

        if (bestFeature != -1) {
            currentFeatures.push_back(bestFeature);
            bestAccuracy = bestTempAccuracy;
            std::cout << "Feature set " << to_string(currentFeatures) << " was best, accuracy is " << bestAccuracy << "%" << std::endl;
        } else {
            break;
        }
    }

    std::cout << "Finished search!! The best feature subset is " << to_string(currentFeatures) << ", which has an accuracy of " << bestAccuracy << "%" << std::endl;
    return currentFeatures;
}

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

    int totalFeatures;
    std::cout << "Please enter total number of features: ";
    std::cin >> totalFeatures;

    std::cout << "Type the number of the algorithm you want to run:\n";
    std::cout << "1. Forward Selection\n";
    std::cout << "2. Backward Elimination\n";
    std::cout << "3. Exit\n";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        forwardSelection(smallDataset, totalFeatures);
    } else if (choice == 2) {
        backwardElimination(largeDataset, totalFeatures);
    } else if (choice == 3) {
        // Exit the program
    } else {
        std::cout << "Invalid choice, please try again.\n";
    }

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

void normalize(std::vector<Point>& dataset) {
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

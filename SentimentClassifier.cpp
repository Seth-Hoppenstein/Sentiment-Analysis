#include "SentimentClassifier.h"
#include <fstream>
#include <sstream>
#include <iostream>

void SentimentClassifier::train(const DSString& trainingFile) {
    std::ifstream file(trainingFile.c_str());
    if (!file) {
        std::cerr << "Failed to open training file." << std::endl;
        return;
    }

    int sentiment;
    DSString tweet;
    while (file >> sentiment) {
        // Skip ID, date, and other columns
        file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        file.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        
        // Read the tweet text
        std::getline(file, tweet, '"');
        std::getline(file, tweet.c_str()[0], '"'); // Read the tweet itself

        std::istringstream iss(tweet.c_str());
        DSString word;
        while (iss >> word) {
            if (sentiment == 4) {
                positiveWords[word]++;
            } else if (sentiment == 0) {
                negativeWords[word]++;
            }
        }
    }
}

int SentimentClassifier::predict(const DSString& tweet) {
    int posCount = 0, negCount = 0;
    std::istringstream iss(tweet.c_str());
    DSString word;
    
    while (iss >> word) {
        posCount += positiveWords[word];
        negCount += negativeWords[word];
    }
    
    return posCount > negCount ? 4 : 0; // Predict positive if more positive words
}

void SentimentClassifier::evaluate(const DSString& testingFile,
                                    const DSString& groundTruthFile,
                                    const DSString& resultsFile,
                                    const DSString& accuracyFile) {
    std::ifstream testFile(testingFile.c_str());
    std::ifstream truthFile(groundTruthFile.c_str());
    std::ofstream resultFile(resultsFile.c_str());
    std::ofstream accFile(accuracyFile.c_str());
    
    int correct = 0, total = 0, id, sentiment;

    while (testFile >> id) {
        testFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        testFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        testFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
        testFile.ignore(std::numeric_limits<std::streamsize>::max(), ',');

        DSString tweet;
        std::getline(testFile, tweet.c_str()[0], '"');
        std::getline(testFile, tweet.c_str()[0], '"'); // Read the tweet itself

        int predicted = predict(tweet);
        resultFile << predicted << ", " << id << std::endl;

        truthFile >> sentiment;
        if (sentiment == predicted) {
            correct++;
        }
        total++;
    }

    double accuracy = static_cast<double>(correct) / total;
    accFile << std::fixed << std::setprecision(3) << accuracy << std::endl;
}


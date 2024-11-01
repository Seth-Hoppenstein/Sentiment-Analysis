#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include "DSString.h"
#include <vector>
#include <unordered_map>

class SentimentClassifier {
private:
    std::unordered_map<DSString, int> positiveWords;
    std::unordered_map<DSString, int> negativeWords;

public:
    void train(const DSString& trainingFile);
    int predict(const DSString& tweet);
    void evaluate(const DSString& testingFile, const DSString& groundTruthFile,
                  const DSString& resultsFile, const DSString& accuracyFile);
};

#endif // SENTIMENTCLASSIFIER_H

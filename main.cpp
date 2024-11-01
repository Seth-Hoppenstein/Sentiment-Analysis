#include "SentimentClassifier.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " training_file testing_file ground_truth_file results_file accuracy_file" << std::endl;
        return 1;
    }

    SentimentClassifier classifier;
    classifier.train(DSString(argv[1]));
    classifier.evaluate(DSString(argv[2]), DSString(argv[3]), DSString(argv[4]), DSString(argv[5]));

    return 0;
}

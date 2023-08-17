// Copyright 2023 William Susi

#include "RandWriter.hpp"

int main(int argc, char** argv) {
    int kGramLen = std::stod(argv[1]);
    int numChar = std::stod(argv[2]);

    string text;
    string line;
    while (getline(cin, line)) {
        text += line;
    }

    RandWriter randText(text, kGramLen);

    cout << randText.generate(text.substr(0, randText.orderK()), numChar) << endl;

    return 0;
}

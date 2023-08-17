// Copyright 2023 William Susi

#include "RandWriter.hpp"

RandWriter::RandWriter(string text, int k) : _orderK(k), _alphabet("abcdefghijklmnopqrstuvwxyz") {
    text += text.substr(0, _orderK);
    for (size_t i = 0; i < text.size() - _orderK; i++) {
        string kgram1 = text.substr(i, _orderK);
        string kgram2 = text.substr(i, _orderK + 1);
        _kGrams[kgram1]++;
        _kPlusGrams[kgram2]++;
    }

    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 num(seed);
    _randNum = num;
}

// Returns the order
int RandWriter::orderK() const {
    return _orderK;
}

// Checks if a kgram matches the order size
void RandWriter::isRightSize(string kgram) const {
    if (static_cast<int>(kgram.size()) != _orderK) {
        throw std::runtime_error("kgram is not the correct length");
    }
}

// Finds the number of occurrences of a given kgram
int RandWriter::freq(string kgram) const {
    isRightSize(kgram);
    auto gram = _kGrams.find(kgram);
    if (gram == _kGrams.end()) {
        return 0;
    } else {
        return gram->second;
    }
}

// Finds the number of occurrences of a given k+1gram
int RandWriter::freq(string kgram, char c) const {
    isRightSize(kgram);
    string newGram = kgram + c;
    auto gram = _kPlusGrams.find(newGram);
    if (gram == _kPlusGrams.end()) {
        return 0;
    } else {
        return gram->second;
    }
}

// Generates a pseudo-random character based on the occurrences
// of given k+1grams in the RandWriter text.
char RandWriter::kRand(string kgram) {
    if (freq(kgram) == 0) {
        throw std::runtime_error("kgram: '" + kgram + "' does not exist");
    }

    // Create map of k+1grams that start with kgram
    unordered_map<string, int> tempGrams;
    for (auto kp1gram : _kPlusGrams) {
        auto found = (kp1gram.first).find(kgram);
        if (found == 0) {
            tempGrams.insert(kp1gram);
        }
    }

    // Count the number of total occurrences of k+1grams with kgram in them
    int totalOccurrences = 0;
    std::for_each(tempGrams.begin(), tempGrams.end(),
        [&totalOccurrences](auto& key) {
            totalOccurrences += key.second;
    });

    // Generate a random number between 0 and the number of total occurrences
    std::uniform_int_distribution<int> dist(1, totalOccurrences);
    int ranNum = dist(_randNum);

    // Use that random number to pick a random k+1gram adn grab its last letter
    int currSum = 0;
    for (auto key : tempGrams) {
        currSum += key.second;
        if (currSum >= ranNum) {
            return key.first[_orderK];
        }
    }

    throw std::runtime_error("Could not generate new char");
}

// Generates a string of length L given a starting kgram based of the RandWriter text.
string RandWriter::generate(string kgram, int L) {
    isRightSize(kgram);
    string randomText = kgram;
    string gram = kgram;
    for (int i = 0; i < L - _orderK; i++) {
        char c = kRand(gram);
        randomText += c;
        if (gram.size() != 0) {
            gram = gram.substr(1, _orderK - 1) + c;
        }
    }
    return randomText;
}

// Displays the internal state of a RandWriter object by printing out the order, alphabet,
// and the frequencies of the k-grams and k+1-grams.
ostream& operator<<(ostream& outStream, const RandWriter& randWriter) {
    outStream << "Order: " << randWriter._orderK << endl;

    outStream << "Alphabet: ";
    for (char letter : randWriter._alphabet) {
        outStream << letter << " ";
    }

    outStream << endl << "k-grams:" << endl;
    for (auto kgram : randWriter._kGrams) {
        outStream << " - " << kgram.first << ": " << kgram.second << endl;
    }

    outStream << endl << "k+1-grams:" << endl;
    for (auto kgram : randWriter._kPlusGrams) {
        outStream << " - " << kgram.first << ": " << kgram.second << endl;
    }

    return outStream;
}

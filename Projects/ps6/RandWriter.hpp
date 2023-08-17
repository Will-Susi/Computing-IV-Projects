// Copyright 2023 William Susi

#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <string>
#include <chrono>
#include <random>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::unordered_map;

class RandWriter {
 public:
    RandWriter(string text, int k);

    int orderK() const;

    void isRightSize(string kgram) const;

    int freq(string kgram) const;
    int freq(string kgram, char c) const;
    char kRand(string kgram);
    string generate(string kgram, int L);

    friend ostream& operator<<(ostream& outStream, const RandWriter& randWriter);
 private:
    int _orderK;
    unordered_map<string, int> _kGrams;
    unordered_map<string, int> _kPlusGrams;
    string _alphabet;
    std::minstd_rand0 _randNum;
};

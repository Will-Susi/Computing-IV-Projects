// Copyright 2023 William Susi

#include "EDistance.hpp"

// EDistance constructor that accepts the two strings to be compared and allocates a NxM matrix.
EDistance::EDistance(string& s1, string& s2) : _s1(s1), _s2(s2) {
    // Set up and fill matrix with placeholder value
    for (size_t i = 0; i <= s1.size(); i++) {
        _matrix.emplace_back(s2.size() + 1, -1);
    }
    // Fill in last row
    int cost = 0;
    for (auto i = _matrix.rbegin(); i != _matrix.rend(); i++) {
        i->back() = cost;
        cost += 2;
    }
    // Fill in last column
    cost = 0;
    for (auto i = _matrix.back().rbegin(); i != _matrix.back().rend(); i++) {
        *i = cost;
        cost += 2;
    }
}

// Returns the penalty between two characters
int EDistance::penalty(char a, char b) {
    return a != b;
}

// Returns the minimum of the three arguments.
int EDistance::min(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c)  {
        return b;
    }
    return c;
    // return std::min(a, std::min(b, c));
}

// Populates the matrix with the distance between two strings and returns the optimal distance.
int EDistance::optDistance() {
    for (size_t i = _s1.size() - 1; i < _s1.size(); i--) {
        for (size_t j = _s2.size() - 1; j < _s2.size(); j--) {
            _matrix.at(i).at(j) = min(_matrix.at(i + 1).at(j + 1) + penalty(_s1[i], _s2[j]),
                                     _matrix.at(i).at(j + 1) + 2,
                                          _matrix.at(i + 1).at(j) + 2);
        }
    }

    return _matrix.at(0).at(0);
}

// Traces the matrix to the optimal distance and returns that alignment.
string EDistance::alignment() {
    string path = "";
    size_t i = 0, j = 0;

    while (i < _s1.size() && j < _s2.size()) {
        if (_matrix.at(i).at(j) == _matrix.at(i + 1).at(j) + 2) {  // Gap in s2
            path = path + _s1[i] + " - 2\n";
            i++;
        } else if (_matrix.at(i).at(j) == _matrix.at(i).at(j + 1) + 2) {  // Gap in s1
            path = path + "- " + _s2[j] + " 2\n";
            j++;
        } else if (_matrix.at(i).at(j) == _matrix.at(i + 1).at(j + 1)) {  // If equal
            path = path + _s1[i] + " " + _s2[j] + " 0\n";
            i++;
            j++;
        } else if (_matrix.at(i).at(j) == _matrix.at(i + 1).at(j + 1) + 1) {  // Else
            path = path + _s1[i] + " " + _s2[j] + " 1\n";
            i++;
            j++;
        }
    }
    return path;
}

// Copyright 2023 William Susi

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using std::string;
using std::to_string;
using std::ostream;

class FibLFSR {
 public:
    explicit FibLFSR(string seed);

    string getRegister() const;

    int step();
    int generate(int k);
 private:
    string _register;
};

void transform(sf::Image&, FibLFSR*);

string generateBinarySeed(string seed);

ostream& operator<<(ostream&, const FibLFSR& lfsr);

// Copyright 2023 William Susi

#include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

class EDistance {
 public:
    EDistance(string& s1, string& s2);

    static int penalty(char a, char b);
    static int min(int a, int b, int c);

    int optDistance();
    string alignment();

 private:
    string _s1;
    string _s2;
    vector<vector<int>> _matrix;
};

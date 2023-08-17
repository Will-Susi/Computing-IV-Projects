// Copyright 2023 William Susi

#include "EDistance.hpp"

int main(int argc, char** argv) {
    sf::Clock clock;
    sf::Time time;

    string s1, s2;
    cin >> s1;
    cin >> s2;

    EDistance dna(s1, s2);

    cout << "Edit distance = " << dna.optDistance() << endl;

    cout << dna.alignment() << endl;

    // Print elapsed time
    time = clock.getElapsedTime();
    cout << "Execution time is " << time.asSeconds() << " seconds \n";

    return 0;
}

#include <iostream>
#include <string>

using namespace std;

class FibLFSR {
public:
    // Constructor to create LFSR with the given initial seed
    FibLFSR(string seed);

    // Getter function to get register
    string getRegister() const;

    // Simulate one step and return the new bit as 0 or 1
    int step();

    // Simulate k steps and return a k-bit integer
    int generate(int k);
private:
    string _register;
};

ostream& operator<<(ostream&, const FibLFSR& lfsr);
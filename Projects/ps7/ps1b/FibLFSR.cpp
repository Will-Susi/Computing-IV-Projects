// Copyright 2023 William Susi

#include <iostream>
#include <string>
#include "FibLFSR.hpp"

FibLFSR::FibLFSR(string seed) {
    _register = seed;
}

string FibLFSR::getRegister() const {
    return _register;
}

// Makes one shift on a FibLFSR object
int FibLFSR::step() {
    int resultBit = _register[5] ^ (_register[3] ^ (_register[2] ^ _register[0]));

    _register = _register.substr(1, 16);
    _register.append(to_string(resultBit));

    return resultBit;
}

// Makes k shifts on a FibLFSR object with a returned number dictated by the fall off bits
int FibLFSR::generate(int k) {
    int result = 0;
    for (int i = 0; i < k; i++) {
        result = (result * 2) + step();
    }
    return result;
}

ostream& operator<<(ostream& outStream, const FibLFSR& lfsr) {
    outStream << lfsr.getRegister();
    return outStream;
}

// Encrypts/decrypts a image given a seed.
void transform(sf::Image& img, FibLFSR* reg) {
    sf::Color pixel;
    for (unsigned int x = 0; x < img.getSize().x; x++) {
        for (unsigned int y = 0; y < img.getSize().y; y++) {
            pixel = img.getPixel(x, y);

            pixel.r = pixel.r ^ reg->generate(8);
            pixel.g = pixel.g ^ reg->generate(8);
            pixel.b = pixel.b ^ reg->generate(8);

            img.setPixel(x, y, pixel);
        }
    }
}

// Generates a pseudo-random binary seed of length 16
string generateBinarySeed(string seed) {
    string binarySeed = "";
    int size = seed.size();
    int i;
    for (i = 0; i < size && i < 16; i++) {
        if (seed[i] % 2 == 1) {
            binarySeed.append("1");
        } else {
            binarySeed.append("0");
        }
    }

    for (i = size; i < 16; i++) {
        if (i % 2 == 1) {
            binarySeed.append("1");
        } else {
            binarySeed.append("0");
        }
    }

    return binarySeed;
}

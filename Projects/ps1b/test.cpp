// Copyright 2023 William Susi

#include "FibLFSR.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(testStep) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
}

BOOST_AUTO_TEST_CASE(testGenerate1) {
    FibLFSR l2("1011011000110110");
    BOOST_REQUIRE_EQUAL(l2.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testGenerate2) {
    FibLFSR l3("1011011000110110");

    BOOST_CHECK_EQUAL(l3.generate(5), 3);
    BOOST_CHECK_EQUAL(l3.getRegister(), "1100011011000011");
    BOOST_CHECK_EQUAL(l3.generate(5), 6);
    BOOST_CHECK_EQUAL(l3.getRegister(), "1101100001100110");
    BOOST_CHECK_EQUAL(l3.generate(5), 14);
    BOOST_CHECK_EQUAL(l3.getRegister(), "0000110011001110");
    BOOST_CHECK_EQUAL(l3.generate(5), 24);
    BOOST_CHECK_EQUAL(l3.getRegister(), "1001100111011000");
    BOOST_CHECK_EQUAL(l3.generate(5), 1);
    BOOST_CHECK_EQUAL(l3.getRegister(), "0011101100000001");
    BOOST_CHECK_EQUAL(l3.generate(5), 13);
    BOOST_CHECK_EQUAL(l3.getRegister(), "0110000000101101");
    BOOST_CHECK_EQUAL(l3.generate(5), 28);
    BOOST_CHECK_EQUAL(l3.getRegister(), "0000010110111100");
}

BOOST_AUTO_TEST_CASE(testGetReg) {
    FibLFSR l4("1011011000110110");
    BOOST_CHECK_EQUAL(l4.getRegister(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testOutputOverload) {
    FibLFSR l5("1011011000110110");
    std::stringstream ss;
    ss << l5;
    BOOST_CHECK_EQUAL(ss.str(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testSeedGenDefault) {
    BOOST_CHECK_EQUAL(generateBinarySeed("0000000000000000"), "0000000000000000");
    BOOST_CHECK_EQUAL(generateBinarySeed("1111111111111111"), "1111111111111111");
    BOOST_CHECK_EQUAL(generateBinarySeed("0101001000111100"), "0101001000111100");
}

BOOST_AUTO_TEST_CASE(testSeedGenWords) {
    BOOST_CHECK_EQUAL(generateBinarySeed("RevengeOfTheSith").size(), 16);
    BOOST_CHECK_EQUAL(generateBinarySeed("RevengeOfTheSith"), "0101011100011100");
    BOOST_CHECK_EQUAL(generateBinarySeed("RevengeOfTheSith"), "0101011100011100");
}

BOOST_AUTO_TEST_CASE(testSeedGenOverflow) {
    BOOST_CHECK_EQUAL(generateBinarySeed("a7sdybj';.,234fd@$#sdaf").size(), 16);
    BOOST_CHECK_EQUAL(generateBinarySeed("a7sdybj';.,234fd@$#sdaf"), "1110100110001000");
    BOOST_CHECK_EQUAL(generateBinarySeed("a7sdybj';.,234fd"), "1110100110001000");
    BOOST_CHECK_EQUAL(generateBinarySeed("a7sdybj';.,234fd"),
    generateBinarySeed("a7sdybj';.,234fd@$#sdaf"));
}

BOOST_AUTO_TEST_CASE(testSeedGenShort) {
    BOOST_CHECK_EQUAL(generateBinarySeed("123abc").size(), 16);
    BOOST_CHECK_EQUAL(generateBinarySeed("123abc"), "1011010101010101");
    BOOST_CHECK_EQUAL(generateBinarySeed("123abc"), "1011010101010101");
}

BOOST_AUTO_TEST_CASE(testTransform) {
    string stringSeed = "1010101010101010";
    string img = "vader.png";

    FibLFSR seed = FibLFSR(stringSeed);
    sf::Image sourceImage, transformedImage;
    sourceImage.loadFromFile(img);
    transformedImage.loadFromFile(img);

    transform(transformedImage, &seed);
    for (unsigned int x = 0; x < sourceImage.getSize().x; x++) {
        for (unsigned int y = 0; y < sourceImage.getSize().y; y++) {
            int count = 0;
            if (sourceImage.getPixel(x, y).r == transformedImage.getPixel(x, y).r) {
                count++;
            }
            if (sourceImage.getPixel(x, y).g == transformedImage.getPixel(x, y).g) {
                count++;
            }
            if (sourceImage.getPixel(x, y).b == transformedImage.getPixel(x, y).b) {
                count++;
            }
            BOOST_CHECK_NE(count, 3);
        }
    }

    seed = FibLFSR(stringSeed);
    transform(transformedImage, &seed);
    for (unsigned int x = 0; x < sourceImage.getSize().x; x++) {
        for (unsigned int y = 0; y < sourceImage.getSize().y; y++) {
            BOOST_REQUIRE_EQUAL(sourceImage.getPixel(x, y).r, transformedImage.getPixel(x, y).r);
            BOOST_REQUIRE_EQUAL(sourceImage.getPixel(x, y).g, transformedImage.getPixel(x, y).g);
            BOOST_REQUIRE_EQUAL(sourceImage.getPixel(x, y).b, transformedImage.getPixel(x, y).b);
        }
    }
}

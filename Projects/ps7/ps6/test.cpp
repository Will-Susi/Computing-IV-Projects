// Copyright 2023 William Susi

#include "RandWriter.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(OrderKMethod) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_EQUAL(text.orderK(), orderK);
}

BOOST_AUTO_TEST_CASE(testFreqNoCharThrow) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_THROW(text.freq("ga"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testFreqNoCharNoThrow) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_NO_THROW(text.freq("gag"));
}

BOOST_AUTO_TEST_CASE(testFreqNoChar) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_EQUAL(text.freq("gag"), 4);
    BOOST_REQUIRE_EQUAL(text.freq("agg"), 2);
    BOOST_REQUIRE_EQUAL(text.freq("ggg"), 1);
    BOOST_REQUIRE_EQUAL(text.freq("gga"), 1);
    BOOST_REQUIRE_EQUAL(text.freq("aga"), 3);
    BOOST_REQUIRE_EQUAL(text.freq("aaa"), 1);

    BOOST_REQUIRE_EQUAL(text.freq("ggc"), 1);
    BOOST_REQUIRE_EQUAL(text.freq("gcg"), 1);
    BOOST_REQUIRE_EQUAL(text.freq("cga"), 1);

    BOOST_REQUIRE_EQUAL(text.freq("cgc"), 0);
}

BOOST_AUTO_TEST_CASE(testFreqCharThrow) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_THROW(text.freq("ga", 'W'), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testFreqCharNoThrow) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_NO_THROW(text.freq("g", 'a'));
}

BOOST_AUTO_TEST_CASE(testFreqChar) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_EQUAL(text.freq("a", 'a'), 2);
    BOOST_REQUIRE_EQUAL(text.freq("a", 'g'), 5);
    BOOST_REQUIRE_EQUAL(text.freq("a", 'c'), 0);

    BOOST_REQUIRE_EQUAL(text.freq("g", 'a'), 5);
    BOOST_REQUIRE_EQUAL(text.freq("g", 'g'), 3);
    BOOST_REQUIRE_EQUAL(text.freq("g", 'c'), 1);

    BOOST_REQUIRE_EQUAL(text.freq("c", 'a'), 0);
    BOOST_REQUIRE_EQUAL(text.freq("c", 'g'), 1);
    BOOST_REQUIRE_EQUAL(text.freq("c", 'c'), 0);
}

BOOST_AUTO_TEST_CASE(testKRandThrow) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_THROW(text.kRand("W"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testKRandNoThrow) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_NO_THROW(text.kRand("g"));
}

BOOST_AUTO_TEST_CASE(testKRand) {
    int orderK = 1;
    RandWriter text("gagggagaggcgagaaa", orderK);
    char c = text.kRand("g");
    BOOST_REQUIRE(c == 'g' || c == 'a' || c == 'c');
    BOOST_REQUIRE(c != 'W');
}

BOOST_AUTO_TEST_CASE(testGenerateThrow) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_THROW(text.generate("gaga", 6), std::runtime_error);
    BOOST_REQUIRE_THROW(text.generate("Won", 6), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(testGenerateNoThrow) {
    int orderK = 3;
    RandWriter text("gagggagaggcgagaaa", orderK);
    BOOST_REQUIRE_NO_THROW(text.generate("gag", 6));
}

BOOST_AUTO_TEST_CASE(testGenerate) {
    int orderK = 2;
    int length = 10;
    RandWriter text("gagggagaggcgagaaa", orderK);
    string s = text.generate("ga", length);
    BOOST_REQUIRE_EQUAL(s.size(), static_cast<size_t>(length));
    for (char ch : s) {
        BOOST_REQUIRE(ch == 'g' || ch == 'a' || ch == 'c');
    }
}

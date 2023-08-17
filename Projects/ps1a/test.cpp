#include <iostream>
#include <string>
#include <sstream>

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
    BOOST_REQUIRE_EQUAL(l4.getRegister(), "1011011000110110");
}

BOOST_AUTO_TEST_CASE(testOutputOverload) {
    FibLFSR l5("1011011000110110");
    stringstream ss;
    ss << l5;
    BOOST_REQUIRE_EQUAL(ss.str(), "1011011000110110");
}
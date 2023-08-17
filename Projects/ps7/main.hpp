// Copyright 2023 William Susi

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "boost/date_time/posix_time/posix_time.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::regex;
using std::regex_match;
using boost::posix_time::time_from_string;

boost::date_time::time_resolution_traits_adapted64_impl::int_type
convertTime(string start, string end);

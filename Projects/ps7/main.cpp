// Copyright 2023 William Susi

#include "main.hpp"

int main(int argc, char** argv) {
    // Regexs for start and completion of log
    regex start{R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}): \(log\.c\.\d+\) server started )"};
    regex completion{R"((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})+\.\d{3}:INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:\d{4})"};

    // Load log file
    std::fstream log;
    string fileName = argv[1];
    log.open(fileName, std::fstream::in);

    // Load report file
    std::fstream report;
    report.open(fileName + ".rpt", std::fstream::out);

    // Create boot stream
    std::stringstream boots;

    // Get line from log
    int lineNum = 1, started = 0, completed = 0;
    bool isBegun = false;
    string line, startTime, endTime;
    while (getline(log, line)) {
        std::match_results<string::const_iterator> match;
        if (regex_match(line, match, start)) {  // Check if a start boot is found
            if (isBegun) {  // Check if a boot already started
                boots << "**** Incomplete boot **** " << endl << endl;
            }
            startTime = match[1];
            boots << "=== Device boot ===" << endl;
            boots << lineNum << "(" << fileName << "): " << startTime << " Boot Start" << endl;
            isBegun = true;
            started++;
        } else if (regex_match(line, match, completion)) {  // Check if boot completed
            endTime = match[1];
            boots << lineNum << "(" << fileName << "): " << endTime << " Boot Completed" << endl;
            boots << "\tBoot Time: " << convertTime(startTime, endTime) << "ms" << endl << endl;
            isBegun = false;
            completed++;
        }

        lineNum++;
    }

    // Write Summary
    report << "=== Boot Summary ===" << endl;
    report << "Total Lines: " << lineNum << endl;
    report << "Started Boots: " << started << endl;
    report << "Completed Boots: " << completed << endl << endl;

    // Add boots to report
    report << boots.rdbuf();

    // Close files
    log.close();
    report.close();

    return 0;
}

// Function to convert the difference between two date/times into milliseconds
boost::date_time::time_resolution_traits_adapted64_impl::int_type
convertTime(string start, string end) {
    return (time_from_string(end) - time_from_string(start)).total_milliseconds();
}

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "schedule.h"
#include "tests_util.h"

TEST_CASE("schedule() Approximate Public Test 1", "[weight=2]") {
    const V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM", "3PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 4);
}

TEST_CASE("schedule() Public Test 1", "[weight=3]") {
    const V2D roster = {{"CS577", "JydY", "MnWd", "tnkL"},\
     {"CS591", "gpDS", "94Ol", "tnkL"}, \
     {"CS386", "SjC0", "EYge", "Nvu1"}, \
     {"CS500", "MnWd", "uAcT", "EYge"}, \
     {"CS395", "gpDS", "EYge", "MnWd"}
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 3);
}

TEST_CASE("schedule() Private Test 1", "[weight=3]") {
    const V2D roster = {{"CS192", "wm1T", "O9i1", "QvSG", "nHjj", "dc7C"},\
     {"CS106", "0er0", "10Px", "QvSG", "g9uV", "Jw5W"}, \
     {"CS464", "Y9tA", "dc7C", "G0dk", "Emdk", "8yvt"}, \
     {"CS194", "O9i1", "Jw5W", "Emdk", "G0dk"}, \
     {"CS135", "N5o6", "Kl61", "nHjj", "Y9tA"}, \
     {"CS526", "RitE", "O9i1", "jaxv", "QvSG"}, \
     {"CS545", "10Px", "Kl61", "nHjj", "8yvt"}, \
     {"CS471", "bsVd", "RitE", "N5o6"}, \
     {"CS593", "dc7C", "jaxv", "8yvt", "bsVd", "Y9tA", "0er0", "Jw5W", "QvSG", "Kl61"}, \
     {"CS129", "g9uV", "N5o6", "vGYN", "URqy", "dc7C"}, \
     {"CS355", "bsVd", "dc7C", "wm1T", "8yvt", "Y9tA"}, \
     {"CS433", "10Px", "Jw5W", "dc7C", "G0dk"}, \
     {"CS366", "0er0", "10Px", "O9i1", "Kl61", "wm1T", "g9uV", "URqy", "N5o6", "vGYN", "QvSG"}, \
     {"CS503", "jaxv", "O9i1", "vGYN", "Y9tA", "bsVd"}, \
     {"CS449", "G0dk", "O9i1", "wm1T", "g9uV", "dc7C", "URqy", "jaxv", "N5o6", "Jw5W", "Emdk"} \
     };

    std::vector<std::string> timeslots = {"9AM", "11AM", "1PM", "2PM", "3PM", "4PM", "5PM", "6PM", "7PM"};

    V2D out = schedule(roster, timeslots);

    verifySchedule(roster, out, 9);
}

TEST_CASE("schedule() No Match Test Public 1", "[weight=5]") {
    const V2D roster = {
    {"CS101", "a", "b"}, \
    {"CS102", "b", "c"}, \
    {"CS103", "a", "c"}
    };

    std::vector<std::string> timeslots = {"9AM", "11AM"};

    V2D out = schedule(roster, timeslots);

    REQUIRE(out.size()==1);
    REQUIRE(out[0].size()==1);
    REQUIRE(out[0][0]=="-1");
}

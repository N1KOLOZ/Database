#pragma once

// Local lib
#include "test_runner.h"

#include "date.h"
#include "event.h"
#include "database.h"
#include "condition_parser.h"
#include "node.h"

#include <sstream>


void TestParseEvent() {
    {
        std::istringstream is(" event");
        ASSERT_EQUAL(ParseEvent(is), "event")
    }

    {
        std::istringstream is("   sport event ");
        ASSERT_EQUAL(ParseEvent(is), "sport event ")
    }

    {
        std::istringstream is("  first event  \n  second event");
        std::vector<std::string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));

        std::vector<std::string> result = {"first event  ", "second event"};

        ASSERT_EQUAL(events, result)
    }
}

void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, TestParseEvent);
}


#include "test.h"

#include "date.h"
#include "event.h"
#include "database.h"
#include "condition_parser.h"
#include "node.h"

#include <iostream>
#include <sstream>
#include <stdexcept>

int main() {
    TestAll();

    Database db;

    for (std::string line; getline(std::cin, line); ) {
        std::istringstream is(line);

        std::string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(std::cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };

           auto count = db.RemoveIf(predicate);
           std::cout << "Removed " << count << " entries" << std::endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const std::string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                std::cout << entry << std::endl;
            }
            std::cout << "Found " << entries.size() << " entries" << std::endl;
        } else if (command == "Last") {
            try {
                std::cout << db.Last(ParseDate(is)) << std::endl;
            } catch (std::invalid_argument& ) {
                std::cout << "No entries" << std::endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw std::logic_error("Unknown command: " + command);
        }
    }

    return 0;
}



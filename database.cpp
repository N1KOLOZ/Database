//
// Created by n1kme on 12/29/2019.
//

// System
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

// Local
#include "database.h"


std::ostream& operator<<(std::ostream& os, const Entry& entry) {
    return os << entry.date << " " << entry.event;
}

void Database::Add(const Date &date, std::string event) {
    if (_dates_to_events.count(date)) {
        auto it = std::find(_dates_to_events[date].begin(), _dates_to_events[date].end(),
                event);

        if (it == _dates_to_events[date].end()) {
            _dates_to_events[date].push_back(event);
        }
    } else {
        _dates_to_events[date].push_back(event);
    }

}

void Database::Print(std::ostream& os) const {
    for (const auto& date_to_events : _dates_to_events) {
        os << date_to_events.first << " ";

        for (const std::string& event : date_to_events.second) {
            os << event << " ";
        }

        os << std::endl;
    }
}

Entry Database::Last(const Date &date) const {
    auto upper_bound = _dates_to_events.upper_bound(date);

    if (upper_bound == _dates_to_events.begin()) {
        throw std::invalid_argument("");
    }

    return {std::prev(upper_bound)->first, std::prev(upper_bound)->second.back()};
}





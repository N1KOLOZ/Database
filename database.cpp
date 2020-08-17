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
    if (_datesToEvents.count(date)) {
        auto it = std::find(_datesToEvents[date].begin(), _datesToEvents[date].end(),
                event);

        if (it == _datesToEvents[date].end()) {
            _datesToEvents[date].push_back(event);
        }
    } else {
        _datesToEvents[date].push_back(event);
    }

}

void Database::Print(std::ostream& os) const {
    for (const auto& dateToEvents : _datesToEvents) {
        os << dateToEvents.first << " ";

        for (const std::string& event : dateToEvents.second) {
            os << event << " ";
        }

        os << std::endl;
    }
}

Entry Database::Last(const Date &date) const {
    auto upper_bound = _datesToEvents.upper_bound(date);

    if (upper_bound == _datesToEvents.begin()) {
        throw std::invalid_argument("");
    }

    return {std::prev(upper_bound)->first, std::prev(upper_bound)->second.back()};
}



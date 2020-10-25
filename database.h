#pragma once

#include "date.h"

#include <map>
#include <set>
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>


struct Entry {
    Date date;
    std::string event;
};

std::ostream& operator<<(std::ostream& os, const Entry& entry);

bool operator == (const Entry& lhs, const Entry& rhs);

class Database {
public:
    void Add(const Date& date, std::string events);

    void Print(std::ostream& os) const;

    Entry Last(const Date& date) const;

    template<class Predicate>
    int RemoveIf(Predicate p);

    template<class Predicate>
    std::vector<Entry> FindIf(Predicate p) const;
private:
    std::map<Date, std::vector<std::string>> _dates_to_events;
};

template<class Predicate>
std::vector<Entry> Database::FindIf(Predicate p) const {
    std::vector<Entry> result;

    for (const auto& date_to_events : _dates_to_events) {
        for (const auto& event : date_to_events.second) {
            if ( p(date_to_events.first, event) ) {
                result.push_back( {date_to_events.first, event} );
            }
        }
    }

    return result;
}

// returns number of removed events
template<class Predicate>
int Database::RemoveIf(Predicate p) {
    int result = 0;

    for (auto& date_to_events : _dates_to_events) {

        const Date& date = date_to_events.first;
        auto split_point = stable_partition(date_to_events.second.begin(), date_to_events.second.end(),
                                            [date, p](const std::string& event) {
                                                return !p(date, event);
                                            });

        result += date_to_events.second.end() - split_point;
        date_to_events.second.erase(split_point, date_to_events.second.end());
    }

    for (auto it = _dates_to_events.begin(); it != _dates_to_events.end(); ) {
        if (it->second.empty()) {
            _dates_to_events.erase(it++);
        } else {
            ++it;
        }
    }

    return result;
}




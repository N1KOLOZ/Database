//
// Created by n1kme on 12/29/2019.
//

#pragma once

// System
#include <map>
#include <set>
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>

// Local
#include "date.h"

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
    int RemoveIf(Predicate p) {
        int count = 0;

        for (auto& dateToEvents : _datesToEvents) {

            const Date& date = dateToEvents.first;
            auto split_point = std::stable_partition(dateToEvents.second.begin(), dateToEvents.second.end(),
                    [date, p](const std::string& event) {
                return !p(date, event);
            });

            count += dateToEvents.second.end() - split_point;
            dateToEvents.second.erase(split_point, dateToEvents.second.end());
        }

        for (auto it = _datesToEvents.begin(); it != _datesToEvents.end(); ) {
            if (it->second.empty()) {
                _datesToEvents.erase(it++);
            } else {
                ++it;
            }
        }

        return count;
    }

    template<class Predicate>
    std::vector<Entry> FindIf(Predicate p) const {
        std::vector<Entry> result;

        for (const auto& _dateToEvents : _datesToEvents) {
            for (const auto& event : _dateToEvents.second) {
                if ( p(_dateToEvents.first, event) ) {
                    result.push_back( {_dateToEvents.first, event} );
                }
            }
        }

        return result;
    }


private:
    std::map<Date, std::vector<std::string>> _datesToEvents;
};




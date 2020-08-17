//
// Created by n1kme on 1/1/2020.
//

// System
#include <iomanip>
#include <tuple>
#include <stdexcept>

// Local
#include "date.h"


Date::Date(int year_, int month_, int day_) :
        year(year_),
        month(month_),
        day(day_){

}

Date ParseDate(std::istream& date_stream) {

    bool dateIsCorrect = true;

    int year;
    dateIsCorrect = dateIsCorrect && (date_stream >> year);
    dateIsCorrect = dateIsCorrect && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    dateIsCorrect = dateIsCorrect && (date_stream >> month);
    dateIsCorrect = dateIsCorrect && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    dateIsCorrect = dateIsCorrect && (date_stream >> day);

    if (!dateIsCorrect) {
        throw std::logic_error("Wrong date format");
    }

    return Date(year, month, day);
}

ostream& operator << (ostream& os, const Date& date) {
    os << setw(4) << setfill('0') << date.year <<
    "-" << setw(2) << setfill('0') << date.month <<
    "-" << setw(2) << setfill('0') << date.day;
    return os;
}


bool operator<(const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) < tie(rhs.year, rhs.month, rhs.day);
}

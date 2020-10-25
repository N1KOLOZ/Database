#include "date.h"

#include <iomanip>
#include <tuple>
#include <stdexcept>

Date::Date(int year, int month, int day) :
        year(year),
        month(month),
        day(day)
{
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

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << std::setw(4) << std::setfill('0') << date.year << "-"
       << std::setw(2) << std::setfill('0') << date.month << "-"
       << std::setw(2) << std::setfill('0') << date.day;

    return os;
}


bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

#pragma once

#include <iostream>

class Date {
public:
    Date(int year, int month, int day);

    int year;
    int month;
    int day;
};

std::ostream& operator<<(std::ostream& os, const Date& date);
bool operator<(const Date& lhs, const Date& rhs);

Date ParseDate(std::istream& is);



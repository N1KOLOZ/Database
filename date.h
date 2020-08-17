//
// Created by n1kme on 1/1/2020.
//

#pragma once

#include <iostream>

using namespace std;

class Date {
public:
    Date(int year_, int month_, int day_);

    int year;
    int month;
    int day;
};

ostream& operator<<(ostream& os, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);

Date ParseDate(istream& is);



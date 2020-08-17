//
// Created by n1kme on 12/29/2019.
//

#pragma once

// Local
#include "date.h"

// System
#include <string>
#include <memory>

using namespace std;

struct Node {
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

struct EmptyNode : public Node {
    bool Evaluate(const Date& date, const string& event) const override;
};

enum class Comparison {
    Less,
    LessOrEqual,
    Equal,
    NotEqual,
    Greater,
    GreaterOrEqual,
};

enum class LogicalOperation {
    And,
    Or,
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& comparison, const Date& date);
    bool Evaluate(const Date& date, const string& event) const override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const string& date);
    bool Evaluate(const Date& date, const string& event) const override;

private:
    Comparison _cmp;
    string _event;
};


class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& op, shared_ptr<Node> left, shared_ptr<Node> right);
    bool Evaluate(const Date& date, const string& event) const override;

private:
    LogicalOperation _op;
    shared_ptr<Node> _lhs, _rhs;
};



#pragma once

#include "date.h"

#include <string>
#include <memory>

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

struct Node {
    virtual bool Evaluate(const Date& date, const std::string& event) const = 0;
};

struct EmptyNode : public Node {
    bool Evaluate(const Date& date, const std::string& event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison& comparison, const Date& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison _cmp;
    Date _date;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison& cmp, const std::string& date);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    Comparison _cmp;
    std::string _event;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation& op, std::shared_ptr<Node> left, std::shared_ptr<Node> right);
    bool Evaluate(const Date& date, const std::string& event) const override;

private:
    LogicalOperation _op;
    std::shared_ptr<Node> _lhs, _rhs;
};



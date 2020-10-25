#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const std::string& event) const {
    return true;
}


DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
        _cmp(cmp),
        _date(date) {
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const std::string& event) :
        _cmp(cmp),
        _event(event)
{
}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    if ( _cmp == Comparison::Equal ) {
        return event == _event;
    } else if ( _cmp == Comparison::NotEqual )  {
        return event != _event;
    }

    return false;
}

LogicalOperationNode::LogicalOperationNode(
        const LogicalOperation& op, std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs) :
        _op(op),
        _lhs(lhs),
        _rhs(rhs) {
}

bool LogicalOperationNode::Evaluate(const Date& date, const std::string& event) const {
    if (_op == LogicalOperation::And) {
        return  _lhs->Evaluate(date, event) && _rhs->Evaluate(date, event);
    } else if ( _op == LogicalOperation::Or ) {
        return  _lhs->Evaluate(date, event) || _rhs->Evaluate(date, event);
    }

    return false;
}

bool DateComparisonNode::Evaluate(const Date& date, const std::string& event) const {
    if ( _cmp == Comparison::Less ) {
        return std::tie(date.year, date.month, date.day) < std::tie(_date.year, _date.month, _date.day);
    } else if ( _cmp == Comparison::LessOrEqual) {
        return std::tie(date.year, date.month, date.day) <= std::tie(_date.year, _date.month, _date.day);
    } else if ( _cmp ==  Comparison::Equal ) {
        return std::tie(date.year, date.month, date.day) == std::tie(_date.year, _date.month, _date.day);
    } else if (_cmp ==  Comparison::NotEqual) {
        return std::tie(date.year, date.month, date.day) != std::tie(_date.year, _date.month, _date.day);
    } else if ( _cmp ==  Comparison::Greater ) {
        return std::tie(date.year, date.month, date.day) > std::tie(_date.year, _date.month, _date.day);
    } else if ( _cmp == Comparison::GreaterOrEqual ) {
        return std::tie(date.year, date.month, date.day) >= std::tie(_date.year, _date.month, _date.day);
    }

    return false;
}


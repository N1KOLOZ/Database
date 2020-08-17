//
// Created by n1kme on 1/4/2020.
//

#include "node.h"



bool EmptyNode::Evaluate(const Date& date, const string& event) const {
    return true;
}


DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& date) :
        _cmp(cmp),
        _date(date) {
}


EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event) :
        _cmp(cmp),
        _event(event)
{
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) const {
    if ( _cmp == Comparison::Equal ) {
        return event == _event;
    } else if ( _cmp == Comparison::NotEqual )  {
        return event != _event;
    }

    return false;
}

LogicalOperationNode::LogicalOperationNode(
        const LogicalOperation& op, shared_ptr<Node> lhs, shared_ptr<Node> rhs) :
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
        return tie(date.year, date.month, date.day) < tie(_date.year, _date.month, _date.day);
    } else if ( _cmp == Comparison::LessOrEqual) {
        return tie(date.year, date.month, date.day) <= tie(_date.year, _date.month, _date.day);
    } else if ( _cmp ==  Comparison::Equal ) {
        return tie(date.year, date.month, date.day) == tie(_date.year, _date.month, _date.day);
    } else if (_cmp ==  Comparison::NotEqual) {
        return tie(date.year, date.month, date.day) != tie(_date.year, _date.month, _date.day);
    } else if ( _cmp ==  Comparison::Greater ) {
        return tie(date.year, date.month, date.day) > tie(_date.year, _date.month, _date.day);
    } else if ( _cmp == Comparison::GreaterOrEqual ) {
        return tie(date.year, date.month, date.day) >= tie(_date.year, _date.month, _date.day);
    }

    return false;
}


#include "event.h"

#include <stdexcept>

std::string ParseEvent(std::istream& event_stream) {
    bool is_correct = true;
    is_correct = is_correct && (event_stream.peek() == ' ');

    if (!is_correct) {
        throw std::logic_error("Wrong event format");
    }

    event_stream.ignore(1);

    std::string event;
    getline(event_stream, event);

    return event;
}

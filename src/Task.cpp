#include "../inc/Task.h"
#include <sstream>

Task::Task(const std::string& description,const DateTime& date_time,const Location& location) : description(description),date_time(date_time),location(location) {}

std::string Task::toString() const { //stampo la task nel formato --> Date & Time: GG-MM-AAAA HH:MM:SS; Location: location; Completed: 1/0; Description: description
    std::ostringstream toString;
    toString << "Date & Time: " << this->date_time.toString() << "; Location: " << this->location.getAddress() << "; Completed: ";
    if (this->completed) toString << "yes; Description: " << this->description;
    else toString << "no; Description: " << this->description;
    return toString.str();
}

const std::string& Task::getDescription() const {
    return this->description;
}
bool Task::isCompleted() const {
    return this->completed;
}
const DateTime& Task::getDateTime() const {
    return this->date_time;
}
const Location& Task::getLocation() const {
    return this->location;
}
void Task::setDescription(const std::string& description) {
    this->description=description;
}
void Task::markCompleted() {
    this->completed=true;
}
void Task::markPending() {
    this->completed=false;
}
void Task::setDateTime(const DateTime &date_time) {
    this->date_time=date_time;
}
void Task::setLocation(const Location& location) {
    this->location=location;
}

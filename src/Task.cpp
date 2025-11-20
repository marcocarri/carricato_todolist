#include "../inc/Task.h"
#include <sstream>

Task::Task(const std::string &description) : description(description) {}

std::string Task::toString() const {
    std::ostringstream toString;
    toString << "Completed: ";
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
void Task::setDescription(const std::string& description) {
    this->description=description;
}
void Task::markCompleted() {
    this->completed=true;
}
void Task::markPending() {
    this->completed=false;
}

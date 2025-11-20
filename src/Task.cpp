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

void Task::save(std::ostream& outstream) const {
    std::string output="";
    output+=this->date_time.getDate().toString()+"|"+this->date_time.getTime().toString()+"|"+this->location.getAddress()+"|"+std::to_string(this->completed)+"|"+this->description;
    outstream << output << std::endl;
}
void Task::load(std::istream& instream) {
    std::string date, time, location, completed;
    if (!std::getline(instream,date,'|')) return;
    if (!std::getline(instream,time,'|')) return;
    try {
        this->date_time=DateTime(date,time);
    } catch (const std::invalid_argument&) {
        instream.setstate(std::ios::failbit);
        return;
    }
    if (!std::getline(instream,location,'|')) return;
    this->location=Location(location);
    if (!std::getline(instream,completed,'|')) return;
    if (completed.compare("1")==0) this->completed=true;
    else this->completed=false;
    if (!std::getline(instream,description)) return;
}

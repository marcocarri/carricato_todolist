#include "../inc/DateTime.h"

#include <sstream>

DateTime::DateTime(int day, int month, int year, int hour, int minute, int second) : date(day,month,year), time(hour,minute,second) {}
DateTime::DateTime(const Date &date, const TimeOfDay &time) : date(date), time(time) {}
DateTime::DateTime(const std::string &dateString, const std::string &timeString) : date(dateString), time(timeString) {}

std::string DateTime::toString() const { //stampo DateTime nel formato GG-MM-AAAA HH:MM:SS
    std::ostringstream toString;
    toString << date.toString() << " " << time.toString();
    return toString.str();
}

const Date &DateTime::getDate() const {
    return this->date;
}
const TimeOfDay &DateTime::getTime() const {
    return this->time;
}
void DateTime::setDate(int day,int month,int year) {
    this->date.setDate(day,month,year);
}
void DateTime::setDate(const Date &date) {
    this->date.setDate(date);
}
void DateTime::setDate(const std::string& date) {
    this->date.setDate(date);
}
void DateTime::setTime(int hour,int minute,int second) {
    this->time.setTime(hour,minute,second);
}
void DateTime::setTime(const TimeOfDay& time) {
    this->time.setTime(time);
}
void DateTime::setTime(const std::string& time) {
    this->time.setTime(time);
}

bool DateTime::operator==(const DateTime& other) const {
    return (this->date == other.date) && (this->time == other.time);
}
bool DateTime::operator>(const DateTime& other) const {
    if (this->date>other.date) {
        return true;
    }
    if (this->date==other.date) {
        return this->time>other.time;
    }
    return false;
}
bool DateTime::operator<(const DateTime& other) const {
    if (this->date<other.date) {
        return true;
    }
    if (this->date==other.date) {
        return this->time<other.time;
    }
    return false;
}

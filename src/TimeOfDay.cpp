#include "../inc/TimeOfDay.h"

#include <stdexcept>

TimeOfDay::TimeOfDay(int hour,int minute,int second) : hour(hour),minute(minute),second(second) {
    if (!checkTime(hour,minute,second)) { //controlla che i valori inseriti siano validi
        throw std::invalid_argument("Orario non valido.");
    }
}
TimeOfDay::TimeOfDay(const TimeOfDay &time) = default;

int TimeOfDay::getHour() const {
    return this->hour;
}
int TimeOfDay::getMinute() const {
    return this->minute;
}
int TimeOfDay::getSecond() const {
    return this->second;
}
void TimeOfDay::setTime(int hour,int minute,int second) {
    TimeOfDay temp(hour,minute,second);
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}
void TimeOfDay::setTime(const TimeOfDay& time) {
    TimeOfDay temp(time);
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}

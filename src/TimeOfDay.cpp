#include "../inc/TimeOfDay.h"

#include <iomanip>
#include <stdexcept>

TimeOfDay::TimeOfDay(int hour,int minute,int second) : hour(hour),minute(minute),second(second) {
    if (!checkTime(hour,minute,second)) {
        throw std::invalid_argument("Orario non valido.");
    }
}
TimeOfDay::TimeOfDay(const TimeOfDay &time) = default;
TimeOfDay::TimeOfDay(const std::string& timeString) {
    std::istringstream inString(timeString);
    char dash1=0, dash2=0;
    if (!(inString >> hour >> dash1 >> minute >> dash2 >> second)||(dash1!=':')||(dash2!=':')) {
        throw std::invalid_argument("Formato orario non valido. Atteso HH:MM:SS.");
    }
    TimeOfDay temp(hour,minute,second);
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}

std::string TimeOfDay::toString() const { //stampo l'orario nel formato HH:MM:SS
    std::ostringstream toString;
    toString << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute << ":" << std::setw(2) << std::setfill('0') << second;
    return toString.str();
}

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

bool TimeOfDay::checkTime(int hour,int minute,int second) {
    if (hour<0||hour>23) return false;
    if (minute<0||minute>59) return false;
    if (second<0||second>59) return false;
    return true;
}

bool TimeOfDay::operator==(const TimeOfDay& other) const {
    return (this->hour==other.hour)&&(this->minute==other.minute)&&(this->second==other.second);
}
bool TimeOfDay::operator>(const TimeOfDay& other) const {
    if (this->hour!=other.hour) return this->hour>other.hour;
    if (this->minute!=other.minute) return this->minute>other.minute;
    return this->second>other.second;
}
bool TimeOfDay::operator<(const TimeOfDay& other) const {
    if (this->hour!=other.hour) return this->hour<other.hour;
    if (this->minute!=other.minute) return this->minute<other.minute;
    return this->second<other.second;
}

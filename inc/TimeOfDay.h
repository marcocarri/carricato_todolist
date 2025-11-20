#ifndef CARRICATO_TODOLIST_TIMEOFDAY_H
#define CARRICATO_TODOLIST_TIMEOFDAY_H

#include <string>

class TimeOfDay { //classe chiamata TimeOfDay per evitare problemi con <ctime>
private:
    int hour;
    int minute;
    int second;

public:
    TimeOfDay(int hour,int minute,int second);
    TimeOfDay(const TimeOfDay& time);
    TimeOfDay(const std::string& time);
    std::string toString() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    void setTime(int hour,int minute,int second);
    void setTime(const TimeOfDay& time);
    bool checkTime(int hour,int minute,int second);
    bool operator==(const TimeOfDay& time) const;
    bool operator>(const TimeOfDay& time) const;
    bool operator<(const TimeOfDay& time) const;
};

#endif //CARRICATO_TODOLIST_TIMEOFDAY_H
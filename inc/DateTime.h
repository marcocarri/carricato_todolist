#ifndef CARRICATO_TODOLIST_DATETIME_H
#define CARRICATO_TODOLIST_DATETIME_H

#include "Date.h"
#include "TimeOfDay.h"

#include <string>

class DateTime {
private:
    Date date;
    TimeOfDay time;

public:
    DateTime(int day,int month,int year,int hour,int minute,int second);
    DateTime(const Date& date,const TimeOfDay& time);
    DateTime(const std::string& dateString,const std::string& timeString);
    std::string toString() const;
    const Date& getDate() const;
    const TimeOfDay& getTime() const;
    void setDate(int day,int month,int year);
    void setDate(const Date& date);
    void setDate(const std::string& dateString);
    void setTime(int hour,int minute,int second);
    void setTime(const TimeOfDay& time);
    void setTime(const std::string& timeString);
    bool operator==(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator<(const DateTime& other) const;

};

#endif //CARRICATO_TODOLIST_DATETIME_H
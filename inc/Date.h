#ifndef CARRICATO_TODOLIST_DATE_H
#define CARRICATO_TODOLIST_DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day,int month,int year);
    Date(const Date& date);
    Date(const std::string& date);
    std::string toString() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDate(int day,int month,int year);
    void setDate(const Date& date);
    bool checkDate(int day,int month,int year);
    bool isLeapYear(int year);
    bool operator==(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
};

#endif //CARRICATO_TODOLIST_DATE_H
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
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void setDate(int day,int month,int year);
    void setDate(const Date& date);
};

#endif //CARRICATO_TODOLIST_DATE_H
#include "../inc/Date.h"

#include <stdexcept>

Date::Date(int day,int month,int year) : day(day), month(month), year(year) {
    if (!checkDate(day,month,year)) {
        throw std::invalid_argument("Data non valida.");
    }
}
Date::Date(const Date& date) = default;

int Date::getDay() const {
    return day;
}
int Date::getMonth() const {
    return month;
}
int Date::getYear() const {
    return year;
}
void Date::setDate(int day,int month,int year) {
    Date temp(day,month,year);
    this->day=temp.day;
    this->month=temp.month;
    this->year=temp.year;
}
void Date::setDate(const Date& date) {
    Date temp(date);
    this->day=temp.day;
    this->month=temp.month;
    this->year=temp.year;
}

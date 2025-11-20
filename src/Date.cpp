#include "../inc/Date.h"

#include <iomanip>
#include <stdexcept>
#include <vector>

Date::Date(int day,int month,int year) : day(day), month(month), year(year) {
    if (!checkDate(day,month,year)) {
        throw std::invalid_argument("Data non valida.");
    }
}
Date::Date(const Date& date) = default;
Date::Date(const std::string& dateString){
    std::istringstream inString(dateString);
    char dash1=0, dash2=0;
    if (!(inString >> day >> dash1 >> month >> dash2 >> year)||(dash1!='-')||(dash2!='-')) {
        throw std::invalid_argument("Formato data non valido. Atteso GG-MM-AAAA.");
    }
    Date temp(day,month,year);
    this->day=temp.day;
    this->month=temp.month;
    this->year=temp.year;
}

std::string Date::toString() const { //stampo la data nel formato GG-MM-AAAA
    std::ostringstream toString;
    toString << std::setw(2) << std::setfill('0') << day << "-" << std::setw(2) << std::setfill('0') << month << "-" << year;
    return toString.str();
}

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

bool Date::checkDate(int day,int month,int year) { //restituisce true se la data inserita è valida
    if (year<1582) return false; //anno minimo inseribile: 1582 (calendario gregoriano)
    //vettore contenente i vari giorni per i rispettivi mesi
    std::vector<int> daysInMonth = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    //se è febbraio e l'anno è bisestile modifico il valore nel vettore per il mese di febbraio
    if ((month==2)&&(isLeapYear(year))) daysInMonth[2] = 29;
    //controllo se mese e giorno sono corretti
    if (month<1||month>12) return false;
    if (day<1||day>daysInMonth[month]) return false;
    return true;
}
bool Date::isLeapYear(int year) { //restituisce true se l'anno è bisestile
    return ((year%4==0)&&(year%100!=0))||(year%400==0);
}

//override operatori
bool Date::operator==(const Date& other) const {
    return (this->day==other.day)&&(this->month==other.month)&&(this->year==other.year);
}
bool Date::operator>(const Date& other) const {
    if (this->year!=other.year) return this->year>other.year;
    if (this->month!=other.month) return this->month>other.month;
    return this->day>other.day;
}
bool Date::operator<(const Date& other) const {
    if (this->year!=other.year) return this->year<other.year;
    if (this->month!=other.month) return this->month<other.month;
    return this->day<other.day;
}

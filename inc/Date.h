#ifndef CARRICATO_TODOLIST_DATE_H
#define CARRICATO_TODOLIST_DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    //costruttore
    Date(int day,int month,int year);
    Date(const Date& date);
    Date(const std::string& date); //costruttore che riceve una stringa contenente una data e si costruisce l'oggetto in automatico

    //toString
    std::string toString() const;

    //getter
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    //setter
    void setDate(int day,int month,int year);
    void setDate(const Date& date);
    void setDate(const std::string& dateString);

    //metodi per verificare la correttezza dell'input
    bool checkDate(int day,int month,int year);
    bool isLeapYear(int year);

    //override operatori
    bool operator==(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator<(const Date& other) const;
};

#endif //CARRICATO_TODOLIST_DATE_H
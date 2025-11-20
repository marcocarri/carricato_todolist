#ifndef CARRICATO_TODOLIST_TIMEOFDAY_H
#define CARRICATO_TODOLIST_TIMEOFDAY_H

#include <string>

class TimeOfDay { //classe chiamata TimeOfDay per evitare problemi con <ctime>
private:
    int hour;
    int minute;
    int second;

public:
    //costruttori
    TimeOfDay(int hour,int minute,int second);
    TimeOfDay(const TimeOfDay& time);
    TimeOfDay(const std::string& time); //costruttore che riceve una stringa contenente un orario e si costruisce l'oggetto in automatico

    //toString
    std::string toString() const;

    //getter
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    //setter
    void setTime(int hour,int minute,int second);
    void setTime(const TimeOfDay& time);
    void setTime(const std::string& time);

    //metodo per verificare la correttezza dell'input
    bool checkTime(int hour,int minute,int second);

    //override operatori
    bool operator==(const TimeOfDay& time) const;
    bool operator>(const TimeOfDay& time) const;
    bool operator<(const TimeOfDay& time) const;
};

#endif //CARRICATO_TODOLIST_TIMEOFDAY_H
#include "../inc/TimeOfDay.h"

#include <iomanip>
#include <stdexcept>

//costruttori
TimeOfDay::TimeOfDay(int hour,int minute,int second) : hour(hour),minute(minute),second(second) {
    if (!checkTime(hour,minute,second)) { //controlla che i valori inseriti siano validi
        throw std::invalid_argument("Orario non valido.");
    }
}
TimeOfDay::TimeOfDay(const TimeOfDay &time) = default;
TimeOfDay::TimeOfDay(const std::string& timeString) {
    std::istringstream inString(timeString);
    char dash1=0, dash2=0; //inizializzati a 0(=null) in modo che il controllo che siano ':' sia corretto
    if (!(inString >> hour >> dash1 >> minute >> dash2 >> second)||(dash1!=':')||(dash2!=':')) { //controlla che il formato della stringa sia corretto, senno invia un errore
        throw std::invalid_argument("Formato orario non valido. Atteso HH:MM:SS.");
    } //se non vengono lasciati errori i dati all'interno della stringa vengono estrapolati
    TimeOfDay temp(hour,minute,second); //costruisce l'oggetto per verificare che i valori di hour, minute e second siano validi
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}

//toString
std::string TimeOfDay::toString() const { //stampo l'orario nel formato HH:MM:SS
    std::ostringstream toString;
    toString << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute << ":" << std::setw(2) << std::setfill('0') << second;
    //--> uso setw(2) per "forzare" a 2 la dimensione dei parametri
    //--> uso setfill(0) in modo che nel caso i parametri siano monocifra venga impostata l'altra (cifra) in automatico a 0 (esempio: hour=5 viene scritto 05)
    //in questa maniera ogni orario è impostato nel formato corretto HH:MM:SS
    return toString.str();
}

//getter
int TimeOfDay::getHour() const {
    return this->hour;
}
int TimeOfDay::getMinute() const {
    return this->minute;
}
int TimeOfDay::getSecond() const {
    return this->second;
}

//setter
void TimeOfDay::setTime(int hour,int minute,int second) {
    TimeOfDay temp(hour,minute,second); //costruisce l'oggetto per verificare che i valori di hour, minute e second siano validi
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}
void TimeOfDay::setTime(const TimeOfDay& time) {
    TimeOfDay temp(time); //costruisce l'oggetto per verificare che i valori di hour, minute e second siano validi
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}
void TimeOfDay::setTime(const std::string& timeString) {
    TimeOfDay temp(timeString); //costruisce l'oggetto per verificare che i valori di hour, minute e second siano validi
    this->hour=temp.hour;
    this->minute=temp.minute;
    this->second=temp.second;
}

//metodo per verificare la correttezza dell'input
bool TimeOfDay::checkTime(int hour,int minute,int second) {
    if (hour<0||hour>23) return false;
    if (minute<0||minute>59) return false;
    if (second<0||second>59) return false;
    return true;
}

//override operatori
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

#ifndef CARRICATO_TODOLIST_LOCATION_H
#define CARRICATO_TODOLIST_LOCATION_H

#include <string>

class Location {
private:
    std::string address;

public:
    //costruttore
    Location(const std::string& address);

    //toString
    std::string toString() const;

    //getter
    const std::string& getAddress() const;

    //setter
    void setAddress(const std::string& address);

    //override operatori
    bool operator==(const Location& other) const;
};

#endif //CARRICATO_TODOLIST_LOCATION_H
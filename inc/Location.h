#ifndef CARRICATO_TODOLIST_LOCATION_H
#define CARRICATO_TODOLIST_LOCATION_H

#include <string>

class Location {
private:
    std::string address;

public:
    Location(const std::string& address);
    std::string toString() const;
    const std::string& getAddress() const;
    void setAddress(const std::string& address);
    bool operator==(const Location& other) const;
};

#endif //CARRICATO_TODOLIST_LOCATION_H
#include "../inc/Location.h"

#include <sstream>

//costruttore
Location::Location(const std::string &address) : address(address) {}

//toString
std::string Location::toString() const {
    std::ostringstream toString;
    toString << address;
    return toString.str();
}

//getter
const std::string &Location::getAddress() const {
    return this->address;
}

//setter
void Location::setAddress(const std::string &address) {
    this->address=address;
}

//toString
bool Location::operator==(const Location& other) const {
    return (this->address.compare(other.getAddress()))==0; //compare restituisce 0 se sono uguali quindi pongo tutto ==0
}

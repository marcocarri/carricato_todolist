#include "../inc/Location.h"
#include <sstream>

Location::Location(const std::string &address) : address(address) {}

std::string Location::toString() const {
    std::ostringstream toString;
    toString << address;
    return toString.str();
}

const std::string &Location::getAddress() const {
    return this->address;
}
void Location::setAddress(const std::string &address) {
    this->address=address;
}

bool Location::operator==(const Location& other) const {
    return (this->address.compare(other.getAddress()))==0; //compare restituisce 0 se sono uguali quindi pongo tutto ==0
}

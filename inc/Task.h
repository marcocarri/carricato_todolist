#ifndef CARRICATO_TODOLIST_TASK_H
#define CARRICATO_TODOLIST_TASK_H

#include "DateTime.h"
#include "Location.h"

#include <string>

class Task {
private:
    std::string description;
    bool completed;
    DateTime date_time;
    Location location;

public:

    Task(const std::string& description,const DateTime& date_time,const Location& location);
    std::string toString() const;
    const std::string& getDescription() const;
    bool isCompleted() const;
    const DateTime& getDateTime() const;
    const Location& getLocation() const;
    void setDescription(const std::string& description);
    void markCompleted();
    void markPending();
    void setDateTime(const DateTime& date_time);
    void setLocation(const Location& location);

    void save(std::ostream& outstream) const;
    void load(std::istream& instream);

};

#endif //CARRICATO_TODOLIST_TASK_H
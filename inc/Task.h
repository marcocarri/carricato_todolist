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
    //costruttore
    Task(const std::string& description,const DateTime& date_time,const Location& location);

    //toString
    std::string toString() const;

    //getter
    const std::string& getDescription() const;
    bool isCompleted() const;
    const DateTime& getDateTime() const;
    const Location& getLocation() const;

    //setter
    void setDescription(const std::string& description);
    void markCompleted();
    void markPending();
    void setDateTime(const DateTime& date_time);
    void setLocation(const Location& location);

    //metodi I/O (persistenza sul disco)
    void save(std::ostream& outstream) const;
    void load(std::istream& instream);

};

#endif //CARRICATO_TODOLIST_TASK_H
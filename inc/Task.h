#ifndef CARRICATO_TODOLIST_TASK_H
#define CARRICATO_TODOLIST_TASK_H

#include <string>

class Task {
private:
    std::string description;
    bool completed;

public:

    Task(const std::string& description);
    std::string toString() const;
    const std::string& getDescription() const;
    bool isCompleted() const;
    void setDescription(const std::string& description);
    void markCompleted();
    void markPending();

    void save();
    void load();

};

#endif //CARRICATO_TODOLIST_TASK_H
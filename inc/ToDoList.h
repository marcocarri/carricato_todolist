#ifndef CARRICATO_TODOLIST_TODOLIST_H
#define CARRICATO_TODOLIST_TODOLIST_H

#include "Task.h"

#include <vector>
#include <string>

class ToDoList {
private:
    std::vector<Task> tasks;
    const std::string filename="carricato_listaToDo.txt";

public:
    ToDoList();
    ~ToDoList();
    std::string toString() const;
    std::string vectorToString(const std::vector<Task>& tasks) const;
    const std::vector<Task>& getTasks() const;
    const std::string& getFileName() const;
    void setTasks(const std::vector<Task>& tasks);
    void addTask(const std::string& description,const DateTime& date_time,const Location& location);
    void removeTask(size_t index);
    Task& getTask(size_t index);

    void saveToFile();
    void loadFromFile();
};

#endif //CARRICATO_TODOLIST_TODOLIST_H
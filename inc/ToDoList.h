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
    //costruttore
    ToDoList();

    //distruttore
    ~ToDoList();

    //metodi di stampa
    std::string toString() const;
    std::string vectorToString(const std::vector<Task>& tasks) const;

    //getter
    const std::vector<Task>& getTasks() const;
    const std::string& getFileName() const;

    //setter
    void setTasks(const std::vector<Task>& tasks);

    //metodi per lavorare con il vettore
    void addTask(const std::string& description,const DateTime& date_time,const Location& location);
    void removeTask(size_t index);
    Task& getTask(size_t index);

    //metodi di ordinamento e filtro
    std::vector<Task> getSortedTasksByDateTimeDescending() const;
    std::vector<Task> getSortedTasksByDateTimeAscending() const;
    std::vector<Task> getFilteredTasksByCompleted(bool completed) const;
    std::vector<Task> getFilteredTasksByDate(const Date& date) const;
    std::vector<Task> getFilteredTasksByLocation(const Location& location) const;

    //metodi I/O (persistenza sul disco)
    void saveToFile() const;
    void loadFromFile();
};

#endif //CARRICATO_TODOLIST_TODOLIST_H
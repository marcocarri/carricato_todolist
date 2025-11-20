#include "../inc/ToDoList.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

using namespace std;

ToDoList::ToDoList() {
    loadFromFile();
}
ToDoList::~ToDoList() {
    saveToFile();
}

std::string ToDoList::toString() const {
    std::ostringstream toString;
    toString << "ToDoList: " << this->filename << endl;
    return toString.str()+vectorToString(this->tasks);
}
std::string ToDoList::vectorToString(const std::vector<Task>& tasks) const { //stampa qualsiasi vettore di task passato come parametro
    std::ostringstream toString;
    if (tasks.empty()) { return "Nessuna task da visualizzare.\n"; } //controllo se il vettore di task è vuoto
    toString << "--- Elenco Tasks ---" << endl;
    for (size_t i=0;i<tasks.size();++i) { toString << "[" << i+1 << "] " << tasks[i].toString() << endl; }
    toString << "--------------------" << endl;
    return toString.str();
}

const std::vector<Task>& ToDoList::getTasks() const {
    return this->tasks;
};
const std::string& ToDoList::getFileName() const {
    return this->filename;
}
void ToDoList::setTasks(const std::vector<Task>& tasks) {
    this->tasks=tasks;
}

void ToDoList::addTask(const std::string &description, const DateTime &date_time, const Location &location) {
    tasks.push_back(Task(description,date_time,location));
}
void ToDoList::removeTask(size_t index) {
    if (index>=tasks.size()) {
        throw std::out_of_range("Indice task non valido.");
    }
    tasks.erase(tasks.begin()+index);
}
Task& ToDoList::getTask(size_t index) {
    if (index>=tasks.size()) {
        throw std::out_of_range("Indice task non valido.");
    }
    return tasks.at(index);
}
std::vector<Task> ToDoList::getSortedTasksByDateTimeDescending() const {
    std::vector<Task> sortedTasks = tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(),
        [](const Task& t1,const Task& t2) {
            return t1.getDateTime()>t2.getDateTime();
        }
    );
    return sortedTasks;
}
std::vector<Task> ToDoList::getSortedTasksByDateTimeAscending() const {
    std::vector<Task> sortedTasks = tasks;
    std::sort(sortedTasks.begin(), sortedTasks.end(),
        [](const Task& t1,const Task& t2) {
            return t1.getDateTime()<t2.getDateTime();
        }
    );
    return sortedTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByCompleted(bool completed) const {
    std::vector<Task> filteredTasks;
    for (const auto& task : tasks) {
        if (task.isCompleted()==completed) {
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByDate(const Date& date) const {
    std::vector<Task> filteredTasks;
    for (const auto& task : tasks) {
        if (task.getDateTime().getDate()==date) {
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByLocation(const Location& location) const {
    std::vector<Task> filteredTasks;
    for (const auto& task : tasks) {
        if (task.getLocation()==location) {
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}

void ToDoList::saveToFile() const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            task.save(file);
        }
        file.close();
    } else {
        cerr << "ERRORE: Impossibile aprire il file per il salvataggio." << endl;
    }
}
void ToDoList::loadFromFile() {
    std::ifstream file(filename);
    if (file.is_open()) {
        tasks.clear();
        std::string templine;
        while (std::getline(file,templine)) {
            if (templine.empty()) continue;
            std::stringstream linestream(templine);
            try {
                Task temp("Placeholder",DateTime(1,1,1582,00,00,00),Location("Placeholder"));
                temp.load(linestream);
                if (!linestream.fail()) { tasks.push_back(temp); }
            } catch (const std::invalid_argument& e) {
                cerr << "Skipping corrupted task line (Invalid Data): " << e.what() << endl;
            } catch (const std::runtime_error& e) {
                cerr << "Skipping corrupted task line: " << e.what() << endl;
            }
        }
        file.close();
    }
}

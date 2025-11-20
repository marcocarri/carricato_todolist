#include "../inc/ToDoList.h"

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

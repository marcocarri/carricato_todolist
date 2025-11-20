#include "../inc/ToDoList.h"

using namespace std;

ToDoList::ToDoList() {
    loadFromFile();
}
ToDoList::~ToDoList() {
    saveToFile();
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

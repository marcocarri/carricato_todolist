#include "../inc/ToDoList.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <stdexcept>

using namespace std;

//costruttore
ToDoList::ToDoList() {
    loadFromFile(); //al momento della chiamata del construttore vengono caricate nella lista tutte le informazioni contenute sul file
}
//distruttore
ToDoList::~ToDoList() {
    saveToFile(); //al momento della chiamata del distruttore viene caricato sul file tutte le informazioni contenute nella lista
}

//metodi di stampa
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

//getter
const std::vector<Task>& ToDoList::getTasks() const {
    return this->tasks;
};
const std::string& ToDoList::getFileName() const {
    return this->filename;
}

//setter
void ToDoList::setTasks(const std::vector<Task>& tasks) {
    this->tasks=tasks;
}

//metodi per lavorare con il vettore
void ToDoList::addTask(const std::string &description, const DateTime &date_time, const Location &location) {
    tasks.push_back(Task(description,date_time,location)); //inserisce la task in fondo al vettore
}
void ToDoList::removeTask(size_t index) {
    if (index>=tasks.size()) { //controllo che l'indice sia corretto
        throw std::out_of_range("Indice task non valido.");
    }
    tasks.erase(tasks.begin()+index);
}
Task& ToDoList::getTask(size_t index) {
    if (index>=tasks.size()) { //controllo che l'indice sia corretto
        throw std::out_of_range("Indice task non valido.");
    }
    return tasks.at(index);
}

//metodi di ordinamento e filtro
// --> in questi metodi vado ad utilizzare gli operatori di confronto di cui ho fatto override nelle altre classi
std::vector<Task> ToDoList::getSortedTasksByDateTimeDescending() const { //metodo che restituisce un vettore di task ordinato per data decrescente
    std::vector<Task> sortedTasks = tasks; //creo vettore ordinato che verra restituito, è una copia di tasks su cui effettuerò l'ordinamento
    std::sort(sortedTasks.begin(), sortedTasks.end(),
        [](const Task& t1,const Task& t2) { //utilizzo sort e inserisco la logica di ordinamento che voglio venga usata
            return t1.getDateTime()>t2.getDateTime();
        }
    );
    return sortedTasks;
}
std::vector<Task> ToDoList::getSortedTasksByDateTimeAscending() const { //metodo che restituisce un vettore di task ordinato per data crescente
    std::vector<Task> sortedTasks = tasks; //creo vettore ordinato che verra restituito, è una copia di tasks su cui effettuerò l'ordinamento
    std::sort(sortedTasks.begin(), sortedTasks.end(),
        [](const Task& t1,const Task& t2) { //utilizzo sort e inserisco la logica di ordinamento che voglio venga usata
            return t1.getDateTime()<t2.getDateTime();
        }
    );
    return sortedTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByCompleted(bool completed) const { //metodo che restituisce un vettore di task filtrato in base a completed
    std::vector<Task> filteredTasks; //creo vettore filtrato che verra restituito
    for (const auto& task : tasks) { //foreach
        if (task.isCompleted()==completed) { //verifica che ogni singola task rispetti la condizione di filtro
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByDate(const Date& date) const { //metodo che restituisce un vettore di task filtrato in base a date
    std::vector<Task> filteredTasks; //creo vettore filtrato che verra restituito
    for (const auto& task : tasks) { //foreach
        if (task.getDateTime().getDate()==date) { //verifica che ogni singola task rispetti la condizione di filtro
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}
std::vector<Task> ToDoList::getFilteredTasksByLocation(const Location& location) const { //metodo che restituisce un vettore di task filtrato in base a location
    std::vector<Task> filteredTasks; //creo vettore filtrato che verra restituito
    for (const auto& task : tasks) { //foreach
        if (task.getLocation()==location) { //verifica che ogni singola task rispetti la condizione di filtro
            filteredTasks.push_back(task);
        }
    }
    return filteredTasks;
}

//metodi I/O (persistenza sul disco)
void ToDoList::saveToFile() const { //metodo per la scrittura su file
    std::ofstream file(filename); //apro il file in modalità scrittura
    if (file.is_open()) { //controllo l'apertura sia andata a buon fine
        for (const auto& task : tasks) { //foreach che su ogni singola task invoca save --> salva ogni singola task sul file
            task.save(file);
        }
        file.close(); //chiude il file
    } else {
        cerr << "ERRORE: Impossibile aprire il file per il salvataggio." << endl;
    }
}
void ToDoList::loadFromFile() { //metodo per la lettura da file
    std::ifstream file(filename); //apro il file in modalita lettura
    if (file.is_open()) { //controllo l'apertura sia andata a buon fine
        tasks.clear(); //svuoto il vettore per evitare errori
        std::string templine; //variabile di appoggio per le varie righe del file che vado a leggere
        while (std::getline(file,templine)) { //while che cicla ogni riga del file --> per ogni ciclo su line viene salvata una riga diversa fino alla fine del file
            if (templine.empty()) continue; //se line è vuota salto al prossimo ciclo di while
            std::stringstream linestream(templine);  //trasformo line in uno stream per poter usare >> per estrarre le informazioni
            try {
                Task temp("Placeholder",DateTime(1,1,1582,00,00,00),Location("Placeholder")); //variabile temporanea su cui verrano inseriti i dati letti dal file
                temp.load(linestream); //carico i dati letti dalla line
                if (!linestream.fail()) { tasks.push_back(temp); } //inserisco la task con i dati letti nel vettore
            } catch (const std::invalid_argument& e) {
                cerr << "Skipping corrupted task line (Invalid Data): " << e.what() << endl;
            } catch (const std::runtime_error& e) {
                cerr << "Skipping corrupted task line: " << e.what() << endl;
            }
        }
        file.close(); //chiudo il file
    }
}

#include "../inc/Task.h"

#include <sstream>

//costruttore
Task::Task(const std::string& description,const DateTime& date_time,const Location& location) : description(description),date_time(date_time),location(location) {}

//toString
std::string Task::toString() const { //stampo la task nel formato --> Date & Time: GG-MM-AAAA HH:MM:SS; Location: location; Completed: 1/0; Description: description
    std::ostringstream toString;
    toString << "Date & Time: " << this->date_time.toString() << "; Location: " << this->location.getAddress() << "; Completed: ";
    if (this->completed) toString << "yes; Description: " << this->description;
    else toString << "no; Description: " << this->description;
    return toString.str();
}

//getter
const std::string& Task::getDescription() const {
    return this->description;
}
bool Task::isCompleted() const {
    return this->completed;
}
const DateTime& Task::getDateTime() const {
    return this->date_time;
}
const Location& Task::getLocation() const {
    return this->location;
}

//setter
void Task::setDescription(const std::string& description) {
    this->description=description;
}
void Task::markCompleted() {
    this->completed=true;
}
void Task::markPending() {
    this->completed=false;
}
void Task::setDateTime(const DateTime &date_time) {
    this->date_time=date_time;
}
void Task::setLocation(const Location& location) {
    this->location=location;
}

//il formato di scrittura di una task sul file è il seguente:
//date|time|location|completed|description
// --> | è il carattere separatore che divide le informazioni della task nella stringa che scriviamo sul file, ogni task è su una propria riga
// --> date è la data della task, è una stringa scritta nel formato GG-MM-AAAA
// --> time è l'orario della task, è una stringa scritta nel formato HH:MM:SS
// --> location è il luogo della task, è una stringa che indica l'indirizzo
// --> completed indica lo stato di completamento della task, è un boolean (true/false che una volta tradotto in stringa diventa 1/0):
// --> description è la descrizione della task, è una stringa

//metodi I/O
void Task::save(std::ostream& outstream) const { //metodo per la scrittura su disco
    std::string output=""; //stringa che andrò a scrivere sul file
    output+=this->date_time.getDate().toString()+"|"+this->date_time.getTime().toString()+"|"+this->location.getAddress()+"|"+std::to_string(this->completed)+"|"+this->description;
    outstream << output << std::endl; //scrivo la stringa sul file è concateno endl, ogni task è scritta su una propria riga
}
void Task::load(std::istream& instream) { //metodo per la lettura su disco
    std::string date, time, location, completed; //variabili temporanee in cui salvo la stringa e la location che ottengo dalla lettura
    if (!std::getline(instream,date,'|')) return; //leggo la riga fino a che non trovo | e salvo ciò che leggo in date
    if (!std::getline(instream,time,'|')) return; //leggo la riga fino a che non trovo | e salvo ciò che leggo in time
    try {
        this->date_time=DateTime(date,time); //assegno alla variabile dateTime il suo valore
    } catch (const std::invalid_argument&) {
        instream.setstate(std::ios::failbit);
        return;
    }
    if (!std::getline(instream,location,'|')) return; //leggo la riga fino a che non trovo | e salvo ciò che leggo in location
    this->location=Location(location); //assegno alla variabile location il suo valore
    if (!std::getline(instream,completed,'|')) return; //leggo la riga fino a che non trovo | e salvo ciò che leggo in completed
    if (completed.compare("1")==0) this->completed=true; //assegno alla variabile completed il suo valore analizzando ciò che ho salvato in completed(stringa)
    else this->completed=false;
    if (!std::getline(instream,description)) return; //leggo il rimanente della riga e salvo in description
    //ogni if oltre ad estrapolare un valore della task controlla che la lettura del valore vada a buon fine, se ciò non avviene il return fa terminare la lettura bruscamente
}

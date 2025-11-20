#include "inc/ToDoList.h"

#include <iostream>
#include <limits>

using namespace std;

//funzioni di input
std::string readStringInput(const string& prompt); //legge input quando devo inserire una stringa
Date readDateInput(const string& prompt); //legge input quando vado ad inserire una data e restituisce un oggetto date
TimeOfDay readTimeInput(const string& prompt); //legge input quando vado ad inserire una data e restituisce un oggetto time
Location readLocationInput(const string& prompt); //legge input quando vado ad inserire un luogo e restituisce un oggetto location
size_t readIndex(const string& prompt,size_t maxIndex); //legge input quando vado ad inserire un indice
void clearInputBuffer(); //pulisce il buffer di input in caso di errore di lettura

//funzioni utility
DateTime getCurrentDateTime(); //restituisce un oggetto DateTime con la data e l'orario attuale

//funzioni di display
void displayMainMenu(); //stampa menù principale
void displaySubMenu1(); //stampa menù di completamento task
void displaySubMenu2(); //stampa menù di modifica task
void displaySubMenu3(); //stampa menù di sorting/filtering dell'elenco delle task

//1 aggiungere task
//2 rimuovere task
//3 completare task
//  3.1 completa task a scelta
//  3.2 completa tutte le task NON completate con data antecedente a quella attuale
//  3.0 torna indietro
//4 modificare task
//  4.1 modificare data
//  4.2 modificare orario
//  4.3 modificare luogo
//  4.4 modificare descrizione
//  4.5 modificare completamento
//  4.0 torna indietro
//5 visualizzare elenco task
//  5.1 visualizzare elenco
//  5.2 visualizzare elenco task ordinate dalla data più recente
//  5.3 visualizzare elenco task ordinate dalla data meno recente
//  5.4 visualizzare elenco task non completate
//  5.5 visualizzare elenco task completate
//  5.6 visualizzare elenco task in una determinata data
//  5.7 visualizzare elenco task in un determinato luogo
//  5.0 torna indietro
//0 esci

int main() {
    ToDoList list;
    cout << endl << "ToDoList: " << list.getFileName() << " caricata" << endl << endl;
    int choice=-1, sub_choice=-1;

    while (choice!=0) {
        displayMainMenu();
        cout << "Scelta: ";
        if (!(cin >> choice)) { clearInputBuffer(); continue; } //controllo che la lettura avvenga correttamente
        try {
            switch (choice) {
                case 1: { //aggiungere task
                    string description = readStringInput("Inserisci la descrizione della nuova Task: ");
                    Date tempDate=readDateInput("Inserisci la data (GG-MM-AAAA): ");
                    TimeOfDay tempTime=readTimeInput("Inserisci l'orario (HH:MM:SS): ");
                    DateTime date_time(tempDate,tempTime);
                    Location location = readLocationInput("Inserisci il luogo: ");
                    list.addTask(description, date_time, location);
                    cout << "Task aggiunta con successo!" << endl;
                } break;
                case 2: { //rimuovere task
                    if (list.getTasks().empty()) { //se il vettore è vuoto usciamo dal case
                        cout << "Nessuna task presente nella lista." << endl;
                        break;
                    }
                    cout << list.vectorToString(list.getTasks()) << endl;
                    size_t index=readIndex("Inserisci il numero della Task da rimuovere: ",list.getTasks().size());
                    Task temp=list.getTask(index-1); //mi salvo la task in una variabile temporanea
                    list.removeTask(index-1); //rimuovo la task
                    cout << "Dati Task da rimuovere --> " << temp.toString() << endl << "Task rimossa con successo!" << endl;
                } break;
                case 3: { //completare task
                    displaySubMenu1();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; } //controllo che la lettura avvenga correttamente
                    switch (sub_choice) {
                        case 1: { //completare task a scelta
                            if (list.getTasks().empty()) { //se il vettore è vuoto usciamo dal case
                                cout << "Nessuna task presente nella lista." << endl;
                                break;
                            }
                            cout << list.vectorToString(list.getTasks()) << endl;
                            size_t index=readIndex("Inserisci il numero della Task da completare: ",list.getTasks().size());
                            list.getTask(index-1).markCompleted(); //segno la task come completa
                            cout << "Task [" << index << "] segnata come completata!" << endl;
                        } break;
                        case 2: { //auto-complete task vecchie
                            for (size_t i=0;i<list.getTasks().size();i++) {
                                Task& task=list.getTask(i);
                                if (!(task.isCompleted())&&(task.getDateTime()<getCurrentDateTime())) { task.markCompleted(); }
                            }
                            cout << "Task con data antecedente a quella attuale completate!" << endl;
                        } break;
                        case 0: { /*torna indietro*/ } break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 4: { //modificare task
                    displaySubMenu2();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; } //controllo che la lettura avvenga correttamente
                    size_t index=-1;
                    if (!(sub_choice==0)) {
                        if (list.getTasks().empty()) { //se il vettore è vuoto usciamo dal case
                            cout << "Nessuna task presente nella lista." << endl;
                            break;
                        }
                        cout << list.vectorToString(list.getTasks()) << endl;
                        index=readIndex("Inserisci il numero della Task da modificare: ",list.getTasks().size());
                        if (index==0) break; //per evitare che si verifichino errori se viene inserito un index errato se index==0 esco dal case
                    }
                    switch (sub_choice) {
                        case 1: { //modifica data
                            Date date=readDateInput("Inserisci la nuova data (GG-MM-AAAA): ");
                            Task& task=list.getTask(index-1);
                            task.setDateTime(DateTime(date,task.getDateTime().getTime()));
                            cout << "Data aggiornata con successo!" << endl;
                        } break;
                        case 2: { //modifica orario
                            TimeOfDay time=readTimeInput("Inserisci il nuovo orario (HH:MM:SS): ");
                            Task& task=list.getTask(index-1);
                            task.setDateTime(DateTime(task.getDateTime().getDate(),time));
                            cout << "Orario aggiornato con successo!" << endl;
                        } break;
                        case 3: { //modifica luogo
                            Location location=readLocationInput("Inserisci il nuovo luogo: ");
                            Task& task=list.getTask(index-1);
                            task.setLocation(location);
                            cout << "Luogo aggiornato con successo!" << endl;
                        } break;
                        case 4: { //modifica descrizione
                            std::string description=readStringInput("Inserisci la nuova descrizione: ");
                            Task& task=list.getTask(index-1);
                            task.setDescription(description);
                            cout << "Descrizione aggiornata con successo!" << endl;
                        } break;
                        case 5: { //modifica completamento
                            Task& task=list.getTask(index-1);
                            size_t temp=readIndex("Imposta la task come: 1 - Completata; 2 - Non Completata",2);
                            if (temp==1) task.markCompleted();
                            else if (temp==2) task.markPending();
                            else { cout << "Operazione annullata (Input non valido)." << endl; break;} //verifica che l'utente abbia inserito 1 oppure 2
                            cout << "Completamento della Task aggiornato con successo!" << endl;
                        } break;
                        case 0: { /*torna indietro*/ } break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 5: { //visualizzare elenco task
                    displaySubMenu3();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; } //controllo che la lettura avvenga correttamente
                    switch (sub_choice) {
                        case 1: { //visualizza elenco task
                            cout << list.toString() << endl;
                        } break;
                        case 2: { //visualizza elenco task ordinata per data decrescente
                            cout << list.vectorToString(list.getSortedTasksByDateTimeDescending()) << endl;
                        } break;
                        case 3: { //visualizza elenco task ordinata per data crescente
                            cout << list.vectorToString(list.getSortedTasksByDateTimeAscending()) << endl;
                        } break;
                        case 4: { //visualizza elenco task completate
                            cout << list.vectorToString(list.getFilteredTasksByCompleted(true)) << endl;
                        } break;
                        case 5: { //visualizza elenco task NON completate
                            cout << list.vectorToString(list.getFilteredTasksByCompleted(false)) << endl;
                        } break;
                        case 6: { //visualizza elenco task in un determinata data
                            Date date=readDateInput("Inserisci la data (GG-MM-AAAA) di cui vuoi sapere le task: ");
                            cout << list.vectorToString(list.getFilteredTasksByDate(date)) << endl;
                        } break;
                        case 7: { //visualizza elenco task in un determinato luogo
                            Location location=readLocationInput("Inserisci il luogo di cui vuoi sapere le task: ");
                            cout << list.vectorToString(list.getFilteredTasksByLocation(location)) << endl;
                        } break;
                        case 0: { /*torna indietro*/ } break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 0: { //esci
                    cout << "Salvataggio e chiusura. Arrivederci!" << endl;
                } break;
                default : {
                    cout << "Scelta non valida. Riprova." << endl;
                } break;
            }
        } catch (const std::out_of_range& e) {
            cerr << endl << "Errore: " << e.what() << endl;
        } catch (const std::invalid_argument& e) {
            cerr << endl << "Errore di Input: " << e.what() << endl;
        } catch (const std::exception& e) {
            cerr << endl << "Errore inatteso: " << e.what() << endl;
        }
        cout << endl;
    }
    return 0;
}

//funzioni di input
size_t readIndex(const string& prompt, size_t maxIndex) {
    if (maxIndex==0) return 0; //se maxIndex=0 returna obbligatoriamente 0
    int index;
    cout << prompt;
    if (!(cin >> index)||index<=0||(size_t)index>maxIndex) { //verifica che l'inserimento sia corretto
        clearInputBuffer();
        cout << "Numero non valido. Deve essere tra 1 e " << maxIndex << endl;
        return 0;
    }
    return (size_t)index;
}
std::string readStringInput(const string& prompt) {
    string string;
    cout << prompt;
    getline(cin >> ws,string);
    return string;
}
Date readDateInput(const string& prompt) {
    while (true) { //while continua finchè non viene inserita una data corretta
        try {
            return Date(readStringInput(prompt));
        } catch (const std::invalid_argument& e) {
            cerr << "Errore Data: " << e.what() << " Riprova." << endl;
        }
    }
}
TimeOfDay readTimeInput(const string& prompt) {
    while (true) { //while continua finchè non viene inserita un'orario corretto
        try {
            return TimeOfDay(readStringInput(prompt));
        } catch (const std::invalid_argument& e) {
            cerr << "Errore Orario: " << e.what() << " Riprova." << endl;
        }
    }
}
Location readLocationInput(const string& prompt) {
    return Location(readStringInput(prompt));
}
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "Input non valido. Riprova." << endl;
}

//funzioni utility
DateTime getCurrentDateTime() {
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo=localtime(&rawtime);
    Date date(timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900);
    TimeOfDay time(timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
    return DateTime(date,time);
}

//funzioni di display
void displayMainMenu() {
    cout << "---- GESTIONE TASK LIST ----" << endl;
    cout << " 1  | Aggiungere Task" << endl;
    cout << " 2  | Rimuovere Task" << endl;
    cout << " 3  | Completare Task (apre sub-menu)" << endl;
    cout << " 4  | Modificare Task (apre sub-menu)" << endl;
    cout << " 5  | Visualizzare elenco Task (apre sub-menu)" << endl;
    cout << " 0  | Esci" << endl;
    cout << "----------------------------" << endl;
}
void displaySubMenu1() {
    cout << "---- gestione completamento Task ----" << endl;
    cout << " 1  | Completa Task a scelta" << endl;
    cout << " 2  | Completa tutte le Task NON completate con data antecedente a quella attuale" << endl;
    cout << " 0  | Torna indietro" << endl;
    cout << "----------------------------" << endl;
}
void displaySubMenu2() {
    cout << "---- gestione modifica Task ----" << endl;
    cout << " 1  | Modificare data di una Task" << endl;
    cout << " 2  | Modificare orario di una Task" << endl;
    cout << " 3  | Modificare luogo di una Task" << endl;
    cout << " 4  | Modificare descrizione di una Task" << endl;
    cout << " 5  | Modificare completamento di una Task" << endl;
    cout << " 0  | Torna indietro di una Task" << endl;
    cout << "----------------------------" << endl;
}
void displaySubMenu3() {
    cout << "---- gestione visualizzazione Task ----" << endl;
    cout << " 1  | Visualizza elenco Task" << endl;
    cout << " 2  | Visualizza elenco Task ordinate per data descrescente" << endl;
    cout << " 3  | Visualizza elenco Task ordinate per data crescente" << endl;
    cout << " 4  | Visualizza elenco Task completate" << endl;
    cout << " 5  | Visualizza elenco Task non completate" << endl;
    cout << " 6  | Visualizza elenco Task in una determinata data" << endl;
    cout << " 7  | Visualizza elenco Task in un determinato luogo" << endl;
    cout << " 0  | Torna indietro" << endl;
    cout << "----------------------------" << endl;
}

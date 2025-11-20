#include "inc/ToDoList.h"

#include <iostream>
#include <limits>

using namespace std;

std::string readStringInput(const string& prompt);
Date readDateInput(const string& prompt);
TimeOfDay readTimeInput(const string& prompt);
Location readLocationInput(const string& prompt);
size_t readIndex(const string& prompt,size_t maxIndex);
void clearInputBuffer();
DateTime getCurrentDateTime();
void displayMainMenu();
void displaySubMenu1();
void displaySubMenu2();
void displaySubMenu3();

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
        if (!(cin >> choice)) { clearInputBuffer(); continue; }
        try {
            switch (choice) {
                case 1: {
                    string description = readStringInput("Inserisci la descrizione della nuova Task: ");
                    Date tempDate=readDateInput("Inserisci la data (GG-MM-AAAA): ");
                    TimeOfDay tempTime=readTimeInput("Inserisci l'orario (HH:MM:SS): ");
                    DateTime date_time(tempDate,tempTime);
                    Location location = readLocationInput("Inserisci il luogo: ");
                    list.addTask(description, date_time, location);
                    cout << "Task aggiunta con successo!" << endl;
                } break;
                case 2: {
                    if (list.getTasks().empty()) {
                        cout << "Nessuna task presente nella lista." << endl;
                        break;
                    }
                    cout << list.vectorToString(list.getTasks()) << endl;
                    size_t index=readIndex("Inserisci il numero della Task da rimuovere: ",list.getTasks().size());
                    Task temp=list.getTask(index-1);
                    list.removeTask(index-1);
                    cout << "Dati Task da rimuovere --> " << temp.toString() << endl << "Task rimossa con successo!" << endl;
                } break;
                case 3: {
                    displaySubMenu1();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; }
                    switch (sub_choice) {
                        case 1: {
                            if (list.getTasks().empty()) {
                                cout << "Nessuna task presente nella lista." << endl;
                                break;
                            }
                            cout << list.vectorToString(list.getTasks()) << endl;
                            size_t index=readIndex("Inserisci il numero della Task da completare: ",list.getTasks().size());
                            list.getTask(index-1).markCompleted();
                            cout << "Task [" << index << "] segnata come completata!" << endl;
                        } break;
                        case 2: {
                            for (size_t i=0;i<list.getTasks().size();i++) {
                                Task& task=list.getTask(i);
                                if (!(task.isCompleted())&&(task.getDateTime()<getCurrentDateTime())) { task.markCompleted(); }
                            }
                            cout << "Task con data antecedente a quella attuale completate!" << endl;
                        } break;
                        case 0: {} break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 4: {
                    displaySubMenu2();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; }
                    size_t index=-1;
                    if (!(sub_choice==0)) {
                        if (list.getTasks().empty()) {
                            cout << "Nessuna task presente nella lista." << endl;
                            break;
                        }
                        cout << list.vectorToString(list.getTasks()) << endl;
                        index=readIndex("Inserisci il numero della Task da modificare: ",list.getTasks().size());
                        if (index==0) break;
                    }
                    switch (sub_choice) {
                        case 1: {
                            Date date=readDateInput("Inserisci la nuova data (GG-MM-AAAA): ");
                            Task& task=list.getTask(index-1);
                            task.setDateTime(DateTime(date,task.getDateTime().getTime()));
                            cout << "Data aggiornata con successo!" << endl;
                        } break;
                        case 2: {
                            TimeOfDay time=readTimeInput("Inserisci il nuovo orario (HH:MM:SS): ");
                            Task& task=list.getTask(index-1);
                            task.setDateTime(DateTime(task.getDateTime().getDate(),time));
                            cout << "Orario aggiornato con successo!" << endl;
                        } break;
                        case 3: {
                            Location location=readLocationInput("Inserisci il nuovo luogo: ");
                            Task& task=list.getTask(index-1);
                            task.setLocation(location);
                            cout << "Luogo aggiornato con successo!" << endl;
                        } break;
                        case 4: {
                            std::string description=readStringInput("Inserisci la nuova descrizione: ");
                            Task& task=list.getTask(index-1);
                            task.setDescription(description);
                            cout << "Descrizione aggiornata con successo!" << endl;
                        } break;
                        case 5: {
                            Task& task=list.getTask(index-1);
                            size_t temp=readIndex("Imposta la task come: 1 - Completata; 2 - Non Completata",2);
                            if (temp==1) task.markCompleted();
                            else if (temp==2) task.markPending();
                            else { cout << "Operazione annullata (Input non valido)." << endl; break;}
                            cout << "Completamento della Task aggiornato con successo!" << endl;
                        } break;
                        case 0: {} break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 5: {
                    displaySubMenu3();
                    cout << "Scelta: ";
                    if (!(cin >> sub_choice)) { clearInputBuffer(); continue; }
                    switch (sub_choice) {
                        case 1: {
                            cout << list.toString() << endl;
                        } break;
                        case 2: {
                            cout << list.vectorToString(list.getSortedTasksByDateTimeDescending()) << endl;
                        } break;
                        case 3: {
                            cout << list.vectorToString(list.getSortedTasksByDateTimeAscending()) << endl;
                        } break;
                        case 4: {
                            cout << list.vectorToString(list.getFilteredTasksByCompleted(true)) << endl;
                        } break;
                        case 5: {
                            cout << list.vectorToString(list.getFilteredTasksByCompleted(false)) << endl;
                        } break;
                        case 6: {
                            Date date=readDateInput("Inserisci la data (GG-MM-AAAA) di cui vuoi sapere le task: ");
                            cout << list.vectorToString(list.getFilteredTasksByDate(date)) << endl;
                        } break;
                        case 7: {
                            Location location=readLocationInput("Inserisci il luogo di cui vuoi sapere le task: ");
                            cout << list.vectorToString(list.getFilteredTasksByLocation(location)) << endl;
                        } break;
                        case 0: {} break;
                        default : {
                            cout << "Scelta non valida. Riprova." << endl;
                        } break;
                    }
                } break;
                case 0: {
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

size_t readIndex(const string& prompt, size_t maxIndex) {
    if (maxIndex==0) return 0;
    int index;
    cout << prompt;
    if (!(cin >> index)||index<=0||(size_t)index>maxIndex) {
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
    while (true) {
        try {
            return Date(readStringInput(prompt));
        } catch (const std::invalid_argument& e) {
            cerr << "Errore Data: " << e.what() << " Riprova." << endl;
        }
    }
}
TimeOfDay readTimeInput(const string& prompt) {
    while (true) {
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
DateTime getCurrentDateTime() {
    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo=localtime(&rawtime);
    Date date(timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900);
    TimeOfDay time(timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
    return DateTime(date,time);
}
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

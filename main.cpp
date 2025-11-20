#include "inc/ToDoList.h"

#include <iostream>

using namespace std;

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

    return 0;
}
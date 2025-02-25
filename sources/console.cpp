//
// Created by dan gaspar on 02.04.2024.
//

#include "../headers/console.h"
#include <iostream>
#include <string>


using std::cout;
using std::string;
using std::cin;

void checkInteger(string str){
    for (auto it = str.begin(); it != str.end(); ++it){
        if (!isdigit(*it)){
            throw ValidatorException("Invalid input. Please introduce an integer.");
        }
    }
}

void Console::menu() {
    cout << "Hey. App to manage touristic offers. Options: \n";
    cout << "Add Offer(cmd: add) \n";
    cout << "Delete (cmd: delete)\n";
    cout << "Modify (cmd: modify)\n";
    cout << "Find (cmd: find)\n";
    cout << "Show (cmd: show)\n";
    cout << "Sort (cmd: sort)\n";
    cout << "Exit (cmd: exit)\n";
    cout << "Filter (cmd: filter)\n";
    cout << "Wishlist (cmd: wishlist)\n";
    cout << "Undo (cmd: undo)\n";
    cout << "-----------------------------------------------\n";
}

void Console::addOffer() {
    cout << "Introduce name, destination, type and price\n";
    cout << "Name: ";
    string name;
    cin >> name;
    cout << "Destination: ";
    string destination;
    cin >> destination;
    cout << "Type: ";
    string type;
    cin >> type;
    cout << "Price: ";
    string price;
    cin >> price;
    try {
        checkInteger(price);
        int price_int = stoi(price);
        srv.addOffer(name, destination, type, price_int);
    }
    catch (const ValidatorException &ex) {
        cout << ex;
        return;
    }
    catch (const RepoException &ex) {
        cout << ex;
        return;
    }
    cout << "Adaugat cu succes!\n";
}

void Console::printOffer(Offer& off) {
    cout << "Name: " << off.getName() << " ";
    cout << "Destination: " << off.getDestination() << " ";
    cout << "Type: " << off.getType() << " ";
    cout << "Price: " << off.getPrice() << "\n";
}

void Console::findOffer() {
    cout << "Introduce name of the offer you are looking for: ";
    string name;
    cin >> name;
    try {
        Offer& off = srv.serv_findOffer(name);
        printOffer(off);
    }
    catch (const RepoException &ex) {
        cout << ex;
        return;
    }
    cout << "Cautare efectuata cu succes!\n";
}

void Console::ui_deleteOffer() {
    cout << "Introduce name of the offer you want to delete: ";
    string name;
    cin >> name;
    try {
        srv.deleteOffer(name);
    }
    catch (const RepoException &ex) {
        cout << ex;
        return;
    }
    cout << "Oferta stearsa cu succes!\n";
}

void Console::ui_modifyOffer(){
    cout << "Introduce name of the offer you want to modify: ";
    string name; cin >> name;
    cout << "Introduce new name, destination, type and price\n";
    cout << "Name: ";
    string newName; cin >> newName;
    cout << "Destination: ";
    string destination; cin >> destination;
    cout << "Type: ";
    string type; cin >> type;
    cout << "Price: ";
    string price;
    cin >> price;
    try {
        checkInteger(price);
        int price_int = stoi(price);
        srv.serv_modifyOffer(name, newName, destination, type, price_int);
    }
    catch (const ValidatorException &ex) {
        cout << ex;
        return;
    }
    catch (const RepoException &ex) {
        cout << ex;
        return;
    }
    cout << "Modificare efectuata cu succes!\n";
}

void Console::ui_showOffers(){
    ui_printVectorOfOffers(srv.serv_getAll());
}

void Console::ui_printVectorOfOffers(vector<Offer>& offers){
    for (auto it = offers.begin(); it != offers.end(); ++it){
        printOffer(*it);
    }
}

void Console::ui_filter(){
    int end = 1;
    while(end) {
        cout << "You want it filter by destination or price: ";
        string condition;
        cin >> condition;
        if (condition == "destination"){
            string destination; cout << "What's the destination: "; cin >> destination;
            //vector<Offer> result = srv.serv_getFiltered("destination", destination);
            vector<Offer> result = srv.serv_filterByDestinationWithCopyIf(destination);
            for (auto it = result.begin(); it != result.end(); ++it){
                printOffer(*it);
            }
            end = 0;
        }
        else if (condition == "price"){
            int price; cout << "What's the price: "; cin >> price;
            vector<Offer> result = srv.serv_filterByPriceWithCopyIf(price);
            for (auto it = result.begin(); it != result.end(); ++it){
                printOffer(*it);
            }
            end = 0;
        }
        else {
            cout << "Invalid filter. Try again.";
        }
    }
}

void Console::ui_sort(){
    int end = 1;
    while(end) {
        cout << "You want to sort by price, name, destination or type: ";
        string condition;
        cin >> condition;
        if (condition == "price"){
            vector<Offer> result = srv.sortByPrice();
            ui_printVectorOfOffers(result);
            end = 0;
        }
        else if (condition == "name"){
            vector<Offer> result = srv.sortByName();
            ui_printVectorOfOffers(result);
            end = 0;
        }
        else if (condition == "destination"){
            vector<Offer> result = srv.sortByDestination();
            ui_printVectorOfOffers(result);
            end = 0;
        }
        else if (condition == "type"){
            vector<Offer> result = srv.sortByType();
            ui_printVectorOfOffers(result);
            end = 0;
        }
        else {
            cout << "Invalid sort. Try again.";
        }
    }
}

void Console::ui_showWishList(){
    ui_printVectorOfOffers(srv.getWishlist());
}

void Console::ui_exportWishlist(){
    cout << "Introduce the name of the file where the export will be stored: ";
    string file_name; cin >> file_name;
    file_name += ".html";

    srv.exportWishlist(file_name);
}

void Console::generateWishlist(){
    cout << "Introduce the number of offers you want to generate: ";
    int nr; cin >> nr;

    srv.generateWishlist(nr);
}

void Console::wishlist(){
    cout << "What do you want to do: add, empty, generate sau export\n";
    cout << ">> ";
    string option; cin >> option;
    if (option == "add"){
        cout << "Offers available: \n"; ui_showOffers();
        cout << "Introduce name of the offer you want to add to wishlist: ";
        string name; cin >> name;
        try {
            srv.addWishlist(name);
        }
        catch (const RepoException &ex) {
            cout << ex;
            return;
        }
        cout << "Offer added to wishlist!\n";
    } else if (option == "empty") {
        try {
            srv.emptyWishlist();
        }
        catch (const RepoException &ex) {
            cout << ex;
            return;
        }
        cout << "Wishlist empty!\n";
    } else if (option == "generate") {
        generateWishlist();
    } else if (option == "export") {
        ui_exportWishlist();
    } else if (option == "show"){
        cout << "Wishlist:\n";
        ui_showWishList();
        cout << '\n';
    } else {
        cout << "Invalid option. Try again.\n";
    }
}

void Console::undo() {
    try {
        srv.undo();
    }
    catch (const RepoException &ex){
        cout << ex;
        return;
    }
    cout << "Undo done!\n";
}

void Console::start() {
    menu();
    while (true) {
        string cmd;
        cout << "command >>> ";
        cin >> cmd;
        if (cmd == "exit") {
            cout << "Bye!";
            return;
        } else if (cmd == "find") {
            findOffer();
        } else if (cmd == "add") {
            addOffer();
        } else if (cmd == "delete") {
            ui_deleteOffer();
        } else if (cmd == "modify") {
            ui_modifyOffer();
        } else if (cmd == "show") {
            ui_showOffers();
        } else if (cmd == "filter") {
            ui_filter();
        } else if (cmd == "sort"){
            ui_sort();
        } else if (cmd == "wishlist"){
            wishlist();
        } else if (cmd == "undo"){
            undo();
        } else {
            cout << "Invalid command. Try again.\n";
        }
    }
}
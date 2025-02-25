//
// Created by dan gaspar on 26.04.2024.
//

#include "../headers/FileRepository.h"
#include <fstream>

void FileRepository::saveToFile() {
    std::ofstream out(this->file_name);
    vector <Offer> offers = repo_getAll();
    for (auto it = offers.begin(); it != offers.end(); ++it)
        out << it->getName() + ";" + it->getDestination() + ";" + it->getType() + ";" + std::to_string(it->getPrice()) + '\n';
}

void FileRepository::readFromFile() {
    std::ifstream in(this->file_name);
    string line;

    string name, destination, type;
    int price;
    while (in >> line){
        size_t pos = 0;
        std::string token;

        string delimiter = ";";
        pos = line.find(delimiter);
        name = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        destination = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        type = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());

        pos = line.find(delimiter);
        price = stoi(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());

        Offer off{name, destination, type, price};
        repo_addOffer(off);
    }
}



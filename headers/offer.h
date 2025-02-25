//
// Created by dan gaspar on 02.04.2024.
//
#pragma once

#include <string>
#include <iostream>

using std::string;

class Offer {
private:
    string name;
    string destination;
    string type;
    int price;
public:
    Offer() = default;

    Offer(const string n, const string d, const string t, const int p):name{n}, destination{d}, type{t}, price{p}{}

    Offer(const Offer&other){
        name = other.name;
        destination = other.destination;
        type = other.type;
        price = other.price;
    }

    string getName() const{
        return name;
    }

    string getDestination() const{
        return destination;
    }

    string getType() const {
        return type;
    }

    int getPrice() const {
        return price;
    }
};

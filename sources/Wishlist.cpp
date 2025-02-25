//
// Created by dan gaspar on 05.06.2024.
//

#include "../headers/Wishlist.h"

#include <random>
#include <fstream>

Wishlist::Wishlist() = default;

vector<Offer*> Wishlist::getOffers() {
    return offers;
}

void Wishlist::addOffer(Offer* offer) {
    offers.push_back(offer);
    notify();
}

void Wishlist::empty(){
    offers.clear();
    notify();
}


void Wishlist::random_add(vector<Offer> offers_available, int &count) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, offers_available.size() - 1);
    for (int i = 0; i < count; i++) {
        addOffer(&offers_available[dis(gen)]);
    }

    notify();
}

void Wishlist::save_to_file(string &filename) {
    ofstream file(filename);
    for (auto &offer : offers) {
        file << offer->getName() + ";" + offer->getDestination() + ";" + offer->getType() + ";" + std::to_string(offer->getPrice()) + '\n';
    }
}

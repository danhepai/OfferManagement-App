//
// Created by dan gaspar on 05.06.2024.
//

#pragma once

#include "observer.h"
#include "offer.h"

class Wishlist : public Observable {
private:
    vector<Offer*> offers;

public:

    Wishlist();

    vector<Offer*> getOffers();

    void addOffer(Offer* offer);

    void empty();

    void random_add(vector<Offer> offers_available, int &count);

    void save_to_file(string &filename);
};



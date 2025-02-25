//
// Created by dan gaspar on 02.04.2024.
//

#pragma once
#include "service.h"

class Console{
private:
    Service& srv;

    void menu();

    void addOffer();

    void ui_deleteOffer();

    void findOffer();

    void printOffer(Offer& off);

    void ui_modifyOffer();

    void ui_showOffers();

    void ui_filter();

    void ui_printVectorOfOffers(vector<Offer>& offers);

    void ui_sort();

    void wishlist();

    void ui_showWishList();

    void ui_exportWishlist();

    void generateWishlist();

    void undo();

public:
    Console(Service &serv):srv{serv}{}

    void start();
};

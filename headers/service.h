//
// Created by dan gaspar on 02.04.2024.
//

#pragma once

#include "repository.h"
#include "validator.h"
#include <fstream>
#include <random>
#include "actUndo.h"

using std::unique_ptr;

class Service{
private:
    OffersRepo& repo;
    OfferValidator& validator;

    vector<unique_ptr<actUndo>> undoActions;

public:
    Service(OffersRepo &rep, OfferValidator &val):repo{rep},validator{val}{}

    void addOffer(const string& name, const string& destination, const string& type, int price);

    void deleteOffer(const string& name);

    Offer& serv_findOffer(const string& name);

    void serv_modifyOffer(const string &nameOfOfferToModify, const string& name, const string& destination, const string& type, int price);

    vector<Offer>& serv_getAll();

    vector<Offer>& getWishlist();

    vector<Offer> serv_getFiltered(string condition, string conditional_var);

    vector<Offer> serv_getSorted(bool (*sortFunction)(Offer& off1, Offer& off2));

    vector<Offer> sortByName();

    vector<Offer> sortByDestination();

    vector<Offer> sortByType();

    vector<Offer> sortByPrice();

    vector<Offer> serv_filterByDestinationWithCopyIf(const string conditional_var);

    vector<Offer> serv_filterByPriceWithCopyIf(const int conditional_var);

//    vector<Offer> sortOffersByName();

    void addWishlist(const string name);

    void emptyWishlist();

    void exportWishlist(string file_name);

    void generateWishlist(int nr);

    void saveToFile();

    void undo();
};

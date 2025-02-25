//
// Created by dan gaspar on 02.04.2024.
//
#pragma once
#include <vector>
#include "offer.h"
#include <ostream>
#include "vector.h"

using std::ostream;
using std::vector;

//CRUD -> CREATE, READ, UPDATE, DELETE

class OffersRepo {
private:
    vector<Offer> offers;
    vector<Offer> wishlist;

    bool exist(const Offer &off);

public:
    OffersRepo() = default;

    virtual void repo_addOffer(const Offer &off);

    virtual void repo_deleteOffer(Offer& offToDel);

    vector<Offer>& repo_getAll();

    vector<Offer>& getWishlist();

    Offer& repo_findOffer(string name);

    void addWishlist(Offer &off);

    void emptyWishlist();
};

class RepoException {
private:
    string msg;
public:
    RepoException(string m):msg{ m } {}
    friend ostream& operator<<(ostream& out, const RepoException& ex);
};

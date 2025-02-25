//
// Created by dan gaspar on 02.04.2024.
//

#include "../headers/repository.h"

#include <iostream>

Offer& OffersRepo::repo_findOffer(const string name) {
    for (auto &off : offers)
        if (off.getName() == name)
            return off;

    throw RepoException("Your offer was not found\n");
}


bool OffersRepo::exist(const Offer &off) {
    try{
        repo_findOffer(off.getName());
        return true;
    }
    catch (RepoException &){
        return false;
    }

}

void OffersRepo::repo_addOffer(const Offer &off) {
    if (exist(off))
        throw RepoException("The offer with this name already exist.\n");
    else {
        offers.push_back(off);
    }
}

void OffersRepo::repo_deleteOffer(Offer& offToDel) {
//    for (auto it = offers.begin(); it != offers.end(); ++it) {
//        if (it.element().getName() == offToDel.getName()) {
//            offers.deleteElem(it.pos());
//            return;
//        }
//    }

    for (auto it = offers.begin(); it != offers.end(); ++it) {
        if (it->getName() == offToDel.getName()) {
            offers.erase(it);
            return;
        }
    }

    throw RepoException("Your offer was not found\n");
}

ostream& operator<<(ostream& out, const RepoException& ex) {
    out << ex.msg;
    return out;
}
//HOW TO TEST THIS

//EU NU TREBUIE SA MAI DISTRUG REPO?

vector<Offer>& OffersRepo::repo_getAll(){
    return offers;
}

vector<Offer>& OffersRepo::getWishlist(){
    return wishlist;
}

void OffersRepo::addWishlist(Offer &off) {
    for (auto &of : wishlist)
        if (of.getName() == off.getName())
            throw RepoException("The offer with this name already exist in the wishlist.\n");

    wishlist.push_back(off);
}

void OffersRepo::emptyWishlist() {
    wishlist.clear();
}
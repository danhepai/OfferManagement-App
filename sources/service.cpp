//
// Created by dan gaspar on 02.04.2024.
//

#include "../headers/service.h"

void Service::addOffer(const string& name, const string& destination, const string& type, int price) {
    Offer off{name, destination, type, price};
    validator.validate(off);
    repo.repo_addOffer(off);

    undoActions.push_back(std::make_unique<UndoAdd>(repo, off));
}

void Service::deleteOffer(const string& name) {
    Offer& offToDel = repo.repo_findOffer(name);
    repo.repo_deleteOffer(offToDel);

    undoActions.push_back(std::make_unique<UndoDelete>(repo, offToDel));
}

Offer& Service::serv_findOffer(const string& name) {
    return repo.repo_findOffer(name);
}

vector<Offer>& Service::serv_getAll() {
    return repo.repo_getAll();
}

vector<Offer> Service::serv_getFiltered(string condition, string conditional_var){
    vector<Offer> result;
    vector<Offer>& all_offers = serv_getAll();
    for (const auto& off : all_offers){
        if (condition == "destination"){
            if (off.getDestination() == conditional_var)
                result.push_back(off);
        }
        else {
            if (off.getPrice() == stoi(conditional_var))
                result.push_back(off);
        }
    }
    return result;
}

void Service::serv_modifyOffer(const string &nameOfOfferToModify, const string &name, const string &destination, const string &type,
                               int price) {
    Offer& offToModify = repo.repo_findOffer(nameOfOfferToModify);
    string last_off_name = offToModify.getName();
    string last_off_destination = offToModify.getDestination();
    string last_off_type = offToModify.getType();
    int last_off_price = offToModify.getPrice();
    Offer off{name, destination, type, price};
    validator.validate(off);
    repo.repo_deleteOffer(offToModify);
    repo.repo_addOffer(off);

    undoActions.push_back(std::make_unique<UndoModify>(repo, off, last_off_name, last_off_destination, last_off_type, last_off_price));
}

vector<Offer> Service::serv_getSorted(bool (*sortFunction)(Offer& off1, Offer& off2)) {
    vector<Offer> all_offers = serv_getAll();
    for (int i = 0; i < all_offers.size(); i++)
        for (int j = i + 1; j < all_offers.size(); j++)
            if (sortFunction(all_offers[i], all_offers[j]))
                std::swap(all_offers[i], all_offers[j]);
    return all_offers;
}

vector<Offer> Service::sortByName(){
    vector<Offer> result = serv_getSorted([](Offer& off1, Offer& off2){
        int res = off1.getName().compare(off2.getName());
        return res > 0;
    });

    return result;
}

vector<Offer> Service::sortByDestination(){
    vector<Offer> result = serv_getSorted([](Offer& off1, Offer& off2){
        int res = off1.getDestination().compare(off2.getDestination());
        return res > 0;
    });

    return result;
}

vector<Offer> Service::sortByType(){
    vector<Offer> result = serv_getSorted([](Offer& off1, Offer& off2){
        int res = off1.getType().compare(off2.getType());
        return res > 0;
    });

    return result;
}

vector<Offer> Service::sortByPrice(){
    vector<Offer> result = serv_getSorted([](Offer& off1, Offer& off2){
        return off1.getPrice() < off2.getPrice();
    });

    return result;
}

//vector<Offer> Service::sortOffersByName(){
//    vector<Offer>& all_offers = serv_getAll();
//    vector<Offer> result;
//    std::sort(all_offers.begin(),
//              all_offers.end(),
//              [&](const Offer& off1, const Offer& off2){
//                  return off1.getName() < off2.getName();
//              });
//
//    return result;
//}

vector<Offer> Service::serv_filterByDestinationWithCopyIf(const string conditional_var){
    vector<Offer>& all_offers = serv_getAll();
    vector<Offer> result;
    std::copy_if(all_offers.begin(),
                 all_offers.end(),
                 std::back_inserter(result),
                 [&](const Offer& offer) {
                            return offer.getDestination() == conditional_var;
    });
    return result;
}

vector<Offer> Service::serv_filterByPriceWithCopyIf(const int conditional_var){
    vector<Offer>& all_offers = serv_getAll();
    vector<Offer> result;
    std::copy_if(all_offers.begin(),
                 all_offers.end(),
                 std::back_inserter(result),
                 [&](const Offer& offer) {
                     return offer.getPrice() == conditional_var;
                 });
    return result;
}



void Service::addWishlist(const std::string name) {
    Offer& off = repo.repo_findOffer(name);
    repo.addWishlist(off);
}

void Service::emptyWishlist() {
    repo.emptyWishlist();
}

vector<Offer>& Service::getWishlist() {
    return repo.getWishlist();
}

void Service::exportWishlist(string file_name) {
    std::ofstream out(file_name);

    vector<Offer> wishlist = getWishlist();

    out << "YOUR WISHLIST:\n\n";
    for (auto it = wishlist.begin(); it != wishlist.end(); ++it){
        out << "OFFER: " + it->getName() + " " + it->getDestination() + " " + it->getType() + " " + std::to_string(it->getPrice()) + '\n';
    }

    out.close();
}

std::string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

void Service::generateWishlist(int nr) {
    while (nr) {
        string randomName = random_string(10);
        string randomDestination = random_string(10);
        string randomType = random_string(5);
        int randomPrice = rand() % 9000 + 1000;
        Offer RandomOff{randomName, randomDestination, randomType, randomPrice};
        try {
            repo.addWishlist(RandomOff);
            nr--;
        }
        catch (const RepoException &ex) {
            continue;
        }
    }
}

void Service::undo() {
    if (undoActions.empty())
        throw RepoException{"You can't undo anymore\n"};

    undoActions.back()->doUndo();
    undoActions.pop_back();
}






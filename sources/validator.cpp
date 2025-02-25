//
// Created by dan gaspar on 02.04.2024.
//

#include "../headers/validator.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

void OfferValidator::validate(const Offer& off){
    string msgs;
    if (off.getName().size() == 0)
        msgs += "Invalid name.\n";
    if (off.getDestination().size() == 0)
        msgs += "Invalid destination.\n";
    if (off.getType().size() == 0)
        msgs += "Invalid type.\n";
    if (off.getPrice() < 0)
        msgs += "Invalid price. Cannot be negative.\n";

    if (msgs.size() > 0)
        throw ValidatorException(msgs);
}

ostream& operator<<(ostream& out, const ValidatorException& ex) {
    out << ex.msg;
    return out;
}
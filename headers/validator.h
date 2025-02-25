//
// Created by dan gaspar on 02.04.2024.
//

#pragma once
#include "offer.h"
#include <ostream>

using std::ostream;

class OfferValidator{
public:
    void validate(const Offer& off);
};


class ValidatorException {
public:
    ValidatorException(string m):msg{ m }{}
    friend ostream & operator<<(ostream& out, const ValidatorException& ex);

    string msg;
};

ostream& operator<<(ostream& out, const ValidatorException& ex);
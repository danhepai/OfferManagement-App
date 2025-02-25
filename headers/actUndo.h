//
// Created by dan gaspar on 11.05.2024.
//

#include "offer.h"
#include "repository.h"

class actUndo {
public:
    virtual void doUndo() = 0;
    virtual ~actUndo()=default;
};

class UndoAdd : public actUndo {
private:
    OffersRepo& rep;
    Offer addedOffer;

public:
    UndoAdd(OffersRepo& repo, Offer off) : rep{ repo }, addedOffer { off }{}

    void doUndo() override{
        rep.repo_deleteOffer(addedOffer);
    }
};

class UndoDelete : public actUndo {
private:
    OffersRepo& rep;
    Offer deletedOffer;

public:
    UndoDelete(OffersRepo& repo, Offer off) : rep{ repo }, deletedOffer { off }{}

    void doUndo() override{
        rep.repo_addOffer(deletedOffer);
    }
};

class UndoModify : public actUndo {
private:
    OffersRepo& rep;
    Offer modifiedOffer;
    string last_name, last_destination, last_type;
    int last_price;

public:
    UndoModify(OffersRepo& repo, Offer off, string last_n, string last_d, string last_t, int last_p) : rep{ repo }, modifiedOffer { off }, last_name{ last_n }, last_destination{ last_d }, last_type{ last_t }, last_price{ last_p }{}

    void doUndo() override{
        rep.repo_deleteOffer(modifiedOffer);
        Offer off{last_name, last_destination, last_type, last_price};
        rep.repo_addOffer(off);
    }
};

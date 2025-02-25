//
// Created by dan gaspar on 26.04.2024.
//

#ifndef LABORATOR06_FILEREPOSITORY_H
#define LABORATOR06_FILEREPOSITORY_H
#include "repository.h"
class FileRepository:public OffersRepo{
private:
    string file_name;

    void readFromFile();
    void saveToFile();

public:
    FileRepository(string f_name):file_name{f_name}{
        readFromFile();
    }

    void repo_addOffer(const Offer &off) override{
        OffersRepo::repo_addOffer(off);
        saveToFile();
    };

    void repo_deleteOffer(Offer& offToDel) override{
        OffersRepo::repo_deleteOffer(offToDel);
        saveToFile();
    }
};


#endif //LABORATOR06_FILEREPOSITORY_H

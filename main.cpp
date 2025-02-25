#include <QApplication>
#include <QPushButton>
#include <iostream>
#include "headers/console.h"
#include "headers/service.h"
#include "headers/repository.h"
#include "headers/validator.h"
#include "headers/tests.h"
#include "headers/FileRepository.h"
#include "headers/GUI.h"

int main(int argc, char *argv[]) {
    testAll();

    FileRepository fileRepo{"/Users/dangaspar/Documents/CS-UBB/Year01/Structuri de date si algoritmi/Laboratoare/LaboratorQT/offers.txt"};
    OffersRepo repo;
    OfferValidator val;
    Service serv{fileRepo, val};
    Wishlist wish;

    QApplication a(argc, argv);

    GUI gui{serv, wish};
    gui.show();

    return QApplication::exec();
}

//
// Created by dan gaspar on 15.05.2024.
//

#include "../headers/GUI.h"
#include "../headers/WishlistGui.h"

void GUI::initGUI() {
    // MAIN Layout
    auto *mainLayout = new QHBoxLayout{this};
    setLayout(mainLayout);

    auto leftLayout = new QVBoxLayout;
    //auto leftleftLayout = new QVBoxLayout;
    auto rightLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    // LEFT SIDE

    leftLayout->addWidget(offersList);
//    table->setRowCount(30000);
//    table->setColumnCount(1);
    //leftleftLayout->addWidget(table);

    // RIGHT SIDE

    //OFFER FORM
    auto fields = new QFormLayout;
    fields->addRow("Name ", nameField);
    fields->addRow("Destinations ", destinationField);
    fields->addRow("Type ",typeField);
    fields->addRow("Price ", priceField);

    auto *fieldLayout = new QVBoxLayout;
    fieldLayout->addItem(fields);

    rightLayout->addLayout(fieldLayout);

    // CRUD BUTTONS
    auto *crudBtnsLayout = new QHBoxLayout;
    crudBtnsLayout->addWidget(addBtn);
    crudBtnsLayout->addWidget(deleteBtn);
    crudBtnsLayout->addWidget(updateBtn);
    crudBtnsLayout->addWidget(exitBtn);
    rightLayout->addLayout(crudBtnsLayout);

    // SORT BUTTONS
    auto *sortBtnsLayout = new QHBoxLayout;
    sortBtnsLayout->addWidget(sortName);
    sortBtnsLayout->addWidget(sortDestination);
    sortBtnsLayout->addWidget(sortType);
    sortBtnsLayout->addWidget(sortPrice);

    rightLayout->addLayout(sortBtnsLayout);

    // FILTER BUTTONS
    auto *filterBtnsLayout = new QHBoxLayout;
    filterBtnsLayout->addWidget(filterDestination);
    filterBtnsLayout->addWidget(filterPrice);

    rightLayout->addLayout(filterBtnsLayout);

    // UNDO BUTTON
    auto *undoBackLayout = new QHBoxLayout;
    undoBackLayout->addWidget(undoBtn);
    undoBackLayout->addWidget(backBtn);
    undoBackLayout->addWidget(wishList);

    rightLayout->addLayout(undoBackLayout);

}

void GUI::loadData() {

    offersList->clear();
    vector<Offer> allOffers = serv.serv_getAll();
    //table->setRowCount(allOffers.size());
    for (const auto &off : allOffers){
        QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
        offersList->addItem(offer);
        //table->setItem(allOffers.size(), 1, new QTableWidgetItem(QString::fromStdString(off.getName())));
    }


}

void GUI::initConnect() {
    // EXIT
    QObject::connect(exitBtn, &QPushButton::clicked, [&]() {
        close();
    });

    QObject::connect(addBtn, &QPushButton::clicked, [&](){
        auto name = nameField->text().toStdString();
        auto destination = destinationField->text().toStdString();
        auto type = typeField->text().toStdString();
        auto price = priceField->text().toInt();

        try {
            serv.addOffer(name, destination, type, price);
        }
        catch (const ValidatorException &ex) {
            QMessageBox::information(nullptr, "Error", "Validator");
            return;
        }
        catch (const RepoException &ex) {
            QMessageBox::information(nullptr, "Error", "Repo");
            return;
        }
        loadData();
    });

    QObject::connect(deleteBtn, &QPushButton::clicked, [&](){
        auto name = nameField->text().toStdString();

        try {
            serv.deleteOffer(name);
        }
        catch (const RepoException &ex) {
            QMessageBox::information(nullptr, "Error", "Repo");
            return;
        }

        loadData();
    });

    QObject::connect(updateBtn, &QPushButton::clicked, [&](){
        auto name = nameField->text().toStdString();
        auto destination = destinationField->text().toStdString();
        auto type = typeField->text().toStdString();
        auto price = priceField->text().toInt();

        try {
            serv.serv_modifyOffer(name, name, destination, type, price);
        }
        catch (const ValidatorException &ex) {
            QMessageBox::information(nullptr, "Error", "Validator");
            return;
        }
        catch (const RepoException &ex) {
            QMessageBox::information(nullptr, "Error", "Repo");
            return;
        }

        loadData();
    });

    QObject::connect(offersList, &QListWidget::itemClicked, [&](QListWidgetItem* item){
        string itemName = item->text().toStdString();
        string name = itemName.substr(0, itemName.find(';'));
        Offer off = serv.serv_findOffer(name);
        nameField->setText(QString::fromStdString(off.getName()));
        destinationField->setText(QString::fromStdString(off.getDestination()));
        typeField->setText(QString::fromStdString(off.getType()));
        priceField->setText(QString::number(off.getPrice()));
    });

    QObject::connect(sortName, &QPushButton::clicked, [&](){
        vector<Offer> result = serv.sortByName();
        offersList->clear();
        for (auto &off : result){
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(sortDestination, &QPushButton::clicked, [&](){
        vector<Offer> result = serv.sortByDestination();
        offersList->clear();
        for (auto &off : result){
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(sortType, &QPushButton::clicked, [&](){
        vector<Offer> result = serv.sortByType();
        offersList->clear();
        for (auto &off : result){
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(sortPrice, &QPushButton::clicked, [&](){
        vector<Offer> result = serv.sortByPrice();
        offersList->clear();
        for (auto &off : result){
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(filterDestination, &QPushButton::clicked, [&](){
        auto destination = destinationField->text().toStdString();
        vector<Offer> result = serv.serv_getFiltered("destination", destination);
        offersList->clear();
        for (auto &off : result){
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(filterPrice, &QPushButton::clicked, [&](){
        auto price = priceField->text().toInt();
        vector<Offer> result = serv.serv_getFiltered("price", to_string(price));
        offersList->clear();
        for (auto &off : result) {
            QString offer = QString::fromStdString(off.getName()) + ";" + QString::fromStdString(off.getType()) + ";" +
                            QString::fromStdString(off.getDestination()) + ";" + QString::fromStdString(to_string(off.getPrice()));
            offersList->addItem(offer);
        }
    });

    QObject::connect(undoBtn, &QPushButton::clicked, [&](){
        try {
            serv.undo();
        }
        catch (const RepoException &ex) {
            QMessageBox::information(nullptr, "Error", "Undo failed");
            return;
        }
        loadData();
    });

    QObject::connect(backBtn, &QPushButton::clicked, [&](){
        loadData();
    });

    QObject::connect(wishList, &QPushButton::clicked, [&](){
        WishlistGui *wishGui = new WishlistGui(wish,serv);
        wishGui->show();
    });
}

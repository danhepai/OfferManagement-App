//
// Created by dan gaspar on 05.06.2024.
//

#include "../headers/WishlistGui.h"

void WishlistGui::connectSignals(){
    QObject::connect(this->addBtn, &QPushButton::clicked, this, [&](){
        std::string name = this->countEdit->text().toStdString();
        this->wish.addOffer(&serv.serv_findOffer(name));
    });
    QObject::connect(this->randomAddBtn, &QPushButton::clicked, this, [&](){
        int count = this->countEdit->text().toInt();
        this->wish.random_add(this->serv.serv_getAll(), count);
    });
    QObject::connect(this->deleteBtn, &QPushButton::clicked, this, [&](){
        this->wish.empty();
        reloadData(wish.getOffers());
    });
    QObject::connect(this->exitBtn, &QPushButton::clicked, this, [&](){
        close();
    });
    QObject::connect(this->saveBtn, &QPushButton::clicked, this, [&](){

    });

}

void WishlistGui::initGUI() {
    // MAIN Layout
    auto *main_Layout = new QHBoxLayout{this};
    setLayout(main_Layout);

    auto leftLayout = new QVBoxLayout;
    //auto leftleftLayout = new QVBoxLayout;
    auto rightLayout = new QVBoxLayout;
    main_Layout->addLayout(leftLayout);
    main_Layout->addLayout(rightLayout);

    leftLayout->addWidget(offersList);

    auto fields = new QFormLayout;
    fields->addRow("Field ", countEdit);

    auto *fieldLayout = new QVBoxLayout;
    fieldLayout->addItem(fields);

    rightLayout->addLayout(fieldLayout);

    auto *crudBtnsLayout = new QHBoxLayout;
    crudBtnsLayout->addWidget(addBtn);
    crudBtnsLayout->addWidget(deleteBtn);
    crudBtnsLayout->addWidget(randomAddBtn);
    crudBtnsLayout->addWidget(exitBtn);
    rightLayout->addLayout(crudBtnsLayout);


}

void WishlistGui::reloadData(const vector<Offer *>& offers) {
    offersList->clear();
    for(const auto& off : offers){
        auto *item=new QListWidgetItem(QString::fromStdString(off->getName()) + " " + QString::fromStdString(off->getDestination()) + " " + QString::fromStdString(off->getType()) + " " + QString::fromStdString(to_string(off->getPrice())));
        offersList->addItem(item);
    }
}

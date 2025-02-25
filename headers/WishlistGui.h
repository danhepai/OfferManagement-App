//
// Created by dan gaspar on 05.06.2024.
//

#pragma once

#include "Wishlist.h"
#include "service.h"
#include "offer.h"
#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QLayout>
#include <QTextBlock>
#include <QTableWidget>
#include <set>
#include <QSlider>
#include <QPainter>
#include <QListView>
#include "observer.h"

class WishlistGui : public QWidget, public Observer {
private:
    Wishlist &wish;
    Service &serv;

    QListWidget *offersList = new QListWidget;


    QPushButton *addBtn = new QPushButton("&Add ");
    QPushButton *deleteBtn = new QPushButton("&Clear ");
    QPushButton *exitBtn = new QPushButton("&Exit ");
    QPushButton *randomAddBtn = new QPushButton("&Random Add ");
    QPushButton *saveBtn = new QPushButton("&Save ");

    QLineEdit *countEdit = new QLineEdit;


    void initGUI();
    void connectSignals();
    void reloadData(const vector<Offer*>& offers);
    void update() override{
        reloadData(wish.getOffers());
    }

public:
    WishlistGui(Wishlist &w, Service &serv): wish{w}, serv{serv}{
        wish.addObs(this);
        this->initGUI();
        this->connectSignals();
        this->reloadData(wish.getOffers());
    }
    ~WishlistGui(){};
};


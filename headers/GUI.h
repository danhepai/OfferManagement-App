//
// Created by dan gaspar on 15.05.2024.
//

#pragma once

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
#include "service.h"
#include "offer.h"
#include "repository.h"
#include <exception>
#include "Wishlist.h"

class GUI : public QWidget{
private:
    Service &serv;
    Wishlist &wish;

    QListWidget *offersList = new QListWidget{this};
    //QTableWidget *table = new QTableWidget{this};

    //BUTTONS:
    QPushButton *addBtn = new QPushButton("&Add ");
    QPushButton *deleteBtn = new QPushButton("&Delete ");
    QPushButton *updateBtn = new QPushButton("&Update ");
    QPushButton *exitBtn = new QPushButton("&Exit ");
    QPushButton *sortName = new QPushButton("Sort by name ");
    QPushButton *sortDestination = new QPushButton("Sort by destination ");
    QPushButton *sortType = new QPushButton("Sort by type ");
    QPushButton *sortPrice = new QPushButton("Sort by price ");
    QPushButton *filterPrice = new QPushButton("Filter by price ");
    QPushButton *filterDestination = new QPushButton("Filter by destination ");
    QPushButton *undoBtn = new QPushButton("Undo ");
    QPushButton *backBtn = new QPushButton("Back ");
    QPushButton *wishList = new QPushButton("Wishlist ");

    // FIELDS
    QLineEdit *nameField = new QLineEdit;
    QLineEdit *destinationField = new QLineEdit;
    QLineEdit *typeField = new QLineEdit;
    QLineEdit *priceField = new QLineEdit;


    void initGUI();
    void loadData();
    void initConnect();


public:
    GUI(Service &s, Wishlist &w): serv(s), wish(w){
        initGUI();
        loadData();
        initConnect();
    }
};


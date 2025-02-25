//
// Created by dan gaspar on 20.05.2024.
//

#pragma once

#include <vector>

using namespace std;

class Observer{
public:
    virtual void update()=0;
};

class Observable{
    vector<Observer*> obs;

public:
    void rmObs(Observer* ob){
        obs.erase(remove(obs.begin(),obs.end(),ob),obs.end());
    }

    void notify(){
        for(auto it:obs){
            it->update();
        }
    }

    void addObs(Observer* ob){
        obs.push_back(ob);
    }
};

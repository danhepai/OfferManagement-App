//
// Created by dan gaspar on 10.04.2024.
//

#pragma once

#include "offer.h"

#define INITIAL_CAPACITY 5

typedef Offer Element;

class IteratorVector;

class DynamicVector {
private:
    Element* elems;
    int size;
    int capacity;

    void resize();

public:

    // Constructor default
    DynamicVector();

    DynamicVector(DynamicVector& other);

    ~DynamicVector();

    DynamicVector& operator=(const DynamicVector& other);

    void add(const Element& e);

    Element& get(int pos) const;

    void set(int pos, const Element& el);

    int len() const noexcept;

    friend class IteratorVector;

    IteratorVector begin();

    IteratorVector end();
};

class IteratorVector {
private:
    const DynamicVector& v;
    int current = 0;

public:
    //Constructor only with vector
    IteratorVector(const DynamicVector& v) noexcept;

    //Constructor with vector and position
    IteratorVector(const DynamicVector& v, int pos)noexcept;

    bool valid();

    Element& element() const noexcept;

    void next() noexcept;

    // Operators overloading

    //De-reference operator
    Element& operator*();

    //Increment operator
    IteratorVector& operator++();

    //Equality operator
    bool operator==(const IteratorVector& ot)noexcept;

    //Inequality operator
    bool operator!=(const IteratorVector& ot)noexcept;

};
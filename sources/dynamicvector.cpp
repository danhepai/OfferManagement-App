//
// Created by dan gaspar on 10.04.2024.
//

#include "../headers/dynamicvector.h"

void DynamicVector::resize() {
    capacity *= 2;
    Element* newElems = new Element[capacity];
    for (int i = 0; i < size; i++)
        newElems[i] = elems[i];
    delete[] elems;
    elems = newElems;
}

DynamicVector::DynamicVector() :elems{ new Element[INITIAL_CAPACITY] }, capacity{ INITIAL_CAPACITY }, size{ 0 } {}

DynamicVector::DynamicVector(DynamicVector& other){
    elems = new Element[other.capacity];
    for (int i = 0; i < other.size; i++)
        elems[i] = other.elems[i];
    size = other.size;
    capacity = other.capacity;
}

DynamicVector::~DynamicVector() {
    delete[] elems;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& other) {
    if (this == &other)
        return *this;
    delete[] elems;
    elems = new Element[other.capacity];
    for (int i = 0; i < other.size; i++)
        elems[i] = other.elems[i];
    size = other.size;
    capacity = other.capacity;
    return *this;
}

void DynamicVector::add(const Element &e) {
    if (size == capacity)
        resize();
    elems[size++] = e;
}

Element &DynamicVector::get(int pos) const {
    return elems[pos];
}

void DynamicVector::set(int pos, const Element &el) {
    elems[pos] = el;
}

int DynamicVector::len() const noexcept {
    return size;
}

IteratorVector::IteratorVector(const DynamicVector& v) noexcept:v{ v } {}

IteratorVector::IteratorVector(const DynamicVector& v, int pos)noexcept :v{ v }, current{ pos } {}

bool IteratorVector::valid() {
    return current < v.len();
}

Element &IteratorVector::element() const noexcept {
    return v.get(current);
}

void IteratorVector::next() noexcept {
    current++;
}

Element &IteratorVector::operator*() {
    return element();
}

IteratorVector& IteratorVector::operator++() {
    next();
    return *this;
}

bool IteratorVector::operator==(const IteratorVector &ot) noexcept {
    return current == ot.current;
}

bool IteratorVector::operator!=(const IteratorVector &ot) noexcept {
    return !(*this == ot);
}

IteratorVector DynamicVector::begin()
{
    return IteratorVector(*this);
}

IteratorVector DynamicVector::end()
{
    return IteratorVector(*this, size);
}
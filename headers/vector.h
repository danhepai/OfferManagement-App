//
// Created by dan gaspar on 10.04.2024.
//

#pragma once
#define INITIAL_CAPACITY 5

template <typename Element>
class IteratorVectorTemplate;

template <typename Element>
class VectorTemplate {
private:
    int n;
    int size;
    Element* elems;

    void resize();

public:
    VectorTemplate();

    VectorTemplate(const VectorTemplate& ot);

    ~VectorTemplate();

    VectorTemplate& operator=(const VectorTemplate& ot);

    void add(const Element& el);

    void deleteElem(int pos);

    Element& get(int pos) const;

    void set(int pos, const Element& el);

    int dim();

    friend class IteratorVectorTemplate<Element>;
    IteratorVectorTemplate<Element> begin();
    IteratorVectorTemplate<Element> end();
};

// Constructor default
template<typename Element>
VectorTemplate<Element>::VectorTemplate() :elems{new Element[INITIAL_CAPACITY]}, size{INITIAL_CAPACITY}, n{0}{}

// Constructor de copiere
template<typename Element>
VectorTemplate<Element>::VectorTemplate(const VectorTemplate<Element> &ot) {
    elems = new Element[ot.size];
    for (int i = 0; i < ot.n; i++)
        elems[i] = ot.elems[i];
    n = ot.n;
    size = ot.size;
}

template<typename Element>
VectorTemplate<Element>& VectorTemplate<Element>::operator=(const VectorTemplate<Element> &ot) {
    if (this == &ot)
        return *this;
    delete[] elems;
    elems = new Element[ot.size];
    for (int i = 0; i < ot.n; i++)
        elems[i] = ot.elems[i];
    n = ot.n;
    size = ot.size;
    return *this;
}

template<typename Element>
VectorTemplate<Element>::~VectorTemplate() {
    delete[] elems;
}

template<typename Element>
void VectorTemplate<Element>::add(const Element &el) {
    if (n == size)
        resize();
    elems[n++] = el;
}

template<typename Element>
void VectorTemplate<Element>::deleteElem(int pos) {
    for (int i = pos; i < n - 1; i++)
        elems[i] = elems[i + 1];
    n--;
}

template<typename Element>
Element &VectorTemplate<Element>::get(int pos) const {
    return elems[pos];
}

template<typename Element>
void VectorTemplate<Element>::set(int pos, const Element &el) {
    elems[pos] = el;
}

template<typename Element>
int VectorTemplate<Element>::dim() {
    return n;
}

template<typename Element>
void VectorTemplate<Element>::resize() {
    size *= 2;
    Element* newElems = new Element[size];
    for (int i = 0; i < n; i++)
        newElems[i] = elems[i];
    delete[] elems;
    elems = newElems;
}

template<typename Element>
class IteratorVectorTemplate {
private:
    const VectorTemplate<Element>& v;
    int poz = 0;
public:
    IteratorVectorTemplate(const VectorTemplate<Element>& v) noexcept;

    IteratorVectorTemplate(const VectorTemplate<Element>& v, int poz)noexcept;

    bool valid()const;

    Element& element() const;

    void next();

    int pos();

    Element& operator*();

    IteratorVectorTemplate& operator++();

    bool operator==(const IteratorVectorTemplate& ot)noexcept;

    bool operator!=(const IteratorVectorTemplate& ot)noexcept;
};

template<typename Element>
IteratorVectorTemplate<Element>::IteratorVectorTemplate(const VectorTemplate<Element>& v) noexcept :v{v } {}

template<typename Element>
IteratorVectorTemplate<Element>::IteratorVectorTemplate(const VectorTemplate<Element>& v, int poz)noexcept :v{v }, poz{poz } {}

template<typename Element>
bool IteratorVectorTemplate<Element>::valid()const {
    return poz < v.dim();
}

template<typename Element>
Element& IteratorVectorTemplate<Element>::element() const {
    return v.get(poz);
}

template<typename Element>
void IteratorVectorTemplate<Element>::next() {
    poz++;
}

template<typename Element>
int IteratorVectorTemplate<Element>::pos() {
    return poz;
}

template<typename Element>
Element& IteratorVectorTemplate<Element>::operator*() {
    return element();
}

template<typename Element>
IteratorVectorTemplate<Element>& IteratorVectorTemplate<Element>::operator++() {
    next();
    return *this;
}

template<typename Element>
bool IteratorVectorTemplate<Element>::operator==(const IteratorVectorTemplate<Element>& ot) noexcept {
    return poz == ot.poz;
}

template<typename Element>
bool IteratorVectorTemplate<Element>::operator!=(const IteratorVectorTemplate<Element>& ot)noexcept {
    return poz != ot.poz;
}

template<typename Element>
IteratorVectorTemplate<Element> VectorTemplate<Element>::begin() {
    return IteratorVectorTemplate<Element>(*this);
}

template<typename Element>
IteratorVectorTemplate<Element> VectorTemplate<Element>::end() {
    return IteratorVectorTemplate<Element>(*this, n);
}



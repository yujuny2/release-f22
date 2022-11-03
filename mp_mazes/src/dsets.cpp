/* Your code here! */
#include "dsets.h"
#include <cmath>
#include <iostream>

DisjointSets::DisjointSets(): number_of_sets_(0) {}

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        elems.push_back(-1);
    }
    number_of_sets_ += num;
}

int DisjointSets::find(int elem) {
    if (elems[elem] < 0) return elem;
    return find(elems[elem]);
}

void DisjointSets::setunion(int a, int b) {
    int root_a = find(a);
    int root_b = find(b);
    int newSize = elems[root_a] + elems[root_b];

    if (elems[root_a] <= elems[root_b]) {
        elems[root_b] = root_a;
        elems[root_a] = newSize;
    } else {
        elems[root_a] = root_b;
        elems[root_b] = newSize;
    }

    number_of_sets_ -= 1;
}

int DisjointSets::size(int elem) {
    int root = find(elem);
    return abs(elems[root]);
}

bool DisjointSets::empty() {
    return elems.empty();
}

void DisjointSets::clear() {
    elems.clear();
}

int DisjointSets::number_of_sets() {
    return number_of_sets_;
}

void DisjointSets::printset() {
    for (auto elem : elems) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}
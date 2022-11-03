/* Your code here! */
#pragma once

#include <vector>

class DisjointSets {
    public:
        DisjointSets();
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        bool empty();
        void clear();
        int number_of_sets();
        void printset();

    private:
        std::vector<int> elems;
        int number_of_sets_;
};
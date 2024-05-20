#pragma once


#include <vector>
#include "InstanceTSP.h"

class Solution {
public:
    Solution(InstanceTSP i);

    int operator[](int i) const;
    int size() const;

    std::vector<int> getSolution() const;
    void shuffle();
    void swap(int i, int j);
protected:
    std::vector<int> villes;
};

std::ostream& operator<<(std::ostream &os, const Solution &sol);
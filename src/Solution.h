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

    Solution echange_par_index(int index);
    Solution reinsertion(int i, int j);
    Solution reinsertion_par_index(int index);
    Solution two_opt(int i, int j);
    Solution two_opt_par_index(int index);

protected:
    std::vector<int> villes;
};

std::ostream& operator<<(std::ostream &os, const Solution &sol);

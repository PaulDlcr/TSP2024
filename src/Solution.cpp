#include <random>
#include <algorithm>
#include <ctime>
#include "Solution.h"

Solution::Solution(InstanceTSP _i) {
    villes.resize(_i.getVilles().size());
    for(int i = 0; i < villes.size(); i++) {
        villes[i] = i;
    }
}

std::vector<int> Solution::getSolution() const {
    return this->villes;
}

int Solution::operator[](int i) const {
    if ( i < 0 )
        return this->villes[this->villes.size() + i];
    return this->villes[i];
}

int Solution::size() const {
    return this->villes.size();
}

void Solution::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    g.seed(time(NULL));
    std::shuffle(this->villes.begin(), this->villes.end(), g);
}

void Solution::swap(int i, int j) {
    std::swap(this->villes[i], this->villes[j]);
}

Solution Solution::echange_par_index(int index) {
    Solution newSol(*this); // Create a copy of the current solution
    int n = static_cast<int>((1 + sqrt(1 + 8 * index)) / 2);
    int i = index - (n * (n - 1)) / 2;
    int j = this->size() - n + i;
    newSol.swap(i, j);
    return newSol;
}

Solution Solution::reinsertion(int i, int j) {
    Solution newSol(*this); // Create a copy of the current solution
    int city = newSol.villes[i];
    newSol.villes.erase(newSol.villes.begin() + i);
    newSol.villes.insert(newSol.villes.begin() + j, city);
    return newSol;
}

Solution Solution::reinsertion_par_index(int index) {
    Solution newSol(*this); // Create a copy of the current solution
    int n = this->size();
    int i, j;
    if (index <= n - 2) {
        i = 0;
        j = index + 1;
    } else {
        i = (index - 1) / (n - 2);
        j = (index - 1) % (n - 2);
        if (j >= i - 1) {
            j += 2;
        }
    }
    return newSol.reinsertion(i, j);
}

Solution Solution::two_opt(int i, int j) {
    Solution newSol(*this); // Create a copy of the current solution
    std::reverse(newSol.villes.begin() + i, newSol.villes.begin() + j + 1);
    return newSol;
}

Solution Solution::two_opt_par_index(int index) {
    Solution newSol(*this); // Create a copy of the current solution
    int n = static_cast<int>((1 + sqrt(1 + 8 * index)) / 2);
    int i = index - (n * (n - 1)) / 2;
    int j = this->size() - n + i;
    return newSol.two_opt(i, j);
}

std::ostream& operator<<(std::ostream &os, const Solution &sol) {
    for (auto v : sol.getSolution()) {
        os << v << " ";
    }
    return os;
}

#include "EvalTSP.h"
#include "Solution.h"
#include <cmath>
#include <limits>
#include <random>

EvalTSP::EvalTSP(InstanceTSP &_instanceTsp) :
    instanceTsp(_instanceTsp) {

}

float EvalTSP::distance(const Ville& a, const Ville& b) {
    return R * acos(sin(toRadian(a.latitude)) * sin(toRadian(b.latitude)) +
        cos(toRadian(a.latitude)) * cos(toRadian(b.latitude)) *
        cos(toRadian(a.longitude)- toRadian(b.longitude)) );
}

float EvalTSP::toRadian(float val) {
    return pi * val / 180;
}

float EvalTSP::operator()(Solution &sol) {
    float d = 0.0;
    for (int i = 0; i < sol.size() - 1; i++) {
        d += distance(instanceTsp[sol[i]], instanceTsp[sol[i+1]]);
    }
    d += distance(instanceTsp[sol[-1]], instanceTsp[sol[0]]);
    return d;
}

InstanceTSP &EvalTSP::getInstance() {
    return this->instanceTsp;
}

Solution EvalTSP::meilleure_ameliorante(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins) {
    Solution meilleure_solution = sol;
    float meilleure_distance = (*this)(sol);
    for (int i = 0; i < nombre_voisins; i++) {
        Solution solution_voisine = voisinage(sol, i);
        float distance_voisine = (*this)(solution_voisine);
        if (distance_voisine < meilleure_distance) {
            meilleure_solution = solution_voisine;
            meilleure_distance = distance_voisine;
        }
    }
    return meilleure_solution;
}

Solution EvalTSP::premiere_ameliorante(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins) {
    for (int i = 0; i < nombre_voisins; i++) {
        Solution solution_voisine = voisinage(sol, i);
        float distance_voisine = (*this)(solution_voisine);
        if (distance_voisine < (*this)(sol)) {
            return solution_voisine;
        }
    }
    return sol;
}

Solution EvalTSP::premiere_ameliorante_aleatoire(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins) {
    std::vector<int> indices(nombre_voisins);
    for (int i = 0; i < nombre_voisins; ++i) {
        indices[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    for (int i : indices) {
        Solution solution_voisine = voisinage(sol, i);
        float distance_voisine = (*this)(solution_voisine);
        if (distance_voisine < (*this)(sol)) {
            return solution_voisine;
        }
    }
    return sol;
}

Solution EvalTSP::algorithme_descente(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins) {
    Solution solution = sol;
    float distance_solution = (*this)(sol);
    Solution meilleure_solution = sol;
    float meilleure_distance = std::numeric_limits<float>::infinity();
    while (meilleure_distance > distance_solution) {
        meilleure_solution = solution;
        meilleure_distance = distance_solution;
        solution = meilleure_ameliorante(solution, voisinage, nombre_voisins);
        distance_solution = (*this)(solution);
    }
    return meilleure_solution;
}

Solution EvalTSP::recherche_locale_voisinage_variable(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int nombre_voisins) {
    Solution meilleure_solution = sol;
    float meilleure_distance = (*this)(sol);
    for (auto& voisinage : voisinages) {
        Solution solution = algorithme_descente(sol, voisinage, nombre_voisins);
        float distance_solution = (*this)(solution);
        if (distance_solution < meilleure_distance) {
            meilleure_solution = solution;
            meilleure_distance = distance_solution;
        }
    }
    return meilleure_solution;
}

Solution EvalTSP::perturber(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int force) {
    Solution nouvelle_solution = sol;
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> distrib(0, voisinages.size() - 1);
    for (int i = 0; i < force; i++) {
        int voisinage_index = distrib(g);
        int nombre_voisins = (nouvelle_solution.size() * (nouvelle_solution.size() - 1)) / 2;
        std::uniform_int_distribution<> distrib_voisins(0, nombre_voisins - 1);
        int voisin_index = distrib_voisins(g);
        nouvelle_solution = voisinages[voisinage_index](nouvelle_solution, voisin_index);
    }
    return nouvelle_solution;
}

Solution EvalTSP::recherche_locale_iteree(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int nombre_voisins, int force, int iterations) {
    Solution meilleure_solution = sol;
    float meilleure_distance = (*this)(sol);
    for (int i = 0; i < iterations; i++) {
        Solution solution = recherche_locale_voisinage_variable(meilleure_solution, voisinages, nombre_voisins);
        solution = perturber(solution, voisinages, force);
        float distance_solution = (*this)(solution);
        if (distance_solution < meilleure_distance) {
            meilleure_solution = solution;
            meilleure_distance = distance_solution;
        }
    }
    return meilleure_solution;
}

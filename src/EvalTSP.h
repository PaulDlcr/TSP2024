#pragma once

#include "InstanceTSP.h"
#include "Solution.h"
#include <functional>
#include <vector>
#include <algorithm>

class EvalTSP {
public:
    EvalTSP(InstanceTSP &_instanceTsp);

    float operator()(Solution &sol);

    InstanceTSP& getInstance();

    static float distance(const Ville& a, const Ville& b);
    static float toRadian(float val);

    Solution meilleure_ameliorante(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins);
    Solution premiere_ameliorante(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins);
    Solution premiere_ameliorante_aleatoire(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins);
    Solution algorithme_descente(Solution &sol, std::function<Solution(Solution, int)> voisinage, int nombre_voisins);

    Solution recherche_locale_voisinage_variable(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int nombre_voisins);

    Solution perturber(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int force);
    Solution recherche_locale_iteree(Solution &sol, std::vector<std::function<Solution(Solution, int)>> voisinages, int nombre_voisins, int force, int iterations);

protected:
    InstanceTSP &instanceTsp;
    constexpr static float pi = 3.141592;
    constexpr static float R = 6378.137;
};

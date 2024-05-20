#include <iostream>
#include "src/InstanceTSP.h"
#include "src/Solution.h"
#include "src/EvalTSP.h"
#include "src/Random.h"
#include "src/Greedy.h"

int main() {
    InstanceTSP instanceTsp("C:/Users/Pol/Documents/Nouveau dossier/TSP2024/instances/france_50.tsp");

    Solution solution(instanceTsp);
    std::cout << "Solution initiale: " << solution << std::endl;

    EvalTSP evalTsp(instanceTsp);
    Greedy greedy;
    Random random;

    solution.shuffle();
    std::cout << "Solution aléatoire: " << solution << std::endl;
    std::cout << "Distance: " << evalTsp(solution) << std::endl;

    greedy(solution, evalTsp);
    std::cout << "Solution gloutonne: " << solution << std::endl;
    std::cout << "Distance: " << evalTsp(solution) << std::endl;

    // Nombre de voisins pour une instance donnée
    int nombre_voisins = (solution.size() * (solution.size() - 1)) / 2;

    // Appliquer l'algorithme de descente avec meilleure_ameliorante
    Solution sol_meilleure_ameliorante = evalTsp.algorithme_descente(solution,
        [&](Solution s, int index) { return s.echange_par_index(index); }, nombre_voisins);
    std::cout << "Solution meilleure ameliorante: " << sol_meilleure_ameliorante << std::endl;
    std::cout << "Distance: " << evalTsp(sol_meilleure_ameliorante) << std::endl;

    // Appliquer l'algorithme de descente avec premiere_ameliorante
    Solution sol_premiere_ameliorante = evalTsp.algorithme_descente(solution,
        [&](Solution s, int index) { return s.echange_par_index(index); }, nombre_voisins);
    std::cout << "Solution premiere ameliorante: " << sol_premiere_ameliorante << std::endl;
    std::cout << "Distance: " << evalTsp(sol_premiere_ameliorante) << std::endl;

    // Appliquer l'algorithme de descente avec premiere_ameliorante_aleatoire
    Solution sol_premiere_ameliorante_aleatoire = evalTsp.algorithme_descente(solution,
        [&](Solution s, int index) { return s.echange_par_index(index); }, nombre_voisins);
    std::cout << "Solution premiere ameliorante aleatoire: " << sol_premiere_ameliorante_aleatoire << std::endl;
    std::cout << "Distance: " << evalTsp(sol_premiere_ameliorante_aleatoire) << std::endl;

    std::vector<std::function<Solution(Solution, int)>> voisinages = {
        [&](Solution s, int index) { return s.echange_par_index(index); },
        [&](Solution s, int index) { return s.reinsertion_par_index(index); },
        [&](Solution s, int index) { return s.two_opt_par_index(index); }
    };

    Solution sol_voisinage_variable = evalTsp.recherche_locale_voisinage_variable(solution, voisinages, nombre_voisins);
    std::cout << "Solution voisinage variable: " << sol_voisinage_variable << std::endl;
    std::cout << "Distance: " << evalTsp(sol_voisinage_variable) << std::endl;

    // Tests pour la recherche locale itérée
    int force = 3;
    int iterations = 10;
    Solution sol_locale_iteree = evalTsp.recherche_locale_iteree(solution, voisinages, nombre_voisins, force, iterations);
    std::cout << "Solution locale iteree: " << sol_locale_iteree << std::endl;
    std::cout << "Distance: " << evalTsp(sol_locale_iteree) << std::endl;

    return 0;
}


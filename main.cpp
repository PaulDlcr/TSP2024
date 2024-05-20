#include <iostream>
#include "src/InstanceTSP.h"
#include "src/Solution.h"
#include "src/EvalTSP.h"
#include "src/Random.h"
#include "src/Greedy.h"

int main() {
    InstanceTSP instanceTsp("instances/france_100.tsp");

    Solution solution(instanceTsp);
    std::cout << solution << std::endl;

    EvalTSP evalTsp(instanceTsp);
    Greedy greedy;
    solution.shuffle();
    greedy(solution, evalTsp);

    std::cout << solution << std::endl;
    std::cout << evalTsp(solution) << std::endl;
    return 0;
}

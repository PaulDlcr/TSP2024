//
// Created by lucien.mousin on 17/04/2024.
//

#include "Greedy.h"

void Greedy::operator()(Solution &_sol, EvalTSP &_eval) {
    for (int i = 0; i < _sol.size() - 1; i++) {
        float min = RAND_MAX;
        int index = -1;
        for (int j = i + 1; j < _sol.size(); j++) {
            float d = _eval.distance(_eval.getInstance()[_sol[i]], _eval.getInstance()[_sol[j]]);
            if ( d < min ) {
                min = d;
                index = j;
            }
        }
        _sol.swap(index, i+1);
    }
}

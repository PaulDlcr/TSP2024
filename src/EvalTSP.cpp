//
// Created by lucien.mousin on 08/04/2024.
//

#include "EvalTSP.h"
#include "Solution.h"

#include <cmath>

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


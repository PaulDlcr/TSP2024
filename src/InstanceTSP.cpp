//
// Created by lucien.mousin on 08/04/2024.
//

#include "InstanceTSP.h"

#include <fstream>

InstanceTSP::InstanceTSP(const std::string& filename) {
    lireInstance(filename);
}

void InstanceTSP::lireInstance(const std::string& filename) {
    std::ifstream file(filename);

    int n;
    file >> n;

    villes.resize(n);

    for (int i = 0; i < n; i++) {
        Ville v;
        file >> v.nom >> v.latitude >> v.longitude;
        villes[i] = v;
    }
}

void InstanceTSP::afficherInstance() {
    for (auto & ville : this->villes) {
        std::cout << ville.nom << " " << ville.latitude << " " << ville.longitude << std::endl;
    }
}

std::vector<Ville> InstanceTSP::getVilles() {
    return this->villes;
}

Ville InstanceTSP::operator[](int i) {
    return this->villes[i];
}

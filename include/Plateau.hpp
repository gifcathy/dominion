#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include "Carte.hpp"

#include <map>
#include <string>
#include <vector>

class Plateau {
    private:
        std::map<std::string, int> piles;

    public:
        Plateau(int nbJoueurs, const std::vector<std::string>& cartesAction);

        int getNombreCartes(const std::string& nom) const;
        bool acheterCarte(const std::string& nom);

}; 

#endif 
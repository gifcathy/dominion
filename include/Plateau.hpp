#ifndef PLATEAU_HPP
#define PLATEAU_HPP
#include "Carte.hpp"
#include "CatalogueCartes.hpp"

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class Plateau {
    private:
        CatalogueCartes catalogue;
        std::map<std::string, int> piles;

    public:
        Plateau(int nbJoueurs, const std::vector<std::string>& cartesAction, const CatalogueCartes& catalogue);

        int getNombreCartes(const std::string& nom) const;
        bool acheterCarte(const std::string& nom);

        const std::map<std::string, int>& getPiles() const;

        void afficher() const;
        void afficherCartePourAchat() const;

        void afficherCarteCoutInfEgal(int coutMax) const;

        bool contientCarte(const std::string& nom) const;
        int getCoutCarte(const std::string& nom) const;

        std::unique_ptr<Carte> creerCarte(const std::string& nom) const;
}; 

#endif 
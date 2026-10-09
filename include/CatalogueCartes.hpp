#ifndef CATALOGUE_CARTES_HPP
#define CATALOGUE_CARTES_HPP

#include "Carte.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>

class CatalogueCartes {
private:
    /*
    - std::map associe une clé à une valeur.
    - std::string est le nom de la carte, par exemple "Or".
    - std::function<std::unique_ptr<Carte>()> représente une fonction qui ne prend aucun argument 
      et retourne un std::unique_ptr<Carte>
    */
    std::map<std::string, std::function<std::unique_ptr<Carte>()>> fabriques;

public:
    void enregistrer(const std::string& nom, std::function<std::unique_ptr<Carte>()> fabrique);

    std::unique_ptr<Carte> creer(const std::string& nom) const;

    bool contient(const std::string& nom) const;
};

#endif
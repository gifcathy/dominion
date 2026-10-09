#include "CatalogueCartes.hpp"

#include <stdexcept>
#include <utility>

void CatalogueCartes::enregistrer(const std::string& nom, std::function<std::unique_ptr<Carte>()> fabrique){
    // Cette ligne enregistre la fonction de création sous le nom fourni. Le std::move transfère ici la fonction dans la map
    fabriques[nom] = std::move(fabrique);
}

std::unique_ptr<Carte> CatalogueCartes::creer(const std::string& nom) const {
    //On recherche le nom demandé
    auto it = fabriques.find(nom);

    //Si la carte n'existe pas dans le catalogue, on signale une erreur
    if (it == fabriques.end()) {
        throw std::invalid_argument("Carte inconnue : " + nom);
    }

    //it->second est la fonction de création associée au nom. Les parenthèses () l'appellent : 
    //elle crée une nouvelle carte et retourne son unique_ptr
    return it->second();
}

// Cette fonction permet simplement de vérifier si le nom est enregistré
bool CatalogueCartes::contient(const std::string& nom) const {
    return fabriques.find(nom) != fabriques.end();
}
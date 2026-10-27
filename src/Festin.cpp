#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Festin.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Festin::Festin() : ActionPlateau("Festin", "Action", 4){}; 

// destructeur 
Festin::~Festin(){}; 

// méthode d'affichage 
void Festin::afficher() const {
    std::cout << "Festin - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez cette carte, recevez une carte coûtant jusqu'à 5 pièces" 
              << std::endl;
}


// jouer la carte 
void Festin::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : FESTIN\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Gagnez une carte coutant au maximum 5 pieces.\n\n";

    Carte* festin = nullptr;

    // on met dans festin l'adresse de la carte dans la liste des cartes jouées 
    for (const auto& carte : joueur.getCartesJouees()) {
        if (carte->getNom() == "Festin") {
            festin = carte.get();
            break;
        }
    }

    // on vérifie qu'on a bien trouvé la carte dans la liste des cartes jouées 
    if (festin == nullptr) {
        std::cout << "Impossible de retrouver la carte Festin." << std::endl;
        return;
    }

    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles :\n";
    plateau.afficherCarteCoutInfEgal(5, cartesDisponibles);

    // Verifier qu'il existe au moins une carte disponible.
    if (cartesDisponibles.empty()) {
        std::cout << "\nAucune carte disponible.\n";
        return;
    }

    int choix;

    // Demander un numero valide.
    while (true) {
        std::cout << "\nVotre choix (0 pour annuler) : ";

        if (std::cin >> choix) {
            if (choix >= 0 && static_cast<std::size_t>(choix) <= cartesDisponibles.size()) {
                break;
            }

            std::cout << "[ERREUR] Choix invalide.\n";
        }
        else {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

            std::cout << "[ERREUR] Entrez un numero valide.\n";
        }
    }

    // Annuler le choix.
    if (choix == 0) {
        std::cout << "Vous n'avez gagne aucune carte.\n";
        return;
    }

    // Recuperer le nom de la carte choisie.
    const std::string& nomCarte = cartesDisponibles[static_cast<std::size_t>(choix - 1)];

    // Retirer une carte de la pile du plateau.
    if (!plateau.acheterCarte(nomCarte)) {
        std::cout << "[ERREUR] Impossible de recuperer cette carte.\n";
        return;
    }

    // Creer la carte et l'ajouter a la defausse du joueur.
    std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);
    joueur.ajouterCarte(std::move(carte));

    std::cout << "\n[SUCCES] Vous avez gagne la carte " << nomCarte << " !\n";
    std::cout << "========================================\n";
}
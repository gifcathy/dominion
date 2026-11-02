#include <iostream> 
#include <limits>
#include "Atelier.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur
Atelier::Atelier() : ActionPlateau("Atelier", "Action", 3){}; 

// destructeur 
Atelier::~Atelier(){}; 

// méthode d'affichage
void Atelier::afficher() const {
    std::cout << "Atelier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Recevez une carte coûtant jusqu'à 4 pièces" << std::endl;
}


// jouer la carte 
void Atelier::jouerPlateau( std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) {
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : ATELIER\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Gagnez une carte coutant au maximum 4 pieces.\n\n";

    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles :\n";
    plateau.afficherCarteCoutInfEgal(4, cartesDisponibles);

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

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <limits>
#include "Renovation.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Renovation::Renovation() : ActionPlateau("Renovation", "Action", 4){}; 

// destructeur 
Renovation::~Renovation(){}; 

// méthode d'affichage 
void Renovation::afficher() const {
    std::cout << "Renovation - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez une carte de votre main, recevez une carte coûtant jusqu'à 2 pièces de plus que la carte écartée" 
              << std::endl;
}


// jouer la carte 
void Renovation::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : RENOVATION\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Ecartez une carte et recevez une carte coûtant jusqu'à deux pièces de plus que la carte écartée.\n\n";

    if (joueur.getMain().empty()) {
        std::cout << "Vous n'avez aucune carte à écarter." << std::endl;
        return;
    }

    // Afficher la main du joueur.
    joueur.afficherMain();

    // Demander quelle carte écarter.
    std::size_t idxCarte;

    while (true) {
        std::cout << "Quelle carte voulez-vous écarter ? (indice de la carte) : ";

        if (!(std::cin >> idxCarte)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Saisie invalide." << std::endl;
            continue;
        }

        if (idxCarte >= 0 && static_cast<std::size_t>(idxCarte) < joueur.getMain().size()) {
            break;
        }

        std::cout << "Indice invalide." << std::endl;
    }

    // Récupérer le coût AVANT d'écarter la carte.
    int coutMax = joueur.getMain()[idxCarte]->getCout() + 2;

    // Écarter la carte choisie.
    joueur.ecarterCarte(static_cast<std::size_t>(idxCarte));

    // Afficher les cartes disponibles dans la limite autorisée.
    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles :\n";
    plateau.afficherCarteCoutInfEgal(coutMax, cartesDisponibles);

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

#include <iostream>
#include <limits>
#include <vector>
#include "Fonderie.hpp"
#include "Plateau.hpp"

// constructeur 
Fonderie::Fonderie() : ActionPlateau("Fonderie", "Action", 4){}; 

// destructeur 
Fonderie::~Fonderie(){}; 

// méthode d'affichage
void Fonderie::afficher() const {
    std::cout << "Fonderie - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Recevez une carte coûtant jusqu'à 4 trésors. Si c'est une carte Action, +1 Action. "
              << "Si c'est une carte Trésor, +1 trésor. Si c'est une carte Victoire, +1 carte" 
              << std::endl;
}

// jouer la carte 
void Fonderie::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    std::cout << "\n========================================\n";
    std::cout << "           CARTE : FONDERIE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Recevez une carte coûtant jusqu'à 4 trésors. Si c'est une carte Action, "
              << "+1 Action. Si c'est une carte Trésor, +1 trésor. Si c'est une carte Victoire, +1 carte\n\n";

    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel]; 
    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles : " << std::endl; 
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
            if (choix >= 1 && static_cast<std::size_t>(choix) <= cartesDisponibles.size()) {
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

    // Recuperer le nom de la carte choisie.
    const std::string& nomCarte = cartesDisponibles[static_cast<std::size_t>(choix - 1)];

    // Retirer une carte de la pile du plateau.
    if (!plateau.acheterCarte(nomCarte)) {
        std::cout << "[ERREUR] Impossible de recuperer cette carte.\n";
        return;
    }

    // Creer la carte et l'ajouter a la defausse du joueur.
    std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);

    // on vérifie de ne pas garder un pointer nul 
    if (carte == nullptr) {
        std::cout << "[ERREUR] Impossible de creer cette carte.\n";
        return;
    }

    std::string typeCarte = carte->getType();
    joueurActuel.ajouterCarte(std::move(carte));

    std::cout << "\n[SUCCES] Vous avez gagne la carte " << nomCarte << " !\n";

    if(typeCarte == "Action" || typeCarte == "Action-Attaque" || typeCarte == "Action-Reaction"){
        joueurActuel.ajouterActions(1); 
        std::cout << "La carte est une Action : vous obtenez +1 Action.\n";
    }
    else if(typeCarte == "Tresor"){
        joueurActuel.ajouterArgent(1); 
        std::cout << "La carte est un Tresor : vous obtenez +1 piece.\n";
    }
    else if(typeCarte == "Victoire"){
        std::unique_ptr<Carte> cartePiochee = joueurActuel.prendreCarteDessusDeck();

        if (cartePiochee != nullptr) {
            joueurActuel.ajouterCarteMain(std::move(cartePiochee));
            std::cout << "La carte est une Victoire : vous piochez une carte.\n";
        }
        else {
            std::cout << "Vous n'avez plus de carte a piocher.\n";
        }
    }
}
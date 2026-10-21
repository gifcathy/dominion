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
    plateau.afficherCarteCoutInfEgal(coutMax);

    // Demander au joueur quelle carte il souhaite gagner.
    std::string nomCarte;
    bool choixValide = false; 

    while(!choixValide){
        std::cout << "Quelle carte souhaitez-vous gagner ? ";
        std::getline(std::cin >> std::ws, nomCarte);
        // Vérifier que la carte existe sur le plateau.
        if (!plateau.contientCarte(nomCarte)) {
            std::cout << "Cette carte n'est pas disponible sur le plateau." << std::endl;
            continue;
        }

        // Vérifier que la pile n'est pas vide.
        if (plateau.getNombreCartes(nomCarte) <= 0) {
            std::cout << "Cette pile est vide." << std::endl;
            continue;
        }

        // Vérifier que la carte coûte au maximum 5 pièces.
        if (plateau.getCoutCarte(nomCarte) > 5) {
            std::cout << "Cette carte coûte plus de 5 pièces." << std::endl;
            continue;
        }
        choixValide = true; 
    }
   

    // Retirer une carte de la pile du plateau.
    if (plateau.acheterCarte(nomCarte)) {
        // on crée la carte que le joueur a choisi
        std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);

        // Ajouter la carte gagnée à la défausse du joueur.
        joueur.ajouterCarte(std::move(carte));

        std::cout << "Vous avez gagné la carte " << nomCarte << " !" << std::endl;
    }
}

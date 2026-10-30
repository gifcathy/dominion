#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Comptoir.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Comptoir::Comptoir() : ActionPlateau("Comptoir", "Action", 5){}; 

// destructeur 
Comptoir::~Comptoir(){}; 

// méthode d'affichage 
void Comptoir::afficher() const {
    std::cout << "Comptoir - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Ecartez 2 cartes de votre main. Dans ce cas, recevez une carte Argent; ajouter cette carte à votre main" 
              << std::endl;
}

// jouer la carte 
void Comptoir::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : Comptoir\n";
    std::cout << "========================================\n";
    std::cout << "Ecartez 2 cartes de votre main. Dans ce cas, recevez une carte Argent; ajouter cette carte à votre main\n\n"; 

    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    for (int i = 0; i < 2; i++) {

        // Vérifier qu'il reste des cartes dans la main.
        if (joueur.getMain().empty()) {
            std::cout << "Vous n'avez plus de cartes a ecarter.\n";
            break;
        }

        // Afficher la main du joueur.
        joueur.afficherMain();

        int idxCarte;

        while (true) {
            std::cout << "Quelle carte voulez-vous ecarter ? (indice) : ";

            if (!(std::cin >> idxCarte)) {
                if (std::cin.eof())
                    return;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Saisie invalide.\n";
                continue;
            }

            if (idxCarte >= 0 &&
                static_cast<std::size_t>(idxCarte) < joueur.getMain().size()) {
                break;
            }

            std::cout << "Indice invalide.\n";
        }

        // Écarter définitivement la carte choisie.
        joueur.ecarterCarte(static_cast<std::size_t>(idxCarte));
    }

    // Le joueur gagne un Argent a ca main
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    // je ne sais pas se que ca fait si il y a plus de carte argent
    joueur.ajouterCarteMain(plateau.creerCarte("Argent"));

    std::cout << "\nVous gagnez un Argent ajouté à votre main.\n";

}




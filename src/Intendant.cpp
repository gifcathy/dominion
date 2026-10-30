#include <iostream>
#include "Intendant.hpp"

// constructeur 
Intendant::Intendant() : Action("Intendant", "Action", 3){}; 

// destructeur 
Intendant::~Intendant(){}; 

// méthode d'affichage 
void Intendant::afficher() const{
    std::cout << "Intendant - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Choisissez : +2 cartes OU +2 pièces OU écartez 2 cartes de votre main" << std::endl;
}

// Jouer la carte
void Intendant::jouer(Joueur& joueur) {

    std::cout << "\n========================================\n";
    std::cout << "            CARTE : INTENDANT\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 cartes OU +2 pieces OU ecartez 2 cartes de votre main\n\n";

    std::cout << "[1] +2 cartes" << std::endl;
    std::cout << "[2] +2 pieces" << std::endl;
    std::cout << "[3] Ecarter 2 cartes de votre main" << std::endl;

    int choix;

    while (true) {
        std::cout << "Que voulez-vous faire : ";

        if (std::cin >> choix) {
            if (choix >= 1 && choix <= 3) {
                break;
            }

            std::cout << "Choix invalide. Choisissez un numero entre 1 et 3.\n";
        }
        else {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Saisie invalide. Entrez un nombre.\n";
        }
    }

    switch (choix) {

        // Choix 1 : piocher 2 cartes
        case 1: {
            std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(2);

            std::cout << "Vous avez pioche : " << std::endl;

            for (const std::string& nomCarte : cartesPiochees) {
                std::cout << "- " << nomCarte << std::endl;
            }

            break;
        }

        // Choix 2 : gagner 2 pieces
        case 2:
            joueur.ajouterArgent(2);
            std::cout << "Vous gagnez 2 pieces.\n";
            break;

        // Choix 3 : écarter jusqu'à 2 cartes de sa main
        case 3: {

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

            break;
        }

        default:
            break;
    }
}
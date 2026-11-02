#include <iostream>
#include <limits>
#include "Chapelle.hpp"

// constructeur 
Chapelle::Chapelle() : Action("Chapelle", "Action", 2){}; 

// destructeur 
Chapelle::~Chapelle(){}; 


// méthode d'affichage 
void Chapelle::afficher() const{
    std::cout << "Chapelle - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez jusqu'à 4 cartes de votre main" << std::endl;
}

// jouer la carte 

void Chapelle::jouer(Joueur& joueur)
{
    std::cout << "\n========================================\n";
    std::cout << "            CARTE : CHAPELLE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : écartez jusqu'à 4 cartes de votre main\n\n"; 

    int nbCartesMainJoueur = static_cast<int>(joueur.getMain().size());
    int maximum = nbCartesMainJoueur;

    if (nbCartesMainJoueur >= 4) {
        maximum = 4;
    }

    std::cout << "Voici votre main :" << std::endl;
    joueur.afficherMain();

    int nombreCartesAEcarter;

    // Choix du nombre de cartes à écarter
    while (true) {
        std::cout << "Veuillez saisir le nombre de cartes à écarter (0 à " << maximum << ")" << std::endl;
        std::cin >> nombreCartesAEcarter;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Saisie invalide" << std::endl;
            continue;
        }

        if (nombreCartesAEcarter >= 0 && nombreCartesAEcarter <= maximum) {
            break;
        }
        std::cout << "Saisie invalide" << std::endl;
    }

    // Choix des cartes à écarter
    for (int i = 0; i < nombreCartesAEcarter; ++i) {
        joueur.afficherMain();
        std::size_t indiceEcarte;

        while (true) {
            std::cout << "Veuillez saisir le numéro de la carte à écarter :" << std::endl;
            std::cin >> indiceEcarte;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Indice invalide" << std::endl;
                continue;
            }

            if (indiceEcarte < joueur.getMain().size()) {
                break;
            }
            std::cout << "Indice invalide" << std::endl;
        }
        joueur.ecarterCarte(indiceEcarte);
    }
    std::cout << "Fin de l'effet de la carte Chapelle" << std::endl;
}

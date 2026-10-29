#include <iostream>
#include <limits>
#include "Cave.hpp"

// constructeur 
Cave::Cave() : Action("Cave", "Action", 2){}; 

// destructeur 
Cave::~Cave(){}; 


// méthode d'affichage 
void Cave::afficher() const{
    std::cout << "Cave - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 Action, défaussez autant de cartes que vous voulez +1 carte par carte défaussée" << std::endl;
}

// jouer la carte 
void Cave::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "              CARTE : CAVE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 Action, défaussez autant de cartes que vous voulez +1 carte par carte "
              << "défaussée.\n\n"; 
    
    joueur.ajouterActions(1);

    std::cout << "\n ---- Cave ----" << std::endl;
    std::cout << "Vous pouvez défaussez autant de cartes que vous voulez" << std::endl;

    int nbCartesMainJoueur = static_cast<int>(joueur.getMain().size());


    std::cout << "Voici votre main :" << std::endl;
    joueur.afficherMain();

    int nombreCartesAEcarter;

    // Choix du nombre de cartes à écarter
    while (true) {
        std::cout << "Veuillez saisir le nombre de cartes à écarter (0 à " << nbCartesMainJoueur << ")" << std::endl;
        std::cin >> nombreCartesAEcarter;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Saisie invalide" << std::endl;
            continue;
        }

        if (nombreCartesAEcarter >= 0 && nombreCartesAEcarter <= nbCartesMainJoueur) {
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

            if (indiceEcarte >= 0 && static_cast<std::size_t>(indiceEcarte) < joueur.getMain().size()) {
                break;
            }
            std::cout << "Indice invalide" << std::endl;
        }
        joueur.defausserUneCarte(indiceEcarte);
    }

    joueur.piocherPlusieurCarte(nombreCartesAEcarter);
    std::cout << "Fin de l'effet de la carte Cave" << std::endl;
}
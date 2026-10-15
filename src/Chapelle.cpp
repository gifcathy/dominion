#include <iostream>
#include <limits>
#include "Chapelle.hpp"

// constructeur 
Chapelle::Chapelle() : ActionActionAttaque("Chapelle", "Action", 2){}; 

// destructeur 
Chapelle::~Chapelle(){}; 

// jouer la carte 
void Chapelle::jouer(Joueur& joueur){
    std::cout << "\n ---- Chapelle ----" << std::endl; 
    std::cout << "Vous pouvez écarter jusqu'à 4 cartes de votre main" << std::endl; 
    int nbCartesMainJoueur = static_cast<int>(joueur.getMain().size()); 
    int maximum; 
    int nombreCartesAEcarter; 

    // on crée le maximum de telle sorte à ce qu'on ne puisse pas supprimer plus de cartes qu'on a
    if (nbCartesMainJoueur >= 4){
        int maximum = 4; 
    }

    // on montre la main pour savoir combien de cartes on veut écarter 
    std::cout << "Voici votre main : " << std::endl; 
    joueur.afficherMain(); 

    // choix du nombre de cartes à écarter
    while(true){
        std::cout << "Veuillez saisir le nombre de cartes à écarter (0 à" << maximum << ")" << std::endl; 
        std::cin >> nombreCartesAEcarter ; 
        if(nombreCartesAEcarter > 0 && nombreCartesAEcarter <= maximum){
            break; 
        }
        std::cout << "Saisie invalide" << std::endl; 
        if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    for (int i = 0; i < nombreCartesAEcarter; ++i) {
        // on lui affiche à nouveau sa main pour qu'il sache quelles cartes enlever 
        joueur.afficherMain(); 

        // choix de la carte à écarter  
        std::size_t indiceEcarte; 
        while(true){
            std::cout << "Veuillez saisir le numéro de la carte à écarter :" << std::endl; 
            std::cin >> indiceEcarte; 
            if(indiceEcarte > 0 && indiceEcarte < joueur.getMain().size()){
                break; 
            }
            std::cout << "Indice invalide" << std::endl; 
            if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        joueur.ecarterCarte(indiceEcarte); 
    }
    std::cout << "Fin de l'effet de la carte Chapelle" << std::endl; 
}
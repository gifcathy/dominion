#include <iostream>
#include "VillageMinier.hpp"

// constructeur 
VillageMinier::VillageMinier() : Action("VillageMinier", "Action", 4){}; 

// destructeur 
VillageMinier::~VillageMinier(){}; 

// méthode d'affichage 
void VillageMinier::afficher() const{
    std::cout << "VillageMinier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 carte, + 2 actions, vous pouvez écarter immédiatement cette carte. Si vous l'écartez, +2 pièce" << std::endl;
}


// jouer la carte 
void VillageMinier::jouer(Joueur& joueur){

    std::cout << "\n========================================\n";
    std::cout << "          CARTE : VillageMinier\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 carte, + 2 actions, vous pouvez écartez la carte et si vous le faite vous gagnez +2 pièce\n\n"; 

    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(1); 
    std::cout << "Vous avez pioché : " << std::endl; 
    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    } 
    joueur.ajouterActions(2); 

    char choix;
    std::cout << "Voulez vous écarter cette carte ? (y ou n) :";
    std::cin >> choix;
    if(choix == 'y' || choix == 'Y'){
        Carte* carteVM = nullptr;

        // On recherche Festin dans la liste des cartes jouées.
        for (const auto& carte : joueur.getCartesJouees()) {
            if (carte->getNom() == "VillageMinier") {
                carteVM = carte.get();
                break;
            }
        }

        // On vérifie qu'on a bien trouvé la carte.
        if (carteVM == nullptr) {
            std::cout << "Impossible de retrouver la carte VillageMinier." << std::endl;
            return;
        }

        // On écarte Festin du jeu.
        joueur.ecarterCarteJouee(carteVM);

        joueur.ajouterArgent(2);
    }
}
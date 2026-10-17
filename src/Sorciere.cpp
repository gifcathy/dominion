#include <iostream>
#include "Sorciere.hpp"

// constructeur 
Sorciere::Sorciere() : ActionPlateau("Sorciere", "Action-Attaque", 5){}; 

// destructeur 
Sorciere::~Sorciere(){}; 

// méthode d'affichage 
void Sorciere::afficher() const{
    std::cout << "Sorcière - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +2 cartes, tous vos adversaires piochent une malédiction et la place sur leur défausse" 
              << std::endl;
}

void Sorciere::jouer(Joueur& joueur){
    joueur.piocherPlusieurCarte(2);
}

void Sorciere::jouerPlateau(std::vector<Joueur>& joueurs, int joueurActuel, Plateau& plateau){
    for (std::size_t i = 0; i < joueurs.size(); ++i) {
        if (static_cast<int>(i) == joueurActuel) {
            continue;
        }

        // Vérifier si ce joueur peut se protéger avec une Douve.
        // Sinon, lui donner une Malédiction.
    }
}
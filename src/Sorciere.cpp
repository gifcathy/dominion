#include <iostream>
#include "Sorciere.hpp"

#include "Plateau.hpp"
#include "Carte.hpp"

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


void Sorciere::jouerPlateau(std::vector<Joueur>& joueurs, int& joueurActuel, Plateau& plateau){
    for (std::size_t i = 0; i < joueurs.size(); ++i){
        // Le joueur qui a joué la Sorcière n'est pas attaqué.
        if (static_cast<int>(i) == joueurActuel){
            continue;
        }

        // Si le joueur possède une Douve en main, il peut se protéger contre l'attaque.
        // ici on ne lui laisse pas le choix d'utilise le pouvoir de la Douve en reaction
        if (joueurs[i].possedeDouveEnMain()){
            std::cout << "Le joueur " << i + 1 << " peut révéler une Douve pour se protéger." << std::endl;
            continue;
        }

        // Vérifier que la pile de Malédictions n'est pas vide.
        if (plateau.getNombreCartes("Malédiction") <= 0){
            std::cout << "Le joueur " << i + 1 << " ne reçoit pas de Malédiction : " << "la pile est vide." << std::endl;
            continue;
        }

        // Créer une Malédiction et l'ajouter à la défausse.
        std::unique_ptr<Carte> carte = plateau.creerCarte("Malédiction");
        joueurs[i].ajouterCarte(std::move(carte));
    }
}

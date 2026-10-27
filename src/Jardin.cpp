#include <iostream>
#include "Jardin.hpp"
#include <cmath>

// constructeur 
Jardin::Jardin() : Victoire("Jardin", 0, 4){}; 

// destructeur 
Jardin::~Jardin(){}; 

// getter 
int Jardin::getNbPointVictoireJardin(const int taille_deck) const{
    return std::floor(taille_deck/10); 
}

// méthode d'affichage 
void Jardin::afficher() const{
    std::cout << "Jardin - Cout : " << getCout() << "\n"
              << "Type de carte : Victoire \n" 
              << "Description : Vaut 1 point de victoire pour chaque 10 cartes dans votre pioche (arrondi à l'unité inférieure)" 
              << std::endl;
}

// pas de méthode jouer parce qu'elle ne produit aucun effet quand on la joue
// calculs des points en fin de partie ajoutés dans joueur 
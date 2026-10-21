#include <iostream>
#include "ChambreDuConseil.hpp"

// constructeur 
ChambreDuConseil::ChambreDuConseil() : ActionPlateau("CDC", "Action", 5){}; 

// destructeur 
ChambreDuConseil::~ChambreDuConseil(){}; 

// méthode d'affichage 
void ChambreDuConseil::afficher() const {
    std::cout << "Chambre du conseil (CDC) - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +4 cartes, +1 achat, tous vos adversaires piochent 1 carte" << std::endl;
}


// jouer la carte 
void ChambreDuConseil::jouer(Joueur& joueur){
    joueur.piocherPlusieurCarte(4); 
    joueur.ajouterAchats(1);
}

void ChambreDuConseil::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){
    for(int i=0; i < listeJoueurs.size(); i++){
        if(i != indiceJoueurActuel){
            Joueur& joueur = listeJoueurs.at(i);
            joueur.piocher();
        }
    }
}
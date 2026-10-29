#include <iostream>
#include "ChambreDuConseil.hpp"

// constructeur 
ChambreDuConseil::ChambreDuConseil() : ActionPlateau("ChambreDuConseil", "Action", 5){}; 

// destructeur 
ChambreDuConseil::~ChambreDuConseil(){}; 

// méthode d'affichage 
void ChambreDuConseil::afficher() const {
    std::cout << "Chambre du conseil - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +4 cartes, +1 achat, tous vos adversaires piochent 1 carte" << std::endl;
}


// jouer la carte 
void ChambreDuConseil::jouer(Joueur& joueur){
    joueur.piocherPlusieurCarte(4); 
    joueur.ajouterAchats(1);
}

void ChambreDuConseil::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){

    std::cout << "\n========================================\n";
    std::cout << "       CARTE : CHAMBRE DU CONSEIL\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +4 cartes, +1 achat, tous vos adversaires piochent 1 carte\n\n"; 

    for(std::size_t i=0; i < listeJoueurs.size(); i++){
        if(i != static_cast<std::size_t>(indiceJoueurActuel)){
            Joueur& joueur = listeJoueurs.at(i);
            joueur.piocher();
        }
    }
}
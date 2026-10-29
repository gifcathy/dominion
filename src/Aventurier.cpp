#include <iostream> 
#include "Aventurier.hpp"

// constructeur 
Aventurier::Aventurier() : ActionPlateau("Aventurier", "Action", 6){}; 

// destructeur 
Aventurier::~Aventurier(){};

// méthode d'affichage 
void Aventurier::afficher() const{
    std::cout << "Aventurier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Dévoilez des cartes de votre deck jusqu'à ce que 2 cartes Trésor "
              << "soient dévoilées. ajoutez ces cartes Trésor à votre main et défaussez les autres "
              << "cartes dévoilées."
              << std::endl;
}


// jouer la carte 
void Aventurier::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){
    std::cout << "\n========================================\n";
    std::cout << "           CARTE : AVENTURIER\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Dévoilez des cartes de votre deck jusqu'à ce que 2 cartes Trésor "
              << "soient dévoilées. ajoutez ces cartes Trésor à votre main et défaussez les autres "
              << "cartes dévoilées.\n\n"; 
    
    std::vector<std::unique_ptr<Carte>> cartesDevoilees; 
    int compteurTresorDevoile = 0; 
    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel]; 

    while(compteurTresorDevoile < 2){
        if(joueurActuel.getNbrCarteDeck() == 0){
            joueurActuel.passerDefausseADeck(); 
        }
        // cas où il n'a toujours pas de deck 
        if(joueurActuel.getNbrCarteDeck() == 0){
            break ; 
        }
        std::unique_ptr<Carte> carte = joueurActuel.prendreCarteDessusDeck();
        // Eviter de conserver un pointeur nul
        if(carte == nullptr){
            break; 
        }

        // on compte le trésor qui vient d'être dévoilé 
        if(carte->getType() == "Tresor"){
            compteurTresorDevoile ++; 
        }

        // on ajoute la carte qui vient d'être dévoilée à cartesDevoilees 
        cartesDevoilees.push_back(std::move(carte));
    }

    // on ajoute les trésor dans la main et on défausse les autres cartes 
    for(std::size_t i = 0; i < cartesDevoilees.size(); i++){
        if(cartesDevoilees[i]->getType() == "Tresor"){
            joueurActuel.ajouterCarteMain(std::move(cartesDevoilees[i])); 
        }
        else{
            joueurActuel.ajouterCarte(std::move(cartesDevoilees[i]));
        }
    }
}
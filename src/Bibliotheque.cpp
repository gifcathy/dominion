#include <iostream>
#include <limits>
#include "Bibliotheque.hpp"

// constructeur 
Bibliotheque::Bibliotheque() : ActionPlateau("Bibliotheque", "Action", 5){}

// destructeur 
Bibliotheque::~Bibliotheque(){}

// méthode d'affichage 
void Bibliotheque::afficher() const{
    std::cout << "Bibliotheque - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Piochez jusqu'à ce que vous ayez 7 cartes en main. Chaque carte Action "
              << "piochée peut être mise de côté. Défaussez les cartes mises de côté lorsque vous "
              << "avez terminé de piocher."
              << std::endl;
}


// jouer la carte 
void Bibliotheque::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){
    std::cout << "\n========================================\n";
    std::cout << "           CARTE : BIBLIOTHÈQUE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Piochez jusqu'à ce que vous ayez 7 cartes en main. Chaque carte Action piochée "
              << "peut être mise de côté. Défaussez les cartes mises de côté lorsque vous avez terminé de piocher.\n\n";


    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel]; 
    int nombreCarteMainJoueur = static_cast<int>(joueurActuel.getMain().size()); 
    std::vector<std::unique_ptr<Carte>> cartesADefausser; 

    // le joueur pioche jusqu'à avoir 7 cartes en main 
    if(nombreCarteMainJoueur < 7){
        while(nombreCarteMainJoueur < 7){
            if(joueurActuel.getNbrCarteDeck() == 0){
                joueurActuel.passerDefausseADeck(); 
            }
            // cas où il n'a toujours pas de deck 
            if(joueurActuel.getNbrCarteDeck() == 0){
                break ; 
            }

            // on récupère la carte au dessus du deck 
            std::unique_ptr<Carte> carte = joueurActuel.prendreCarteDessusDeck();
            if(carte == nullptr){
                break; 
            }

            bool saisieInvalide = true; 

            if(carte->getType() == "Action" || carte->getType() == "Action-Attaque" 
                    || carte->getType() == "Action-Reaction"){

                int reponse = 0; 
                std::cout << "Vous avez pioché la carte " << carte->getNom() << std::endl; 
                std::cout << "Voulez vous l'ajouter à votre main ou la mettre de côté ? \n" << std::endl; 
                std::cout << "1. L'ajouter à la main" << std::endl; 
                std::cout << "2. La mettre de côté" << std::endl; 
                std::cout << "Votre choix : "; 

                while(saisieInvalide){
                    if (!(std::cin >> reponse)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        std::cout << "Saisie invalide. Veuillez saisir 1 ou 2." << std::endl;
                        std::cout << "Votre choix : " << std::endl;  
                        continue;
                    }
                    else if(reponse != 1 && reponse !=2){
                        std::cout << "Veuillez choisir 1 ou 2" << std::endl; 
                    }
                    else{
                        saisieInvalide = false; 
                    }
                }

                if(reponse == 1){
                    joueurActuel.ajouterCarteMain(std::move(carte)); 
                    nombreCarteMainJoueur ++; 
                }
                else if(reponse == 2){
                    cartesADefausser.push_back(std::move(carte)); 
                }
            }
            else{
                joueurActuel.ajouterCarteMain(std::move(carte)); 
                nombreCarteMainJoueur++; 
            }
        }
    }
    else {
        std::cout << "Vous avez déjà 7 cartes ou plus en main" << std::endl; 
    }

    // on défausse les cartes qu'on a mis de côté 
    for(auto& carte : cartesADefausser){
        joueurActuel.ajouterCarte(std::move(carte)); 
    }
}
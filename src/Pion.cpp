#include <iostream>
#include <limits>
#include <memory>
#include <utility>
#include <Pion.hpp>

// constructeur 
Pion::Pion() : Action("Pion", "Action", 2){}; 

// destructeur 
Pion::~Pion(){}; 

// méthode d'affichage 
void Pion::afficher() const {
    std::cout << "Pion - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Choisissez 2 : +1 carte, +1 action, +1 achat, +1 trésor. Les choix "
              << "doivent être différents." 
              << std::endl;
}


// jouer la carte
void Pion::jouer(Joueur& joueur){
    std::cout << "\n========================================\n";
    std::cout << "            CARTE : PION\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Choisissez 2 : +1 carte, +1 action, +1 achat, +1 trésor. Les choix "
              << "doivent être différents.\n\n";

    int nombreChoix = 0; 
    int choixDejaPris = 0; 
    while(nombreChoix < 2){
        std::cout << "Quelle action voulez vous faire ?" << std::endl; 
        std::cout << "1. +1 carte" << std::endl; 
        std::cout << "2. +1 action" << std::endl; 
        std::cout << "3. +1 achat" << std::endl; 
        std::cout << "4. +1 trésor" << std::endl; 
        std::cout << "Votre choix :" << std::endl; 

        int choix = 0; 
        while(true){
            if(!(std::cin >> choix)){
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Saisie invalide. Veuillez saisir un chiffre entre 1 et 4 : ";
            }
            else if(choix <= 0 || choix >= 5){
                std::cout << "Saisie invalide. Veuillez saisir un chiffre entre 1 et 4 : "; 
            }
            else if(choix == choixDejaPris){
                std::cout << "Vous avez déjà choisi cette option, veuillez en choisir un autre :"; 
            }
            else{
                nombreChoix++; 
                choixDejaPris = choix; 
                break; 
            }
        }

        
        switch (choix){
            case 1: {
                if(joueur.getNbrCarteDeck() == 0){
                    joueur.passerDefausseADeck(); 
                }
                if(joueur.getNbrCarteDeck() == 0){
                    std::cout << "Vous n'avez plus assez de cartes dans votre Deck pour piocher" << std::endl;
                    break; 
                }
                std::unique_ptr<Carte> carte = joueur.prendreCarteDessusDeck(); 
                std::cout << "Vous avez pioché : \n" << std::endl; 
                std::cout << "- " << carte->getNom() << std::endl;
                joueur.ajouterCarteMain(std::move(carte)); 
                break;
            }
            case 2: {
                joueur.ajouterActions(1); 
                std::cout << "Vous avez gagné une action !" << std::endl;
                break; 
            }
            case 3: {
                joueur.ajouterAchats(1); 
                std::cout << "Vous avez gagné un achat !" << std::endl; 
                break;
            }
            case 4: {
                joueur.ajouterArgent(1); 
                std::cout << "Vous avez gagné un trésor !" << std::endl; 
                break;
            }
            default:
                break;
        }
    }
}
#include <iostream>
#include "Milice.hpp"

// constructeur 
Milice::Milice() : ActionPlateau("Milice", "Action-Attaque", 4){}

// destructeur 
Milice::~Milice(){}; 

// méthode d'affichage 
void Milice::afficher() const {
    std::cout << "Milice - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +2 Trésor. Tous vos adversaires défaussent leurs cartes de façon "
              << "à n'avoir que 3 cartes en main." 
              << std::endl;
}


// jouer la carte 
void Milice::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau&){
    std::cout << "\n========================================\n";
    std::cout << "             CARTE : MILICE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +2 pièces. Tous vos adversaires défaussent leurs cartes de façon à "
              << "n'avoir que 3 cartes en main. \n\n";

    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel]; 
    joueurActuel.ajouterArgent(2); 

    for(std::size_t i = 0; i < listeJoueurs.size(); i++){
        Joueur& joueur = listeJoueurs[i]; 
        if(i == static_cast<std::size_t>(indiceJoueurActuel)){
            continue;
        }

        // L'adversaire défausse jusqu'à avoir 3 cartes en main
        while (joueur.getMain().size() > 3) {
            std::cout << "Joueur " << i + 1 << ", voici votre main :" << std::endl;

            joueur.afficherMain();

            std::cout << "Donnez l'indice de la carte que vous voulez defausser : ";

            int indiceAEcarter;
            bool saisieInvalide = true;

            while (saisieInvalide) {
                if (!(std::cin >> indiceAEcarter)) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "Saisie invalide. Veuillez saisir un indice valide : ";
                }
                else if (indiceAEcarter < 0 
                    || static_cast<std::size_t>(indiceAEcarter) >= joueur.getMain().size()) {
                    std::cout << "Indice invalide. Veuillez choisir un indice valide : ";
                }
                else {
                    saisieInvalide = false;
                }
            }

            // Défausser la carte choisie
            joueur.defausserUneCarte(static_cast<std::size_t>(indiceAEcarter));
        }

        std::cout << "Joueur " << i + 1 << " a maintenant 3 cartes ou moins en main." << std::endl;
    }
}


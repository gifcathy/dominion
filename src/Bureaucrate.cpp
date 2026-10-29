#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Bureaucrate.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Bureaucrate::Bureaucrate() : ActionPlateau("Bureaucrate", "Action-Attaque", 4){}; 

// destructeur 
Bureaucrate::~Bureaucrate(){}; 

// méthode d'affichage 
void Bureaucrate::afficher() const {
    std::cout << "Bureaucrate - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +1 carte Argent placez-la sur votre deck. Tous vos adversaires dévoilent 1 carte Victoire et placent sur leur deck (sinon ils devoilent leur main afin que vous puissiez voir qu'ils n'ont pas de cartes Victoire)" 
              << std::endl;
}

// jouer la carte 
void Bureaucrate::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){

    std::cout << "\n========================================\n";
    std::cout << "           CARTE : BUREAUCRATE\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 carte Argent placez-la sur votre deck. Tous vos adversaires dévoilent "
              << "1 carte Victoire et placent sur leur deck (sinon ils devoilent leur main afin que "
              << "vous puissiez voir qu'ils n'ont pas de cartes Victoire).\n\n"; 

    // 1. Le joueur gagne un Argent sur le dessus de son deck
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    // je ne sais pas se que ca fait si il y a plus de carte argent
    joueur.ajouterCarteDessusDeck(plateau.creerCarte("Argent"));

    std::cout << "\nVous gagnez un Argent sur le dessus de votre deck.\n";

    // Ordre de priorite des cartes Victoire
    std::vector<std::string> priorite = {
        "Domaine",
        "Duche",
        "Jardin",
        "Duc",
        "Province"
    };
    
    // 2. Chaque adversaire révèle une carte Victoire
    for (size_t i = 0; i < listeJoueurs.size(); ++i) {

        // Ne pas traiter le joueur qui joue le Bureaucrate
        if (static_cast<int>(i) == indiceJoueurActuel) {
            continue;
        }

        Joueur& adversaire = listeJoueurs.at(i);

        std::cout << "\n--- Joueur " << i + 1 << " ---\n";

        bool carteTrouvee = false;

        // Chercher une carte Victoire selon l'ordre de priorite
        for (size_t p = 0; p < priorite.size() && !carteTrouvee; ++p) {

            for (size_t j = 0; j < adversaire.getMain().size(); ++j) {

                if (adversaire.getCarte(j) != nullptr && adversaire.getCarte(j)->getNom() == priorite[p]) {

                    std::string nomCarte = adversaire.getCarte(j)->getNom();

                    std::cout << "Carte revelee : " << nomCarte << '\n';

                    adversaire.mettreCarteMainDessusDeck(j);

                    std::cout << nomCarte << " est placee sur le dessus du deck.\n";

                    carteTrouvee = true;
                    break;
                }
            }
        }

        // Aucune carte Victoire trouvee : reveler toute la main
        if (!carteTrouvee) {

            std::cout << "Aucune carte Victoire en main.\n";
            std::cout << "Main revelee :\n";

            for (size_t j = 0; j < adversaire.getMain().size(); ++j) {

                if (adversaire.getCarte(j) != nullptr) {
                    std::cout << "- " << adversaire.getCarte(j)->getNom() << '\n';
                }
            }
        }
    }
}
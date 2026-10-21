#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Festin.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Festin::Festin() : ActionPlateau("Festin", "Action", 4){}; 

// destructeur 
Festin::~Festin(){}; 

// méthode d'affichage 
void Festin::afficher() const {
    std::cout << "Festin - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez cette carte, recevez une carte coûtant jusqu'à 5 pièces" 
              << std::endl;
}


// jouer la carte 
void Festin::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    Carte* festin = nullptr;

    // on met dans festin l'adresse de la carte dans la liste des cartes jouées 
    for (const auto& carte : joueur.getCartesJouees()) {
        if (carte->getNom() == "Festin") {
            festin = carte.get();
            break;
        }
    }

    // on vérifie qu'on a bien trouvé la carte dans la liste des cartes jouées 
    if (festin == nullptr) {
        std::cout << "Impossible de retrouver la carte Festin." << std::endl;
        return;
    }

    // Afficher les cartes disponibles qui coûtent au maximum 5 pièces.
    plateau.afficherCarteCoutInfEgal(5);

    // Demander au joueur quelle carte il souhaite gagner.
    std::string nomCarte;
    bool choixValide = false; 

    while(!choixValide){
        std::cout << "Quelle carte souhaitez-vous gagner ? ";
        std::getline(std::cin >> std::ws, nomCarte);
        // Vérifier que la carte existe sur le plateau.
        if (!plateau.contientCarte(nomCarte)) {
            std::cout << "Cette carte n'est pas disponible sur le plateau."
                    << std::endl;
            continue;
        }

        // Vérifier que la pile n'est pas vide.
        if (plateau.getNombreCartes(nomCarte) <= 0) {
            std::cout << "Cette pile est vide." << std::endl;
            continue;
        }

        // Vérifier que la carte coûte au maximum 5 pièces.
        if (plateau.getCoutCarte(nomCarte) > 5) {
            std::cout << "Cette carte coûte plus de 5 pièces." << std::endl;
            continue;
        }
        choixValide = true; 
    }
   

    // Retirer une carte de la pile du plateau.
    if (plateau.acheterCarte(nomCarte)) {
        // on crée la carte que le joueur a choisi
        std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);

        // Ajouter la carte gagnée à la défausse du joueur.
        joueur.ajouterCarte(std::move(carte));

        std::cout << "Vous avez gagné la carte " << nomCarte << " !" << std::endl;
    }

    // une fois que l'action de la carte est finie, on écarte la carte 
    joueur.ecarterCarteJouee(festin);
}
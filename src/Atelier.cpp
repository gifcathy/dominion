#include <iostream> 
#include "Atelier.hpp"

// constructeur
Atelier::Atelier() : ActionPlateau("Atelier", "Action", 3){}; 

// destructeur 
Atelier::~Atelier(){}; 

// méthode d'affichage
void Atelier::afficher() const {
    std::cout << "Atelier - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : Recevez une carte coûtant jusqu'à 4 pièces" << std::endl;
}


// jouer la carte 
void Atelier::jouerPlateau(std::vector<Joueur>& listeJoueurs,int& indiceJoueurActuel, Plateau& plateau){
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    // Afficher les cartes disponibles qui coûtent au maximum 4 pièces.
    plateau.afficherCarteCoutInfEgal(4);

    // Demander au joueur quelle carte il souhaite gagner.
    std::string nomCarte;
    std::cout << "Quelle carte souhaitez-vous gagner ? ";
    std::getline(std::cin >> std::ws, nomCarte);

    // Vérifier que la carte existe sur le plateau.
    if (!plateau.contientCarte(nomCarte)) {
        std::cout << "Cette carte n'est pas disponible sur le plateau."
                  << std::endl;
        return;
    }

    // Vérifier que la pile n'est pas vide.
    if (plateau.getNombreCartes(nomCarte) <= 0) {
        std::cout << "Cette pile est vide." << std::endl;
        return;
    }

    // Vérifier que la carte coûte au maximum 4 pièces.
    if (plateau.getCoutCarte(nomCarte) > 4) {
        std::cout << "Cette carte coûte plus de 4 pièces." << std::endl;
        return;
    }

    // Retirer une carte de la pile du plateau.
    if (!plateau.acheterCarte(nomCarte)) {
        std::cout << "Impossible de récupérer cette carte."
                  << std::endl;
        return;
    }

    // Créer l'objet représentant la carte choisie.
    std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);

    // Ajouter la carte gagnée à la défausse du joueur.
    joueur.ajouterCarte(std::move(carte));

    std::cout << "Vous avez gagné la carte " << nomCarte << " !" << std::endl;
}
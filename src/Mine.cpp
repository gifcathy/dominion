#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Mine.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Mine::Mine() : ActionPlateau("Mine", "Action", 4){}; 

// destructeur 
Mine::~Mine(){}; 

// méthode d'affichage 
void Mine::afficher() const {
    std::cout << "Mine - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : écartez une carte Tresor de votre main, recevez une carte Tresor coûtant jusqu'à 3 pièces de plus; ajoutez cette carte a votre main" 
              << std::endl;
}


// jouer la carte 
void Mine::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    joueur.afficherMain();

    int indice;

    // 1. Choisir un Tresor a ecarter.
    while (true){
        std::cout << "Choisissez un Tresor a ecarter (-1 pour annuler) : ";

        if (!(std::cin >> indice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide." << std::endl;
            continue;
        }

        if (indice == -1) {
            return;
        }

        if (indice < 0 || static_cast<std::size_t>(indice) >= joueur.getMain().size()) {
            std::cout << "Indice invalide." << std::endl;
            continue;
        }

        if (joueur.getMain()[indice]->getType() != "Tresor") {
            std::cout << "Vous devez choisir un Tresor." << std::endl;
            continue;
        }

        break;
    }

    // 2. Calculer le cout maximal avant d'ecarter la carte.
    int coutMax = joueur.getMain()[indice]->getCout() + 3;

    // 3. Ecarter le Tresor choisi.
    joueur.ecarterCarte(static_cast<std::size_t>(indice));

    // 4. Afficher les Tresors disponibles.
    plateau.afficherTresorCoutInfEgal(coutMax);

    // 5. Choisir un Tresor a gagner.
    std::string nomCarte;

    while (true){
        std::cout << "Nom du Tresor a gagner (cout maximal " << coutMax << ") : ";

        if (!(std::cin >> nomCarte)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide." << std::endl;
            continue;
        }

        // Verifier que la carte est un Tresor et qu'elle
        // respecte le cout maximal.
        if (nomCarte != "Cuivre" && nomCarte != "Argent" && nomCarte != "Or") {
            std::cout << "Ce n'est pas un Tresor valide." << std::endl;
            continue;
        }

        std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);

        if (carte->getType() != "Tresor") {
            std::cout << "Vous devez choisir un Tresor." << std::endl;
            continue;
        }

        if (carte->getCout() > coutMax) {
            std::cout << "Cette carte depasse le cout maximal autorise." << std::endl;
            continue;
        }

        // Retirer une carte de la pile.
        if (!plateau.acheterCarte(nomCarte)) {
            std::cout << "Cette pile est vide." << std::endl;
            continue;
        }

        // Ajouter la carte directement a la main.
        joueur.ajouterCarteMain(std::move(carte));

        return;
    }
}
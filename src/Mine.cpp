#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "Mine.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

// constructeur 
Mine::Mine() : ActionPlateau("Mine", "Action", 5){}; 

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
    std::vector<std::string> tresorsDisponibles;
    std::cout << "Trésors disponibles :\n";
    plateau.afficherTresorCoutInfEgal(coutMax, tresorsDisponibles);

    // Verifier qu'il existe au moins une carte disponible.
    if (tresorsDisponibles.empty()) {
        std::cout << "\nAucune trésor disponible.\n";
        return;
    }

    // 5. Choisir un Tresor a gagner.
    int choix;
    

    while (true){
        std::cout << "Votre choix (0 pour annuler) : ";

        if (std::cin >> choix) {
            if (choix >= 0 && static_cast<std::size_t>(choix) <= tresorsDisponibles.size()) {
                break;
            }

            std::cout << "[ERREUR] Choix invalide.\n";
        }
        else {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

            std::cout << "[ERREUR] Entrez un numero valide.\n";
        }
    }

    // Annuler le choix.
    if (choix == 0) {
        std::cout << "Vous n'avez gagne aucune carte.\n";
        return;
    }

    // Recuperer le nom de la carte choisie.
    const std::string& nomCarte = tresorsDisponibles[static_cast<std::size_t>(choix - 1)];

    // Retirer une carte de la pile du plateau.
    if (!plateau.acheterCarte(nomCarte)) {
        std::cout << "[ERREUR] Impossible de recuperer cette carte.\n";
        return;
    }

    // Creer la carte et l'ajouter a la defausse du joueur.
    std::unique_ptr<Carte> carte = plateau.creerCarte(nomCarte);
    joueur.ajouterCarte(std::move(carte));

    std::cout << "\n[SUCCES] Vous avez gagne la carte " << nomCarte << " !\n";
    std::cout << "========================================\n";
}
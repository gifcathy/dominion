#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "Cour.hpp"

// constructeur 
Cour::Cour() : Action("Cour", "Action", 2){}; 

// destructeur 
Cour::~Cour(){}; 


// méthode d'affichage 
void Cour::afficher() const{
    std::cout << "Cour - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +3 cartes, Placez une carte de votre main sur le dessus de votre deck" << std::endl;
}

// Jouer la carte
void Cour::jouer(Joueur& joueur) {

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : COUR\n";
    std::cout << "========================================\n";
    std::cout << "+3 cartes, placez une carte de votre main sur le dessus de votre deck\n\n";

    // Piocher 3 cartes.
    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(3);

    std::cout << "Vous avez pioche :" << std::endl;

    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    }

    // Vérifier que la main n'est pas vide.
    if (joueur.getMain().empty()) {
        std::cout << "Vous n'avez aucune carte a remettre sur votre deck.\n";
        return;
    }

    // Afficher la main du joueur.
    joueur.afficherMain();

    std::size_t idxCarte;

    while (true) {
        std::cout << "Quelle carte voulez-vous remettre sur votre deck ? (indice) : ";

        if (!(std::cin >> idxCarte)) {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Saisie invalide." << std::endl;
            continue;
        }

        if (idxCarte < joueur.getMain().size()) {
            break;
        }

        std::cout << "Indice invalide." << std::endl;
    }

    // Récupérer la carte choisie. On récupère la propriété de la carte choisie depuis la main
    std::unique_ptr<Carte> carte = std::move(joueur.getMain()[idxCarte]);

    // Supprimer la carte de la main. On supprime son ancien emplacement dans la main.
    joueur.getMain().erase(joueur.getMain().begin() + idxCarte);

    // Placer la carte sur le dessus du deck. On transfère la carte vers le deck.
    joueur.ajouterCarteDessusDeck(std::move(carte));

    std::cout << "La carte a ete remise sur le dessus de votre deck.\n";
}

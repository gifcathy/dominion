#include <iostream>
#include "Larbin.hpp"

// constructeur 
Larbin::Larbin() : ActionPlateau("Larbin", "Action-Attaque", 5){}; 

// destructeur 
Larbin::~Larbin(){}; 

// méthode d'affichage 
void Larbin::afficher() const {
    std::cout << "Larbin - Cout : " << getCout() << "\n"
              << "Type de carte : Action-Attaque \n" 
              << "Description : +1 action, choisissez : +2 pièces OU défaussez vtre main, +4 cartes, et tous les autres joueurs qui ont au moins 5 cartes en main défaussent leur main et piochent 4 carte" << std::endl;
}


// jouer la carte 
void Larbin::jouer(Joueur& joueur) {
    std::cout << "\n========================================\n";
    std::cout << "             CARTE : LARBIN\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 action, choisissez : +2 pièces OU défaussez votre main, +4 cartes, et tous les autres joueurs qui ont au moins 5 cartes en main défaussent leur main et piochent 4 carte\n\n"; 

    // Ajouter 1 action
    joueur.ajouterActions(1);
}

void Larbin::jouerPlateau(std::vector<Joueur>& listeJoueurs,
                          int& indiceJoueurActuel,
                          Plateau&) {

    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    std::cout << "\n[1] +2 pièces" << std::endl;
    std::cout << "[2] Défausser votre main et piocher 4 cartes. "
              << "Les autres joueurs ayant au moins 5 cartes en main "
              << "défaussent leur main et piochent 4 cartes." << std::endl;

    int choix;

    // Demander le choix du joueur
    while (true) {
        std::cout << "Que voulez-vous faire : ";

        if (std::cin >> choix) {
            if (choix >= 1 && choix <= 2) {
                break;
            }

            std::cout << "Choix invalide. Choisissez 1 ou 2.\n";
        }
        else {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Saisie invalide. Entrez un nombre.\n";
        }
    }

    switch (choix) {

        // Choix 1 : +2 pièces
        case 1:
            joueur.ajouterArgent(2);
            break;

        // Choix 2 : défausser sa main et piocher 4 cartes
        case 2: {

            std::cout << "\nVous défaussez toute votre main.\n";

            // Défausser toutes les cartes de sa main
            while (!joueur.getMain().empty()) {
                joueur.defausserUneCarte(0);
            }

            // Piocher 4 cartes
            joueur.piocherPlusieurCarte(4);

            std::cout << "\nLes autres joueurs sont maintenant attaqués.\n";

            // Parcourir tous les joueurs
            for (std::size_t i = 0; i < listeJoueurs.size(); i++) {

                // Ne pas attaquer le joueur qui a joué le Larbin
                if (static_cast<int>(i) == indiceJoueurActuel) {
                    continue;
                }

                Joueur& adversaire = listeJoueurs[i];

                // L'adversaire doit avoir au moins 5 cartes en main
                if (adversaire.getMain().size() < 5) {
                    continue;
                }

                std::cout << "\nLe joueur " << i + 1 << " possède au moins 5 cartes en main.\n";

                // Vérifier si l'adversaire possède une Douve
                if (adversaire.possedeDouveEnMain()) {

                    int choixDouve;

                    std::cout << "\nDonnez l'ordinateur au joueur " << i + 1 << std::endl;
                    std::cout << "Vous possédez une Douve !\n";
                    std::cout << "[1] Révéler la Douve et annuler l'attaque\n";
                    std::cout << "[2] Ne pas révéler la Douve\n";

                    // Demander si le joueur souhaite révéler sa Douve
                    while (true) {
                        std::cout << "Votre choix : ";

                        if (std::cin >> choixDouve) {
                            if (choixDouve == 1 || choixDouve == 2) {
                                break;
                            }

                            std::cout << "Choix invalide. Choisissez 1 ou 2.\n";
                        }
                        else {
                            if (std::cin.eof())
                                return;

                            std::cin.clear();
                            std::cin.ignore(
                                std::numeric_limits<std::streamsize>::max(), '\n'
                            );

                            std::cout << "Saisie invalide. Entrez un nombre.\n";
                        }
                    }

                    std::cout << "Redonnez l'ordinateur au joueur principale !\n";
                    std::cout << "\nAppuyez sur Entree remprendre la partie ...";
                    // Attendre que le joueur appuie sur Entree
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                    std::cin.get();

                    // Si le joueur révèle sa Douve, il est protégé
                    if (choixDouve == 1) {
                        std::cout << "Le joueur " << i + 1 << " révèle sa Douve et annule l'attaque !\n";
                        continue;
                    }
                }

                // L'adversaire subit l'attaque
                std::cout << "Le joueur " << i + 1 << " défausse toute sa main et pioche 4 cartes.\n";

                // Défausser toute sa main
                while (!adversaire.getMain().empty()) {
                    adversaire.defausserUneCarte(0);
                }

                // Piocher 4 cartes
                adversaire.piocherPlusieurCarte(4);
            }

            break;
        }

        default:
            break;
    }
}
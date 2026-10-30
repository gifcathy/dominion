#include <iostream>
#include "Baron.hpp"
#include "Plateau.hpp"

// constructeur 
Baron::Baron() : ActionPlateau("Baron", "Action", 4){}; 

// destructeur 
Baron::~Baron(){}; 

// méthode d'affichage 
void Baron::afficher() const{
    std::cout << "Baron - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 achat. Vous pouvez défausser une carte Domaine. Dans ce cas " 
              << "vous obtenez 4 trésors. Sinon recevez une carte domaine."
              << std::endl;
}

// jouer la carte 
void Baron::jouer(Joueur& joueur){
    joueur.ajouterAchats(1); 
}

void Baron::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau){

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : BARON\n";
    std::cout << "========================================\n";
    std::cout << "Effet : +1 achat.\n";
    std::cout << "Vous pouvez defausser une carte Domaine.\n";
    std::cout << "Si vous le faites, vous obtenez +4 pieces.\n";
    std::cout << "Sinon, vous recevez une carte Domaine.\n\n";

    Joueur& joueurActuel = listeJoueurs[indiceJoueurActuel];

    // Recuperer la main du joueur
    const auto& mainJoueur = joueurActuel.getMain();

    // Rechercher tous les Domaines dans la main
    std::vector<std::size_t> indicesDomaines;

    for (std::size_t i = 0; i < mainJoueur.size(); i++) {
        if (mainJoueur[i]->getNom() == "Domaine") {
            indicesDomaines.push_back(i);
        }
    }

    int choix = 0;

    // Si le joueur possede au moins un Domaine
    if (!indicesDomaines.empty()) {
        std::cout << "Vous possedez " << indicesDomaines.size() << " carte(s) Domaine.\n";
        std::cout << "Voulez-vous en defausser une ?\n";
        std::cout << "1. Oui\n";
        std::cout << "2. Non\n";
        std::cout << "Votre choix : ";

        // Verifier la saisie
        while (true) {
            if (!(std::cin >> choix)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Saisie invalide. Veuillez saisir 1 ou 2.\n";
                std::cout << "Votre choix : ";
            }
            else if (choix != 1 && choix != 2) {
                std::cout << "Veuillez choisir 1 ou 2.\n";
                std::cout << "Votre choix : ";
            }
            else {
                break;
            }
        }

        // Si le joueur souhaite defausser un Domaine
        if (choix == 1) {
            std::size_t indiceChoisi = 0;
            // Afficher les Domaines disponibles
            if (indicesDomaines.size() > 1) {
                std::cout << "\nQuel Domaine voulez-vous defausser ?\n";
                for (std::size_t i = 0; i < indicesDomaines.size(); i++) {
                    std::cout << i + 1 << ". Domaine\n";
                }

                std::cout << "Votre choix : ";

                while (true) {

                    if (!(std::cin >> indiceChoisi)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Saisie invalide. Reessayez : ";
                    }
                    else if (indiceChoisi < 1 ||indiceChoisi > indicesDomaines.size()) {
                        std::cout << "Choix invalide. Reessayez : ";
                    }
                    else {
                        break;
                    }
                }

                // Recuperer l'indice reel dans la main
                indiceChoisi = indicesDomaines[indiceChoisi - 1];
            }
            else {
                // Un seul Domaine : pas besoin de demander
                indiceChoisi = indicesDomaines[0];
            }

            // Defausser le Domaine choisi
            joueurActuel.defausserUneCarte(indiceChoisi);

            // Ajouter 4 pieces
            joueurActuel.ajouterArgent(4);

            std::cout << "\nVous avez defausse votre Domaine.\n";
            std::cout << "Vous obtenez +4 pieces !\n";

            return;
        }
    }

    // Si le joueur refuse ou ne possede aucun Domaine, il recoit un Domaine depuis le plateau.
    if (plateau.contientCarte("Domaine")) {
        if (plateau.acheterCarte("Domaine")) {
            std::unique_ptr<Carte> domaine = plateau.creerCarte("Domaine");
            joueurActuel.ajouterCarte(std::move(domaine));
            std::cout << "\nVous recevez une carte Domaine !\n";
        }
    }
    else {
        std::cout << "\nIl ne reste plus de Domaine sur le plateau.\n";
    }
}

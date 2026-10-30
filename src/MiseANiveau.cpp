#include <iostream>
#include "MiseANiveau.hpp"

#include "Plateau.hpp"
#include "Joueur.hpp"

// constructeur 
MiseANiveau::MiseANiveau() : ActionPlateau("MiseANiveau", "Action", 5){}; 

// destructeur 
MiseANiveau::~MiseANiveau(){}; 

// méthode d'affichage 
void MiseANiveau::afficher() const {
    std::cout << "Mise à niveau - Cout : " << getCout() << "\n"
              << "Type de carte : Action \n" 
              << "Description : +1 carte, +1 action, écartez une carte de vitre main et recevze une carte coûtant exactement une pièce de plus" << std::endl;
}


// jouer la carte 
void MiseANiveau::jouer(Joueur& joueur) {

    std::cout << "\n========================================\n";
    std::cout << "       CARTE : MISE A NIVEAU\n";
    std::cout << "========================================\n";
    std::cout << "+1 carte, +1 action, écartez une carte de vitre main et recevze une carte coûtant exactement une pièce de plus\n\n"; 

    std::vector<std::string> cartesPiochees = joueur.piocherDesCartes(1);

    std::cout << "Vous avez pioche :" << std::endl;

    for (const std::string& nomCarte : cartesPiochees) {
        std::cout << "- " << nomCarte << std::endl;
    }

    // Ajouter 1 actions
    joueur.ajouterActions(1);
}

void MiseANiveau::jouerPlateau(std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) {
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);
    
    if (joueur.getMain().empty()) {
        std::cout << "Vous n'avez aucune carte à écarter." << std::endl;
        return;
    }

    // Afficher la main du joueur.
    joueur.afficherMain();

    // Demander quelle carte écarter.
    std::size_t idxCarte;

    while (true) {
        std::cout << "Quelle carte voulez-vous écarter ? (indice de la carte) : ";

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

    // Récupérer le coût AVANT d'écarter la carte.
    int coutFixe = joueur.getMain()[idxCarte]->getCout() + 1;

    // Écarter la carte choisie.
    joueur.ecarterCarte(static_cast<std::size_t>(idxCarte));

    // Afficher les cartes disponibles dans la limite autorisée.
    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles :\n";
    plateau.afficherCarteCoutEgal(coutFixe, cartesDisponibles);

    // Verifier qu'il existe au moins une carte disponible.
    if (cartesDisponibles.empty()) {
        std::cout << "\nAucune carte disponible.\n";
        return;
    }

    int choix;

    // Demander un numero valide.
    while (true) {
        std::cout << "\nVotre choix (0 pour annuler) : ";

        if (std::cin >> choix) {
            if (choix >= 0 && static_cast<std::size_t>(choix) <= cartesDisponibles.size()) {
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
    const std::string& nomCarte = cartesDisponibles[static_cast<std::size_t>(choix - 1)];

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
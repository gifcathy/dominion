#include <iostream> 
#include "Atelier.hpp"

#include "Joueur.hpp"
#include "Plateau.hpp"
#include "Carte.hpp"

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


void Atelier::jouerPlateau( std::vector<Joueur>& listeJoueurs, int& indiceJoueurActuel, Plateau& plateau) {
    Joueur& joueur = listeJoueurs.at(indiceJoueurActuel);

    std::cout << "\n========================================\n";
    std::cout << "             CARTE : ATELIER\n";
    std::cout << "========================================\n";
    std::cout << "Effet : Gagnez une carte coutant au maximum 4 pieces.\n\n";

    std::vector<std::string> cartesDisponibles;

    std::cout << "Cartes disponibles :\n";
    plateau.afficherCarteCoutInfEgal(4, cartesDisponibles);

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

/*
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
}*/
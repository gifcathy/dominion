#include "Partie.hpp"
#include "InitialisationCartes.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>


    // -----------------------------------------------------------------------
    // -----  ATTENTION les fonction tour() et acheterCarte on des soucie
    // -----------------------------------------------------------------------

Partie::Partie(int nombreJoueurs, const std::vector<std::string>& cartesAction)
                : catalogue(),
                plateau(nombreJoueurs, cartesAction),
                joueurs(),
                joueurActuel(0)
{
    if (nombreJoueurs < 2 || nombreJoueurs > 4) {
        throw std::invalid_argument("Le nombre de joueurs doit etre compris entre 2 et 4.");
    }

    // Enregistrer les fabriques de toutes les cartes concretes
    initialiserCatalogue(catalogue);

    // Creer les joueurs avec leur deck de depart
    for (int i = 0; i < nombreJoueurs; ++i) {
        joueurs.emplace_back(creerDeckInitial());
    }
}

// Cree un deck contenant 7 Cuivres et 3 Domaines
std::vector<std::unique_ptr<Carte>> Partie::creerDeckInitial()
{
    std::vector<std::unique_ptr<Carte>> deck;

    for (int i = 0; i < 7; ++i) {
        deck.push_back(catalogue.creer("Cuivre"));
    }

    for (int i = 0; i < 3; ++i) {
        deck.push_back(catalogue.creer("Domaine"));
    }

    return deck;
}

// Lance la partie
void Partie::commencer()
{
    std::cout << "La partie commence !" << std::endl;

    while (!estTerminee()) {
        tour();
    }

    std::cout << "La partie est terminee !" << std::endl;
}


// Gere le tour du joueur actuel
void Partie::tour()
{
    Joueur& joueur = joueurs[joueurActuel];

    std::cout << "\n--- Tour du joueur "
              << joueurActuel + 1 << " ---\n";

    bool tourEnCours = true;

    while (tourEnCours) {
        //ATTENTION Il faut afficher les carte de la main du joueur
        //ATTENTION A refaire car beaucoup de chose ne vons pas car oublie de carte jouer

        std::cout << "\nArgent : " << joueur.getArgent()
                  << " | Actions : " << joueur.getAction()
                  << " | Achats : " << joueur.getAchat()
                  << std::endl;

        std::cout << "1. Jouer un Tresor\n"
                  << "2. Jouer une Action\n"
                  << "3. Acheter une carte\n"
                  << "4. Terminer le tour\n"
                  << "Choix : ";

        int choix;
        if (!(std::cin >> choix)) {
            if (std::cin.eof()) {
                return;
            }

            std::cin.clear(); //réinitialise l'état d'erreur de la saisie
            std::cin.ignore(10000, '\n'); //élimine les caractères invalides jusqu'à la fin de la ligne
            std::cout << "Saisie invalide.\n";
            continue;
        }

        if (choix == 1) {
            std::size_t indice;
            std::cout << "Indice du Tresor dans votre main : ";
            std::cin >> indice;
            joueur.jouerTresor(indice);
        }
        else if (choix == 2) {
            std::size_t indice;
            std::cout << "Indice de l'Action dans votre main : ";
            std::cin >> indice;
            joueur.jouerAction(indice);
        }
        else if (choix == 3) {
            acheterCarte();
        }
        else if (choix == 4) {
            finTour();
            tourEnCours = false;
        }
        else {
            std::cout << "Choix invalide.\n";
        }
    }
}


// Achete une carte choisie par le joueur actuel
void Partie::acheterCarte()
{
    Joueur& joueur = joueurs[joueurActuel];

    //ATTENTION il faudrait afficher toutes les carte et leur coup

    std::string nom;
    std::cout << "Nom de la carte a acheter : ";
    std::cin >> nom;

    // Verifier que la carte existe dans le catalogue
    if (!catalogue.contient(nom)) {
        std::cout << "Cette carte n'existe pas dans le catalogue.\n";
        return;
    }

    // Verifier qu'il reste des cartes dans la pile
    if (plateau.getNombreCartes(nom) <= 0) {
        std::cout << "Cette pile est vide ou indisponible.\n";
        return;
    }

    // Creer temporairement la carte pour connaitre son cout
    std::unique_ptr<Carte> carte = catalogue.creer(nom);
    int coutCarte = carte->getCout();

    if (joueur.getAchat() <= 0) {
        std::cout << "Vous n'avez plus d'achat disponible.\n";
        return;
    }

    if (joueur.getArgent() < coutCarte) {
        std::cout << "Vous n'avez pas assez d'argent.\n";
        return;
    }

    // Retirer une carte de la pile du plateau
    if (!plateau.acheterCarte(nom)) {
        std::cout << "Impossible d'acheter cette carte.\n";
        return;
    }

    // Payer et consommer un achat
    joueur.depenserArgent(coutCarte);
    joueur.depenserAchat();

    // Ajouter la carte achetee a la defausse du joueur
    joueur.ajouterCarte(std::move(carte));

    std::cout << "Carte achetee : " << nom << std::endl;
}


// Termine le tour et passe au joueur suivant
void Partie::finTour()
{
    joueurs[joueurActuel].terminerTour();

    joueurActuel = (joueurActuel + 1) % static_cast<int>(joueurs.size());
}


// Verifie si la partie est terminee
bool Partie::estTerminee() const
{
    // Premiere condition : la pile de Provinces est vide
    return plateau.getNombreCartes("Province") <= 0;
}

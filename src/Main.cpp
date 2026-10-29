
#include "Partie.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <limits>

// Lit un nombre en evitant de bloquer le programme
int lireChoix(int minimum, int maximum) {
    int choix;

    while (true) {
        std::cout << "Votre choix : ";

        if (std::cin >> choix && choix >= minimum && choix <= maximum) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            return choix;
        }

        std::cout << "Choix invalide. Reessayez.\n";
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
    }
}

// Affiche les cartes disponibles
void afficherCartes(const std::vector<std::string>& cartes) {
    for (std::size_t i = 0; i < cartes.size(); ++i) {
        std::cout << i + 1 << ". " << cartes[i] << '\n';
    }
}

// Choix manuel de 10 cartes Action differentes
std::vector<std::string> choisirCartes(
    const std::vector<std::string>& cartesDisponibles
) {
    std::vector<std::string> cartesChoisies;

    std::cout << "\n=== Choix des cartes Action ===\n";
    std::cout << "Choisissez 10 cartes differentes.\n";

    while (cartesChoisies.size() < 10) {
        std::cout << "\nCartes disponibles :\n";

        for (std::size_t i = 0; i < cartesDisponibles.size(); ++i) {
            bool dejaChoisie = false;

            for (std::size_t j = 0; j < cartesChoisies.size(); ++j) {
                if (cartesChoisies[j] == cartesDisponibles[i]) {
                    dejaChoisie = true;
                    break;
                }
            }

            if (!dejaChoisie) {
                std::cout << i + 1 << ". "
                          << cartesDisponibles[i] << '\n';
            }
        }

        std::cout << "Cartes choisies : "
                  << cartesChoisies.size() << "/10\n";

        int choix = lireChoix(
            1, static_cast<int>(cartesDisponibles.size())
        );

        const std::string& carte = cartesDisponibles[choix - 1];
        bool dejaChoisie = false;

        for (std::size_t i = 0; i < cartesChoisies.size(); ++i) {
            if (cartesChoisies[i] == carte) {
                dejaChoisie = true;
                break;
            }
        }

        if (dejaChoisie) {
            std::cout << "Cette carte est deja choisie.\n";
        } else {
            cartesChoisies.push_back(carte);
            std::cout << carte << " ajoutee !\n";
        }
    }

    return cartesChoisies;
}

// Selection d'un paquet predefini
std::vector<std::string> choisirPaquet() {

    std::vector<std::string> paquetDebutant;
    paquetDebutant.push_back("Atelier");
    paquetDebutant.push_back("Bucheron");
    paquetDebutant.push_back("Village");
    paquetDebutant.push_back("Douves");
    paquetDebutant.push_back("Milice");
    paquetDebutant.push_back("Renovation");
    paquetDebutant.push_back("Cave");
    paquetDebutant.push_back("Mine");
    paquetDebutant.push_back("Forgeron");
    paquetDebutant.push_back("Marche");

    std::vector<std::string> paquetRichesse;
    paquetRichesse.push_back("Aventurier");
    paquetRichesse.push_back("Bureaucrate");
    paquetRichesse.push_back("Chancelier");
    paquetRichesse.push_back("Chapelle");
    paquetRichesse.push_back("Festin");
    paquetRichesse.push_back("Laboratoire");
    paquetRichesse.push_back("Marche");
    paquetRichesse.push_back("Mine");
    paquetRichesse.push_back("PreteurSurGages");
    paquetRichesse.push_back("SalleDuTrone");

    std::vector<std::string> paquetInteraction;
    paquetInteraction.push_back("Bibliotheque");
    paquetInteraction.push_back("Bureaucrate");
    paquetInteraction.push_back("ChambreDuConseil");
    paquetInteraction.push_back("Chancelier");
    paquetInteraction.push_back("Douves");
    paquetInteraction.push_back("Espion");
    paquetInteraction.push_back("Festival");
    paquetInteraction.push_back("Milice");
    paquetInteraction.push_back("Village");
    paquetInteraction.push_back("Voleur");

    std::vector<std::string> paquetChangementTaille;
    paquetChangementTaille.push_back("Atelier");
    paquetChangementTaille.push_back("Bucheron");
    paquetChangementTaille.push_back("Cave");
    paquetChangementTaille.push_back("Chapelle");
    paquetChangementTaille.push_back("Festin");
    paquetChangementTaille.push_back("Jardin");
    paquetChangementTaille.push_back("Laboratoire");
    paquetChangementTaille.push_back("Sorciere");
    paquetChangementTaille.push_back("Village");
    paquetChangementTaille.push_back("Voleur");

    std::vector<std::string> paquetPlaceDuVillage;
    paquetPlaceDuVillage.push_back("Bibliotheque");
    paquetPlaceDuVillage.push_back("Bucheron");
    paquetPlaceDuVillage.push_back("Bureaucrate");
    paquetPlaceDuVillage.push_back("Cave");
    paquetPlaceDuVillage.push_back("Festival");
    paquetPlaceDuVillage.push_back("Forgeron");
    paquetPlaceDuVillage.push_back("Marche");
    paquetPlaceDuVillage.push_back("Renovation");
    paquetPlaceDuVillage.push_back("SalleDuTrone");
    paquetPlaceDuVillage.push_back("Village");

    std::cout << "\n=== Paquets predefinis ===\n";
    std::cout << "1. Debutant\n";
    std::cout << "2. Richesses et trésor\n";
    std::cout << "3. Interaction\n";
    std::cout << "4. Changement de taille\n";
    std::cout << "5. Place du village\n";

    int choix = lireChoix(1, 5);

    switch (choix) {
        case 1 :
            return paquetDebutant;
        case 2 :
            return paquetRichesse;
        case 3 :
            return paquetInteraction;
        case 4 :
            return paquetChangementTaille;
        case 5 :
            return paquetPlaceDuVillage;
    }

    return paquetDebutant;
}

int main() {
    try {
        std::cout << "============================\n";
        std::cout << "       DOMINION\n";
        std::cout << "============================\n";

        // 1. Nombre de joueurs
        std::cout << "\nCombien de joueurs ?\n";
        std::cout << "2. Deux joueurs\n";
        std::cout << "3. Trois joueurs\n";
        std::cout << "4. Quatre joueurs\n";

        int nombreJoueurs = lireChoix(2, 4);

        // Cartes disponibles dans le projet
        std::vector<std::string> cartesDisponibles;
        cartesDisponibles.push_back("Atelier");
        cartesDisponibles.push_back("Aventurier");
        cartesDisponibles.push_back("Bibliotheque");
        cartesDisponibles.push_back("Bucheron");
        cartesDisponibles.push_back("Bureaucrate");
        cartesDisponibles.push_back("Cave");
        cartesDisponibles.push_back("ChambreDuConseil");
        cartesDisponibles.push_back("Chancelier");
        cartesDisponibles.push_back("Chapelle");
        cartesDisponibles.push_back("Douves");
        cartesDisponibles.push_back("Espion");
        cartesDisponibles.push_back("Festin");
        cartesDisponibles.push_back("Festival");
        cartesDisponibles.push_back("Forgeron");
        cartesDisponibles.push_back("Jardin");
        cartesDisponibles.push_back("Laboratoire");
        cartesDisponibles.push_back("Marche");
        cartesDisponibles.push_back("Mine");
        cartesDisponibles.push_back("PreteurSurGages");
        cartesDisponibles.push_back("Renovation");
        cartesDisponibles.push_back("Sorciere");
        cartesDisponibles.push_back("Village");
        cartesDisponibles.push_back("Voleur");

        // 2. Mode de choix des cartes
        std::cout << "\nComment voulez-vous choisir les cartes ?\n";
        std::cout << "1. Choisir les cartes manuellement\n";
        std::cout << "2. Utiliser un paquet predefini\n";

        int mode = lireChoix(1, 2);

        std::vector<std::string> cartesAction;

        if (mode == 1) {
            cartesAction = choisirCartes(cartesDisponibles);
        } else {
            cartesAction = choisirPaquet();
        }

        // 3. Recapitulatif
        std::cout << "\n=== Recapitulatif de la partie ===\n";
        std::cout << "Nombre de joueurs : " << nombreJoueurs << '\n';
        std::cout << "Cartes Action :\n";
        afficherCartes(cartesAction);

        // 4. Creation et lancement de la partie
        Partie partie(nombreJoueurs, cartesAction);
        partie.commencer();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}



/*
#include "Partie.hpp"

#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        int nombreJoueurs = 2;

        // Cartes Action choisies pour cette partie
        std::vector<std::string> cartesAction;/
        cartesAction.push_back("Atelier");
        cartesAction.push_back("Bucheron");
        cartesAction.push_back("Village");
        cartesAction.push_back("Chapelle");
        cartesAction.push_back("Festin");
        cartesAction.push_back("Laboratoire");/
        cartesAction.push_back("Sorciere");
        cartesAction.push_back("Douves");
        cartesAction.push_back("Cave");
        cartesAction.push_back("CDC");
        cartesAction.push_back("Chancelier");
        cartesAction.push_back("Festival");
        cartesAction.push_back("Forgeron");
        cartesAction.push_back("Marche");
        cartesAction.push_back("Mine");
        cartesAction.push_back("PSG");
        cartesAction.push_back("Renovation");
        cartesAction.push_back("Voleur");

        // Creation de la partie
        Partie partie(nombreJoueurs, cartesAction);

        // Lancement de la partie
        partie.commencer();
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
*/
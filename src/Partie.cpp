#include "Partie.hpp"
#include "InitialisationCartes.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>


    // -----------------------------------------------------------------------
    // -----  ATTENTION les fonction tour() et acheterCarte on des soucie
    // -----------------------------------------------------------------------

//fonction static qui creer et initialise le cataloque qui est avant la creation de partie
static CatalogueCartes creerCatalogueInitialise(){
    CatalogueCartes catalogue;
    initialiserCatalogue(catalogue);
    return catalogue;
}

Partie::Partie(int nombreJoueurs, const std::vector<std::string>& cartesAction)
                : catalogue(creerCatalogueInitialise()),
                plateau(nombreJoueurs, cartesAction, catalogue),
                joueurs(),
                joueurActuel(0)
{
    if (nombreJoueurs < 2 || nombreJoueurs > 4) {
        throw std::invalid_argument(
            "Le nombre de joueurs doit etre compris entre 2 et 4."
        );
    }

    // Creer les joueurs avec leur deck de depart
    for (int i = 0; i < nombreJoueurs; ++i) {
        joueurs.emplace_back(creerDeckInitial());
    }
}

// Cree un deck contenant 7 Cuivres et 3 Domaines
std::vector<std::unique_ptr<Carte>> Partie::creerDeckInitial(){
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
void Partie::commencer(){
    std::cout << "--------------------" << std::endl;
    std::cout << "La partie commence !" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "" << std::endl;

    while (!estTerminee()) {
        tour();
    }

    std::cout << "La partie est terminee !" << std::endl;
}

// Gere le tour du joueur actuel
void Partie::tour(){
    Joueur& joueur = joueurs[joueurActuel];

    std::cout << "\n--- Tour du joueur " << joueurActuel + 1 << " ---\n";

    bool tourEnCours = true;

    while (tourEnCours) {
        /////-------- ATTENTION A refaire car beaucoup de chose ne vons pas car oublie de carte jouer
        ///// ---- AFFICHER LES PILES DES DIFFERENTES CARTE (le plateau)
        std::cout << "\nLe plateau : ";
        plateau.afficher();
        
        std::cout << "\nVotre main : ";
        for (std::size_t i = 0; i < joueur.getMain().size(); i++) {
            std::cout << "[" << i << "] " << joueur.getMain()[i]->getNom() << " | ";
        }
        std::cout << std::endl;

        std::cout << "\nArgent : " << joueur.getArgent()
                  << " | Actions : " << joueur.getAction()
                  << " | Achats : " << joueur.getAchat()
                  << std::endl;

                  //peut etre plutot demander si il veut jouer une action puis si il veut acheter une carte 
                  //car la sinon il peut d'abord acheter puis jouer une action alos que c pas se qu'on doit pouvoir faire
        std::cout << "1. Jouer une Action\n"
                  << "2. Acheter une carte\n" // jouer un ou plusieur tresor
                  << "3. Terminer le tour\n"
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

        switch (choix){ // ----ATTENTION voir si on ajoute le fait que la personne puisse annuler ce quel viens de faire (pas sur)
        case 1 : 
            //----ATTENTION verifier que c'est bien une carte action
            //----Placer la carte dans le vecteur carteJouer du joueur
            std::size_t indice;
            std::cout << "Indice de l'Action dans votre main : ";
            std::cin >> indice;

            if (indice >= joueur.getMain().size()) {
                std::cout << "Indice invalide.\n";
                break;
            }
            const std::unique_ptr<Carte>& carte = joueur.getCarte(indice);

            if (carte->getType() == "Attaque") {
                // ...
            }

            joueur.jouerAction(indice);
            //---verifier si on joue une carte attaque 
            //--- si oui regader quelle est elle et faire sont attauqe sur les autre joueur 
            break;
        
        case 2 :
            //----demander au joueur de selectionner les carte tresor qu'il veut utiliser pour acheter une carte
            //----les tresor seront placer dans le vecteur carteJouer du joueur
            //---- selectionne tout les tresor 
            jouerToutTresor(joueur);
            acheterCarte();
            break;
        case 3 :
            finTour();
            tourEnCours = false;
            break;
        default:
            std::cout << "Choix invalide.\n";
            break;
        }
    }
}

void Partie::jouerToutTresor(Joueur& joueur)
{
    for (int i = static_cast<int>(joueur.getMain().size()) - 1; i >= 0; --i) {
        if (joueur.getMain()[i]->getType() == "Tresor")
        {
            joueur.jouerTresor(static_cast<std::size_t>(i));
        }
    }
}

// Achete une carte choisie par le joueur actuel
void Partie::acheterCarte(){
    Joueur& joueur = joueurs[joueurActuel];

    // Afficher les cartes disponibles à l'achat
    plateau.afficherCartePourAchat();

    std::string nom;
    std::cout << "Nom de la carte a acheter : ";
    std::cin >> nom;

    // 1. Vérifier que la carte existe et que sa pile n'est pas vide
    if (!plateau.contientCarte(nom)) {
        std::cout << "Cette carte est inconnue ou indisponible.\n";
        return;
    }

    // 2. Vérifier que le joueur possède encore un achat
    if (joueur.getAchat() <= 0) {
        std::cout << "Vous n'avez plus d'achat disponible.\n";
        return;
    }

    // 3. Récupérer le coût de la carte
    int coutCarte = plateau.getCoutCarte(nom);

    // 4. Vérifier que le joueur possède assez d'argent
    if (joueur.getArgent() < coutCarte) {
        std::cout << "Vous n'avez pas assez d'argent.\n";
        return;
    }

    // 5. Retirer une carte de la pile du plateau
    if (!plateau.acheterCarte(nom)) {
        std::cout << "Impossible d'acheter cette carte.\n";
        return;
    }

    // 6. Payer et consommer un achat
    joueur.depenserArgent(coutCarte);
    joueur.depenserAchat();

    // 7. Créer la carte achetée et l'ajouter à la défausse
    std::unique_ptr<Carte> carte = catalogue.creer(nom);
    joueur.ajouterCarte(std::move(carte));

    std::cout << "Carte achetee : " << nom << std::endl;
}


// Termine le tour et passe au joueur suivant
void Partie::finTour(){
    joueurs[joueurActuel].terminerTour();

    joueurActuel = (joueurActuel + 1) % static_cast<int>(joueurs.size());
}


// Verifie si la partie est terminee
bool Partie::estTerminee() const{
    // Premiere condition : la pile de Provinces est vide
    return plateau.getNombreCartes("Province") <= 0;
}

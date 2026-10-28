#include "Partie.hpp"
#include "InitialisationCartes.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>



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


void Partie::commencer()
{
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "                                            \n";
    std::cout << "          BIENVENUE DANS DOMINION            \n";
    std::cout << "                                            \n";
    std::cout << "============================================\n";
    std::cout << "\nLa partie commence ! Bonne chance a tous !\n";

    while (!estTerminee()) {
        tour();
    }

    // Calculer les points de chaque joueur.
    std::vector<std::pair<int, int>> classement;

    for (std::size_t i = 0; i < joueurs.size(); ++i) {
        int points = joueurs[i].calculerPointsVictoire();
        classement.push_back(std::make_pair(static_cast<int>(i), points));
    }

    // Trier les joueurs du meilleur score au moins bon.
    std::sort(classement.begin(), classement.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second > b.second;
        }
    );

    std::cout << "\n\n";
    std::cout << "============================================\n";
    std::cout << "                                            \n";
    std::cout << "               FIN DE PARTIE                \n";
    std::cout << "                                            \n";
    std::cout << "============================================\n";

    std::cout << "\n";
    std::cout << "           RESULTATS FINAUX                 \n";
    std::cout << "--------------------------------------------\n";

    // Afficher le classement.
    for (std::size_t i = 0; i < classement.size(); ++i) {
        int numeroJoueur = classement[i].first + 1;
        int points = classement[i].second;

        if (i == 0) {
            std::cout << "  [1er] ";
        }
        else if (i == 1) {
            std::cout << "  [2e]  ";
        }
        else if (i == 2) {
            std::cout << "  [3e]  ";
        }
        else {
            std::cout << "  [" << i + 1 << "e]  ";
        }

        std::cout << "Joueur " << numeroJoueur << " : " << points << " points\n";
    }

    std::cout << "--------------------------------------------\n";

    // Verifier s'il y a une egalite en premiere place.
    if (classement.size() > 1 && classement[0].second == classement[1].second) {
        std::cout << "\n";
        std::cout << "============================================\n";
        std::cout << "               EGALITE !                    \n";
        std::cout << "============================================\n";
        std::cout << "Plusieurs joueurs ont " << classement[0].second << " points !\n";
    }
    else if (!classement.empty()) {
        std::cout << "\n";
        std::cout << "============================================\n";
        std::cout << "             VICTOIRE !                     \n";
        std::cout << "============================================\n";
        std::cout << " FELICITATIONS AU JOUEUR " << classement[0].first + 1 << " !\n";
        std::cout << " Avec " << classement[0].second << " points de victoire !\n";
        std::cout << "============================================\n";
    }

    std::cout << "\nMerci d'avoir joue a Dominion !\n";
    std::cout << "A bientot pour une nouvelle partie !\n\n";
}



void Partie::tour()
{
    Joueur& joueur = joueurs[joueurActuel];

    // Couleurs du terminal
    const std::string RESET = "\033[0m";
    const std::string BLEU = "\033[36m";
    const std::string VERT = "\033[32m";
    const std::string JAUNE = "\033[33m";
    const std::string ROUGE = "\033[31m";
    const std::string MAGENTA = "\033[1;35m";

    ///--------
    // Afficher un titre ------ATTENTION VOIR POUR LA SORTIR DE LA FONCTION TOUR
    auto afficherTitre = [&](const std::string& titre) {
        std::cout << "\n" << BLEU
                  << "========================================\n"
                  << "  " << titre << "\n"
                  << "========================================"
                  << RESET << "\n";
    };

    // Demander un nombre valide compris entre min et max.
    // Retourne false si l'entree est fermee (EOF).
    auto demanderChoix = [&](int& choix, int min, int max) -> bool {
        while (true) {
            std::cout << JAUNE << "Votre choix : " << RESET;

            if (std::cin >> choix) {
                if (choix >= min && choix <= max) {
                    return true;
                }

                std::cout << ROUGE
                          << "Choix invalide. Entrez un nombre entre "
                          << min << " et " << max << ".\n"
                          << RESET;
            }
            else {
                if (std::cin.eof()) {
                    return false;
                }

                std::cin.clear();
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

                std::cout << ROUGE << "Saisie invalide. Entrez un nombre.\n" << RESET;
            }
        }
    };

    // ==================================================
    // AFFICHAGE DU PLATEAU
    // ==================================================

    afficherTitre("DOMINION - PLATEAU");
    std::cout << "\n" << MAGENTA;
    plateau.afficher();
    std::cout << RESET << "\n";

    // ==================================================
    // DEBUT DU TOUR
    // ==================================================

    afficherTitre("TOUR DU JOUEUR " + std::to_string(joueurActuel + 1));

    std::cout << "Actions : " << joueur.getAction()
              << " | Achats : " << joueur.getAchat()
              << " | Argent : " << joueur.getArgent()
              << " pieces\n";

    // ==================================================
    // PHASE 1 : ACTION
    // ==================================================

    bool phaseAction = true;

    while (phaseAction) {
        // Verifier les actions disponibles
        if (joueur.getAction() <= 0) {
            std::cout << JAUNE << "\nVous n'avez plus d'action disponible.\n" << RESET;
            break;
        }

        // Rechercher les cartes Action en main
        bool possedeAction = false;

        for (std::size_t i = 0; i < joueur.getMain().size(); ++i) {
            std::string type = joueur.getMain()[i]->getType();

            if (type == "Action" || type == "Action-Réaction" || type == "ActionPlateau" || type == "Action-Attaque") {
                possedeAction = true;
                break;
            }
        }

        if (!possedeAction) {
            std::cout << JAUNE << "\nVous n'avez aucune carte Action en main.\n" << RESET;
            break;
        }

        afficherTitre("PHASE D'ACTION");

        joueur.afficherMain();

        std::cout << "\nActions disponibles : " << joueur.getAction()
                  << "\nArgent actuel : " << joueur.getArgent()
                  << " pieces\n\n";

        std::cout << "1. Jouer une carte Action\n"
                  << "2. Passer a la phase d'achat\n";

        int choix;

        if (!demanderChoix(choix, 1, 2)) {
            return;
        }

        switch (choix) {
            case 1:
            {
                // Afficher les cartes Action avec leur indice
                std::cout << "\nCartes Action jouables :\n";

                for (std::size_t i = 0; i < joueur.getMain().size(); ++i) {
                    Carte* carte = joueur.getMain()[i].get();
                    std::string type = carte->getType();

                    if (type == "Action" || type == "Action-Réaction" || type == "ActionPlateau" || type == "Action-Attaque") {
                        std::cout << "  [" << i << "] " << carte->getNom() << "\n";
                    }
                }

                std::cout << "  [" << joueur.getMain().size() << "] Annuler\n";

                int indice;

                if (!demanderChoix( indice, 0, static_cast<int>(joueur.getMain().size()) )) {
                    return;
                }

                // L'indice correspondant a Annuler
                if (static_cast<std::size_t>(indice) == joueur.getMain().size()) {
                    break;
                }

                // Verifier que la carte choisie est une Action
                Carte* carte = joueur.getMain()[indice].get();
                std::string type = carte->getType();

                if (type != "Action" && type != "Action-Réaction" && type != "ActionPlateau" && type != "Action-Attaque") {
                    std::cout << ROUGE << "Cette carte n'est pas une Action.\n" << RESET;
                    break;
                }

                std::cout << VERT << "\nVous jouez : " << carte->getNom() << "\n" << RESET;

                // Conserver le pointeur vers l'objet carte
                // avant de deplacer la carte hors de la main.
                ActionPlateau* actionP = dynamic_cast<ActionPlateau*>(carte);

                joueur.jouerAction(static_cast<std::size_t>(indice));

                // Appliquer l'effet concernant le plateau
                // ou les autres joueurs, si necessaire.
                if (actionP != nullptr) {
                    actionP->jouerPlateau(joueurs, joueurActuel, plateau);
                }

                break;
            }

            case 2:
                phaseAction = false;
                break;
        }
    }

    // ==================================================
    // PHASE 2 : ACHAT
    // ==================================================

    bool phaseAchat = true;

    while (phaseAchat) {
        jouerToutTresor(joueur);
        if (joueur.getAchat() <= 0) {
            std::cout << JAUNE << "\nVous n'avez plus d'achat disponible.\n" << RESET;
            break;
        }

        afficherTitre("PHASE D'ACHAT");

        joueur.afficherMain();

        std::cout << "Argent disponible : " << VERT << joueur.getArgent() << " pieces" << RESET << "\n";

        std::cout << "Achats disponibles : " << joueur.getAchat() << "\n\n";

        std::cout << "1. Acheter une carte\n"
                  << "2. Terminer le tour\n";

        int choix;

        if (!demanderChoix(choix, 1, 2)) {
            return;
        }

        switch (choix) {
            case 1:
                acheterCarte();
                break;

            case 2:
                phaseAchat = false;
                break;
        }
    }

    // ==================================================
    // PHASE 3 : FIN DU TOUR
    // ==================================================

    afficherTitre("FIN DU TOUR");

    std::cout << VERT << "Fin du tour du joueur " << joueurActuel + 1 << ".\n" << RESET;

    // Laisser le temps au joueur de voir le resultat
    std::cout << "\nAppuyez sur Entree pour passer l'ordinateur au joueur suivant...";

    // Attendre que le joueur appuie sur Entree
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    std::cin.get();

    // Passer au joueur suivant
    finTour();

    // Ecran de transition avant le prochain joueur
    std::cout << "\n\n\n";
    std::cout << "========================================\n";
    std::cout << "       Passez l'ordinateur !\n";
    std::cout << "========================================\n";
    std::cout << "Le joueur " << joueurActuel + 1 << " peut maintenant jouer.\n";
    std::cout << "\nAppuyez sur Entree pour continuer...";

    // Attendre que le joueur suivant soit pret
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    std::cin.get();
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



void Partie::acheterCarte()
{
    Joueur& joueur = joueurs[joueurActuel];

    // Verifier que le joueur peut encore acheter.
    if (joueur.getAchat() <= 0) {
        std::cout << "\nVous n'avez plus d'achat disponible.\n";
        return;
    }

    // Afficher les informations du joueur.
    std::cout << "\n========================================\n";
    std::cout << "             MENU D'ACHAT\n";
    std::cout << "========================================\n";
    std::cout << "Argent disponible : " << joueur.getArgent() << " pieces\n";
    std::cout << "Achats disponibles : " << joueur.getAchat() << "\n";
    std::cout << "----------------------------------------\n";

    // Afficher les cartes que le joueur peut acheter.
    std::vector<std::string> cartesAchetable;

    std::cout << "\nCartes que vous pouvez acheter :\n\n";

    plateau.afficherCarteCoutInfEgal(joueur.getArgent(), cartesAchetable);

    // Verifier qu'il existe des cartes achetables.
    if (cartesAchetable.empty()) {
        std::cout << "\nAucune carte disponible avec votre argent.\n";
        std::cout << "Vous pouvez terminer votre tour.\n";
        return;
    }

    std::cout << "\n[0] Annuler l'achat\n";

    // Demander un choix valide.
    int choix;

    while (true) {
        std::cout << "\nVotre choix : ";

        if (std::cin >> choix) {
            if (choix >= 0 && static_cast<std::size_t>(choix) <= cartesAchetable.size()) {
                break;
            }

            std::cout << "Choix invalide. Choisissez un numero de 0 a " << cartesAchetable.size() << ".\n";
        }
        else {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );

            std::cout << "Saisie invalide. Entrez un nombre.\n";
        }
    }

    // Gerer l'annulation.
    if (choix == 0)
    {
        std::cout << "Achat annule.\n";
        return;
    }

    // Recuperer le nom de la carte selectionnee.
    const std::string& nom = cartesAchetable[static_cast<std::size_t>(choix - 1)];

    int coutCarte = plateau.getCoutCarte(nom);

    // Acheter la carte sur le plateau.
    if (!plateau.acheterCarte(nom)) {
        std::cout << "Impossible d'acheter cette carte.\n";
        return;
    }

    // Payer et consommer un achat.
    joueur.depenserArgent(coutCarte);
    joueur.depenserAchat();

    // Creer la carte et l'ajouter a la defausse.
    std::unique_ptr<Carte> carte = catalogue.creer(nom);
    joueur.ajouterCarte(std::move(carte));

    std::cout << "\n[SUCCES] Carte achetee : " << nom << " !\n";
    std::cout << "Argent restant : " << joueur.getArgent() << " pieces\n";
    std::cout << "Achats restants : " << joueur.getAchat() << "\n";
}



// Termine le tour et passe au joueur suivant
void Partie::finTour(){
    joueurs[joueurActuel].terminerTour();

    joueurActuel = (joueurActuel + 1) % static_cast<int>(joueurs.size());
}


// Verifie si la partie est terminee
bool Partie::estTerminee() const {
    // Premiere condition : la pile de Provinces est vide
    if (plateau.getNombreCartes("Province") <= 0) {
        return true;
    }

    // Deuxieme condition : au moins 3 piles sont vides
    int pilesVides = 0;

    // Parcourir toutes les piles du plateau
    for (const auto& pile : plateau.getPiles()) {
        if (pile.second <= 0) {
            pilesVides++;
        }
    }

    return pilesVides >= 3;
}





/*
void Partie::tour()
{
    Joueur& joueur = joueurs[joueurActuel];

    std::cout << "\n==================================";
    std::cout << "\n========== Le plateau : ==========";
    std::cout << "\n==================================";
    plateau.afficher();

    std::cout << "\n==================================";
    std::cout << "\n======== Tour du joueur " << joueurActuel + 1 << " ========";
    std::cout << "\n==================================" << std::endl;
    //joueur.afficherMain();

    // ==================================================
    // PHASE 1 : ACTION
    // ==================================================

    bool phaseAction = true;

    joueur.afficherMain();
    
    while (phaseAction)
    {
        

        // Vérifier si le joueur possède encore une action.
        if (joueur.getAction() <= 0)
        {
            std::cout << "\nVous n'avez plus d'action disponible.\n";
            break;
        }

        // Vérifier si le joueur possède une carte Action en main.
        bool possedeAction = false;

        for (std::size_t i = 0; i < joueur.getMain().size(); i++)
        {
            std::string type = joueur.getMain()[i]->getType();

            if (type == "Action" ||
                type == "Action-Réaction" ||
                type == "ActionPlateau" ||
                type == "Action-Attaque")
            {
                possedeAction = true;
                break;
            }
        }

        if (!possedeAction)
        {
            std::cout << "\nVous n'avez aucune carte Action en main.\n";
            break;
        }

        // Afficher le plateau et la main du joueur.
        std::cout << "\n========== PHASE ACTION ==========\n";

        std::cout << "\n--- Tour du joueur " << joueurActuel + 1 << " ---\n";
        joueur.afficherMain();

        std::cout << "\nActions disponibles : " << joueur.getAction()
                  << "\nArgent : " << joueur.getArgent()
                  << "\nAchats : " << joueur.getAchat()
                  << "\n";

        std::cout << "\n1. Jouer une carte Action\n"
                  << "2. Passer a la phase Achat\n"
                  << "Choix : ";

        int choix;

        if (!(std::cin >> choix))
        {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide.\n";
            continue;
        }

        switch (choix)
        {
            case 1:
            {
                std::size_t indice;

                std::cout << "Indice de la carte Action : ";

                if (!(std::cin >> indice))
                {
                    if (std::cin.eof())
                        return;

                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Saisie invalide.\n";
                    break;
                }

                if (indice >= joueur.getMain().size())
                {
                    std::cout << "Indice invalide.\n";
                    break;
                }

                // Vérifier que la carte est bien une Action.
                Carte* carte = joueur.getMain()[indice].get();

                std::string type = carte->getType();

                if (type != "Action" &&
                    type != "Action-Réaction" &&
                    type != "ActionPlateau" &&
                    type != "Action-Attaque")
                {
                    std::cout << "Cette carte n'est pas une Action.\n";
                    break;
                }

                // Jouer la carte.
                // Cette fonction doit retirer une action disponible,
                // déplacer la carte et appliquer son effet personnel.
                ActionPlateau* actionP = dynamic_cast<ActionPlateau*>(carte);

                joueur.jouerAction(indice);

                // Appliquer ensuite l'effet nécessitant le plateau
                // ou les autres joueurs, si la carte en possède un.
                if (actionP != nullptr)
                {
                    actionP->jouerPlateau(joueurs, joueurActuel, plateau);
                }

                break;
            }

            case 2:
                // On ne revient plus à la phase Action.
                phaseAction = false;
                break;

            default:
                std::cout << "Choix invalide.\n";
                break;
        }
    }

    // ==================================================
    // PHASE 2 : ACHAT
    // ==================================================

    //--peut etre reaficher
    //--std::cout << "\nLe plateau : ";
    //--plateau.afficher();

    bool phaseAchat = true;

    while (phaseAchat)
    {
        if (joueur.getAchat() <= 0){
            std::cout << "\nVous n'avez plus d'achat disponible.\n";
            break;
        }
        //--voir si on ne verrifierai pas si il a une carte tresor dans la mains ou si il a de l'argent en main

        std::cout << "\n========== PHASE ACHAT ==========\n";

        std::cout << "\n--- Tour du joueur " << joueurActuel + 1 << " ---\n";
        joueur.afficherMain();

        std::cout << "\nArgent : " << joueur.getArgent()
                  << "\nAchats disponibles : " << joueur.getAchat()
                  << "\n";

        std::cout << "\n1. Jouer ses tresors\n"
                  << "2. Acheter une carte\n"
                  << "3. Terminer le tour\n"
                  << "Choix : ";

        int choix;

        if (!(std::cin >> choix))
        {
            if (std::cin.eof())
                return;

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide.\n";
            continue;
        }

        switch (choix)
        {
            case 1:
                // Jouer les trésors présents dans la main.
                jouerToutTresor(joueur);
                break;

            case 2:
                // Acheter une carte si les conditions le permettent.
                acheterCarte();
                break;

            case 3:
                phaseAchat = false;
                break;

            default:
                std::cout << "Choix invalide.\n";
                break;
        }
    }

    // ==================================================
    // PHASE 3 : FIN DU TOUR
    // ==================================================

    std::cout << "\nFin du tour.\n";

    finTour();
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


















void Partie::acheterCarte()
{
    Joueur& joueur = joueurs[joueurActuel];

    // 1. Verifier que le joueur peut encore acheter
    if (joueur.getAchat() <= 0)
    {
        std::cout << "\nVous n'avez plus d'achat disponible.\n";
        return;
    }

    // 2. Recuperer les cartes disponibles et abordables
    std::vector<std::string> cartesAchetable;

    for (const auto& pile : plateau.getPiles())
    {
        const std::string& nom = pile.first;
        int nombreRestant = pile.second;
        int coutCarte = plateau.getCoutCarte(nom);

        if (nombreRestant > 0 && coutCarte <= joueur.getArgent())
        {
            cartesAchetable.push_back(nom);
        }
    }

    // 3. Afficher les informations du joueur
    std::cout << "\n========================================\n";
    std::cout << "             MENU D'ACHAT\n";
    std::cout << "========================================\n";

    std::cout << "Argent disponible : "
              << joueur.getArgent() << " pieces\n";

    std::cout << "Achats disponibles : "
              << joueur.getAchat() << "\n";

    std::cout << "----------------------------------------\n";

    // 4. Verifier qu'il existe des cartes achetables
    if (cartesAchetable.empty())
    {
        std::cout << "\nAucune carte disponible avec votre argent.\n";
        std::cout << "Vous pouvez terminer votre tour.\n";
        return;
    }

    // 5. Afficher le menu numerote
    std::cout << "\nCartes que vous pouvez acheter :\n\n";

    for (std::size_t i = 0; i < cartesAchetable.size(); ++i)
    {
        const std::string& nom = cartesAchetable[i];

        std::cout << "[" << i + 1 << "] "
                  << nom
                  << " | Cout : " << plateau.getCoutCarte(nom)
                  << " pieces"
                  << " | Restantes : "
                  << plateau.getNombreCartes(nom)
                  << "\n";
    }

    std::cout << "\n[0] Annuler l'achat\n";

    // 6. Demander un choix valide
    int choix;

    while (true)
    {
        std::cout << "\nVotre choix : ";

        if (std::cin >> choix)
        {
            if (choix >= 0 &&
                static_cast<std::size_t>(choix) <= cartesAchetable.size())
            {
                break;
            }

            std::cout << "Choix invalide. Choisissez un numero de 0 a "
                      << cartesAchetable.size() << ".\n";
        }
        else
        {
            if (std::cin.eof())
            {
                return;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Saisie invalide. Entrez un nombre.\n";
        }
    }

    // 7. Gerer l'annulation
    if (choix == 0)
    {
        std::cout << "Achat annule.\n";
        return;
    }

    // 8. Recuperer le nom de la carte selectionnee
    const std::string& nom = cartesAchetable[
        static_cast<std::size_t>(choix - 1)
    ];

    int coutCarte = plateau.getCoutCarte(nom);

    // 9. Acheter la carte sur le plateau
    if (!plateau.acheterCarte(nom))
    {
        std::cout << "Impossible d'acheter cette carte.\n";
        return;
    }

    // 10. Payer et consommer un achat
    joueur.depenserArgent(coutCarte);
    joueur.depenserAchat();

    // 11. Creer la carte et l'ajouter a la defausse
    std::unique_ptr<Carte> carte = catalogue.creer(nom);
    joueur.ajouterCarte(std::move(carte));

    std::cout << "\nCarte achetee avec succes : "
              << nom << " !\n";

    std::cout << "Argent restant : "
              << joueur.getArgent() << " pieces\n";

    std::cout << "Achats restants : "
              << joueur.getAchat() << "\n";
}









// ==================================================
    // PHASE 2 : ACHAT
    // ==================================================

    bool phaseAchat = true;

    while (phaseAchat) {
        if (joueur.getAchat() <= 0) {
            std::cout << JAUNE << "\nVous n'avez plus d'achat disponible.\n" << RESET;
            break;
        }

        afficherTitre("PHASE D'ACHAT");

        joueur.afficherMain();

        std::cout << "Argent disponible : " << VERT << joueur.getArgent() << " pieces" << RESET << "\n";

        std::cout << "Achats disponibles : " << joueur.getAchat() << "\n\n";

        std::cout << "1. Jouer ses tresors\n"
                  << "2. Acheter une carte\n"
                  << "3. Terminer le tour\n";

        int choix;

        if (!demanderChoix(choix, 1, 3)) {
            return;
        }

        switch (choix) {
            case 1:
                jouerToutTresor(joueur);
                break;

            case 2:
                acheterCarte();
                break;

            case 3:
                phaseAchat = false;
                break;
        }
    }
    */

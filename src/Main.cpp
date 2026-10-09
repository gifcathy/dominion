#include "InitialisationCartes.hpp"

int main() {
    CatalogueCartes catalogue;

    initialiserCatalogue(catalogue);

    auto cArgent = catalogue.creer("Argent");
    cArgent->afficher();

    auto cAtelier = catalogue.creer("Atelier");
    cAtelier->afficher();

    auto cBucheron = catalogue.creer("Bucheron");
    cBucheron->afficher();

    return 0;
}
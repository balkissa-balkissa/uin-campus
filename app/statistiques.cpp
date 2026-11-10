#include "uincampus/statistiques.hpp"
#include "uincampus/saisie.hpp"

#include <format>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::string ue = uin::lireTexte("Nom de l'UE : ");
    const int effectif = uin::lireEntier("Nombre d'étudiants (1-200) : ", 1, 200);

    std::vector<double> notes{};
    notes.reserve(static_cast<std::size_t>(effectif));
    for (int i = 1; i <= effectif; ++i) {
        notes.push_back(uin::lireNote(std::format("Note de l'étudiant {} (0-20) : ", i)));
    }

    const uincampus::Statistiques stats =
        uincampus::calculer_statistiques(notes);

    std::cout << "\nStatistiques - " << ue << " (" << notes.size()
              << " étudiants)\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Note minimale : " << stats.minimum << "\n";
    std::cout << "Note maximale : " << stats.maximum << "\n";
    std::cout << "Moyenne : " << stats.moyenne << "\n";
    std::cout << "Écart-type : " << stats.ecart_type << "\n";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Admis : " << stats.nb_admis << " ("
              << stats.pourcentage_admis << " %)\n";

    std::cout << "\nRépartition par mention\n";
    for (std::size_t i = 0; i < uincampus::kNbMentions; ++i) {
        const uincampus::Mention mention =
            static_cast<uincampus::Mention>(i);
        const int count = stats.repartition[i];
        std::cout << uincampus::nom_mention(mention) << " "
                  << std::string(static_cast<std::size_t>(count), '*')
                  << " (" << count << ")\n";
    }
    return 0;
}

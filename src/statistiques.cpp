#include "uincampus/statistiques.hpp"

#include <algorithm>
#include <cmath>

namespace uincampus {

Mention mention_de(double note) {
    if (note < kSeuilAdmis) {
        return Mention::Ajourne;
    }
    if (note < kSeuilPassable) {
        return Mention::Passable;
    }
    if (note < kSeuilAssezBien) {
        return Mention::AssezBien;
    }
    if (note < kSeuilBien) {
        return Mention::Bien;
    }
    return Mention::TresBien;
}

Statistiques calculer_statistiques(const std::vector<double>& notes) {
    Statistiques stats{};
    if (notes.empty()) {
        return stats;
    }

    double minimum = notes.front();
    double maximum = notes.front();
    double somme = 0.0;

    for (double note : notes) {
        minimum = std::min(minimum, note);
        maximum = std::max(maximum, note);
        somme += note;
    }

    const double moyenne = somme / static_cast<double>(notes.size());

    double somme_carres = 0.0;
    for (double note : notes) {
        const double ecart = note - moyenne;
        somme_carres += ecart * ecart;
    }
    const double variance = somme_carres / static_cast<double>(notes.size());

    int nb_admis = 0;
    std::array<int, kNbMentions> repartition{};

    for (double note : notes) {
        if (note >= kSeuilAdmis) {
            ++nb_admis;
        }
        const Mention mention = mention_de(note);
        const std::size_t index = static_cast<std::size_t>(mention);
        ++repartition[index];
    }

    stats.minimum = minimum;
    stats.maximum = maximum;
    stats.moyenne = moyenne;
    stats.ecart_type = std::sqrt(variance);
    stats.nb_admis = nb_admis;
    stats.pourcentage_admis =
        100.0 * static_cast<double>(nb_admis) / static_cast<double>(notes.size());
    stats.repartition = repartition;
    return stats;
}

std::string nom_mention(Mention mention) {
    switch (mention) {
        case Mention::Ajourne: return "Ajourné";
        case Mention::Passable: return "Passable";
        case Mention::AssezBien: return "Assez bien";
        case Mention::Bien: return "Bien";
        case Mention::TresBien: return "Très bien";
    }
    return "Ajourné";
}

} // namespace uincampus

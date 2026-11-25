#pragma once

#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "ui_language.h"

namespace esphome::nspanel_easy {

/// @brief One text from Home Assistant (in Polish) and its translations.
struct UiDictionaryEntry {
  const char *pl;
  const char *en;
  const char *hu;
  const char *sk;
  const char *cs;
  const char *de;
  const char *fr;
  const char *es;
};

/**
 * @brief Kurantowka: texts the Blueprint sends in Polish (names, page labels), translated on the panel.
 *
 * Exact, case-sensitive match on the whole text. Add a row here for any new Polish name used in a Blueprint input.
 */
inline constexpr UiDictionaryEntry UI_DICTIONARY[] = {
    // Pages
    {"Ogrzewanie", "Heating", "Fűtés", "Kúrenie", "Topení", "Heizung", "Chauffage", "Calefacción"},
    {"Rozkład dnia", "Daily schedule", "Napirend", "Denný program", "Denní program", "Tagesablauf", "Programme du jour", "Horario del día"},
    // Rooms
    {"Salon", "Main Room", "Nappali", "Obývačka", "Obývací pokoj", "Wohnzimmer", "Salon", "Salón"},
    {"Sypialnia", "Sleeping Room", "Hálószoba", "Spálňa", "Ložnice", "Schlafzimmer", "Chambre", "Dormitorio"},
    {"Pokój", "Room", "Szoba", "Izba", "Pokoj", "Zimmer", "Chambre", "Habitación"},
    {"Łazienka", "Bathroom", "Fürdőszoba", "Kúpeľňa", "Koupelna", "Badezimmer", "Salle de bain", "Baño"},
    {"Prawy pokój", "Right Room", "Jobb oldali szoba", "Pravá izba", "Pravý pokoj", "Rechtes Zimmer", "Chambre droite", "Habitación derecha"},
    {"Lewy pokój", "Left Room", "Bal oldali szoba", "Ľavá izba", "Levý pokoj", "Linkes Zimmer", "Chambre gauche", "Habitación izquierda"},
    {"Pokój prawy", "Right Room", "Jobb oldali szoba", "Pravá izba", "Pravý pokoj", "Rechtes Zimmer", "Chambre droite", "Habitación derecha"},
    {"Pokój lewy", "Left Room", "Bal oldali szoba", "Ľavá izba", "Levý pokoj", "Linkes Zimmer", "Chambre gauche", "Habitación izquierda"},
    {"Korytarz", "Hallway", "Folyosó", "Chodba", "Chodba", "Flur", "Couloir", "Pasillo"},
    {"Kuchnia", "Kitchen", "Konyha", "Kuchyňa", "Kuchyně", "Küche", "Cuisine", "Cocina"},
    {"Przedpokój", "Hallway", "Előszoba", "Predsieň", "Předsíň", "Diele", "Entrée", "Recibidor"},
    {"Antresola", "Mezzanine", "Galéria", "Antresol", "Antresol", "Galerie", "Mezzanine", "Altillo"},
    // Daily schedule
    {"Zameldowanie", "Check-in", "Érkezés", "Príchod", "Příjezd", "Check-in", "Arrivée", "Entrada"},
    {"Wymeldowanie", "Check-out", "Távozás", "Odchod", "Odjezd", "Check-out", "Départ", "Salida"},
    {"Śniadanie", "Breakfast", "Reggeli", "Raňajky", "Snídaně", "Frühstück", "Petit-déjeuner", "Desayuno"},
    {"SPA (rezerwacja)", "SPA (booking)", "SPA (foglalás)", "SPA (rezervácia)", "SPA (rezervace)", "SPA (Reservierung)", "SPA (réservation)", "SPA (reserva)"},
    {"Cisza nocna", "Quiet hours", "Csendes órák", "Nočný kľud", "Noční klid", "Nachtruhe", "Heures calmes", "Horas de silencio"},
    {"Właściciel (tel.)", "Owner (phone)", "Tulajdonos (tel.)", "Majiteľ (tel.)", "Majitel (tel.)", "Eigentümer (Tel.)", "Propriétaire (tél.)", "Propietario (tel.)"},
    {"Recepcja", "Reception", "Recepció", "Recepcia", "Recepce", "Rezeption", "Réception", "Recepción"},
};

/// @brief The text in the current user interface language, or the text itself when it is not in the dictionary.
inline std::string ui_translate(const std::string &text) {
  if (ui_language() == 0 || text.empty()) return text;
  for (const auto &entry : UI_DICTIONARY) {
    if (text == entry.pl) return ui_text(entry.pl, entry.en, entry.hu, entry.sk, entry.cs, entry.de, entry.fr, entry.es);
  }
  // Times of the daily schedule: "od 15:00" (from) and "do 11:00" (until)
  if (text.rfind("od ", 0) == 0) {
    const std::string rest = text.substr(3);
    if (ui_language() == 2) return rest + "-tól";  // Hungarian: a suffix
    return std::string(ui_text("od", "from", "", "od", "od", "ab", "à partir de", "desde")) + " " + rest;
  }
  if (text.rfind("do ", 0) == 0) {
    const std::string rest = text.substr(3);
    if (ui_language() == 2) return rest + "-ig";  // Hungarian: a suffix
    return std::string(ui_text("do", "until", "", "do", "do", "bis", "jusqu'à", "hasta")) + " " + rest;
  }
  return text;
}

/// @brief Translates the text of a raw Nextion text command (`component.txt="text"`), as the Blueprint sends
/// for the labels of the entities pages; any other command is returned as it is.
inline std::string ui_translate_command(const std::string &command) {
  if (ui_language() == 0) return command;
  static const std::string MARK = ".txt=\"";
  const size_t start = command.find(MARK);
  if (start == std::string::npos || command.size() < start + MARK.size() + 1 || command.back() != '"') return command;
  const size_t text_start = start + MARK.size();
  const std::string text = command.substr(text_start, command.size() - text_start - 1);
  const std::string translated = ui_translate(text);
  if (translated == text) return command;
  return command.substr(0, text_start) + translated + "\"";
}

/// @brief A button page setup as received from the Blueprint (untranslated), drawn again after a language change.
struct UiButtonsSetup {
  std::string page_label;
  std::vector<std::string> labels;
  std::vector<std::string> state_values;
  int32_t confirm{0};
  int32_t icon_font{0};
  std::string temperature_unit;
};

/// @brief The last button page setups from the Blueprint, by page name.
inline std::map<std::string, UiButtonsSetup> &ui_buttons_setups() {
  static std::map<std::string, UiButtonsSetup> setups;
  return setups;
}

/// @brief Translated copy of a list of texts.
inline std::vector<std::string> ui_translate_all(const std::vector<std::string> &texts) {
  std::vector<std::string> out;
  out.reserve(texts.size());
  for (const auto &text : texts) out.push_back(ui_translate(text));
  return out;
}

}  // namespace esphome::nspanel_easy

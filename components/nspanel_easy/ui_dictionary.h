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
};

/**
 * @brief Kurantowka: texts the Blueprint sends in Polish (names, page labels), translated on the panel.
 *
 * Exact, case-sensitive match on the whole text. Add a row here for any new Polish name used in a Blueprint input.
 */
inline constexpr UiDictionaryEntry UI_DICTIONARY[] = {
    // Pages
    {"Ogrzewanie", "Heating", "Fűtés", "Kúrenie", "Topení"},
    {"Rozkład dnia", "Daily schedule", "Napirend", "Denný program", "Denní program"},
    // Rooms
    {"Salon", "Main Room", "Nappali", "Obývačka", "Obývací pokoj"},
    {"Sypialnia", "Sleeping Room", "Hálószoba", "Spálňa", "Ložnice"},
    {"Pokój", "Room", "Szoba", "Izba", "Pokoj"},
    {"Łazienka", "Bathroom", "Fürdőszoba", "Kúpeľňa", "Koupelna"},
    {"Kuchnia", "Kitchen", "Konyha", "Kuchyňa", "Kuchyně"},
    {"Przedpokój", "Hallway", "Előszoba", "Predsieň", "Předsíň"},
    {"Antresola", "Mezzanine", "Galéria", "Antresol", "Antresol"},
    // Daily schedule
    {"Zameldowanie", "Check-in", "Érkezés", "Príchod", "Příjezd"},
    {"Wymeldowanie", "Check-out", "Távozás", "Odchod", "Odjezd"},
    {"Śniadanie", "Breakfast", "Reggeli", "Raňajky", "Snídaně"},
    {"SPA (rezerwacja)", "SPA (booking)", "SPA (foglalás)", "SPA (rezervácia)", "SPA (rezervace)"},
    {"Cisza nocna", "Quiet hours", "Csendes órák", "Nočný kľud", "Noční klid"},
    {"Właściciel (tel.)", "Owner (phone)", "Tulajdonos (tel.)", "Majiteľ (tel.)", "Majitel (tel.)"},
    {"Recepcja", "Reception", "Recepció", "Recepcia", "Recepce"},
};

/// @brief The text in the current user interface language, or the text itself when it is not in the dictionary.
inline std::string ui_translate(const std::string &text) {
  if (ui_language() == 0 || text.empty()) return text;
  for (const auto &entry : UI_DICTIONARY) {
    if (text == entry.pl) return ui_text(entry.pl, entry.en, entry.hu, entry.sk, entry.cs);
  }
  return text;
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

#pragma once

#include <cstring>
#include <string>

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
    {"Salon", "Living room", "Nappali", "Obývačka", "Obývací pokoj"},
    {"Sypialnia", "Bedroom", "Hálószoba", "Spálňa", "Ložnice"},
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

}  // namespace esphome::nspanel_easy

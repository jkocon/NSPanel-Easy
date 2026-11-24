#pragma once

#include <cstdint>

namespace esphome::nspanel_easy {

/**
 * @brief Kurantowka: the user interface language, selectable at runtime.
 *
 * Index order follows the "Language" select in Home Assistant and the language list on the panel:
 * 0 Polski, 1 English, 2 Magyar, 3 Slovenčina, 4 Čeština.
 */
inline uint8_t &ui_language() {
  static uint8_t value = 0;
  return value;
}

/// @brief Number of selectable user interface languages.
inline constexpr uint8_t UI_LANGUAGE_COUNT = 5;

/// @brief Short codes of the selectable languages, in index order (sent to Home Assistant).
inline const char *ui_language_code(uint8_t index) {
  static const char *const codes[UI_LANGUAGE_COUNT] = {"pl", "en", "hu", "sk", "cs"};
  return index < UI_LANGUAGE_COUNT ? codes[index] : codes[0];
}

/// @brief The text for the current user interface language; Polish is the fallback.
inline const char *ui_text(const char *pl, const char *en, const char *hu, const char *sk, const char *cs) {
  switch (ui_language()) {
    case 1:
      return en;
    case 2:
      return hu;
    case 3:
      return sk;
    case 4:
      return cs;
    default:
      return pl;
  }
}

}  // namespace esphome::nspanel_easy

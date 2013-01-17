#include "xml_savegame.h"

xml_savegame::xml_savegame() {
  this->external = "";
  this->clone = true;
}

/* <savegame> attributes */
void xml_savegame::set_external(const QString &directory) {
  this->external = directory;
}

QString xml_savegame::get_external() {
  return this->external;
}

void xml_savegame::set_clone(bool choice) {
  this->clone = choice;
}

bool xml_savegame::get_clone() {
  return this->clone;
}

#include "xml_choice.h"

xml_choice::xml_choice() {
  /* <choice> attributes */
  this->name = "";

  /* <patch> */
  this->patch_ids = new QList<QString>;
}

/* <choice> attributes */
void xml_choice::set_name(const QString &choice) {
  this->name = choice;
}

QString xml_choice::get_name() {
  return this->name;
}

/* <patch> */
void xml_choice::add_patch_id(const QString &patch) {
  this->patch_ids->append(patch);
}

QList<QString> * xml_choice::get_patch_ids() {
  return this->patch_ids;
}

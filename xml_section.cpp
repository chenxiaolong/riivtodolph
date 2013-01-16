#include "xml_section.h"

xml_section::xml_section() {
  this->name = "";
  this->options = new QList<xml_option *>();
}

/* <section> attributes */
void xml_section::set_name(const QString &section) {
  this->name = section;
}

QString xml_section::get_name() {
  return this->name;
}

/* <option> */
void xml_section::add_option(xml_option *option) {
  this->options->append(option);
}

QList<xml_option *> * xml_section::get_options() {
  return this->options;
}

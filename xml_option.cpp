#include "xml_option.h"

xml_option::xml_option() {
  /* <option> attributes */
  this->id = "";
  this->name = "";
  this->default_choice = 0;

  /* <choice> */
  this->choices = new QList<xml_choice *>();
}

/* <option> attributes */
void xml_option::set_id(const QString &option) {
  this->id = option;
}

QString xml_option::get_id() {
  return this->id;
}

void xml_option::set_name(const QString &option) {
  this->name = option;
}

QString xml_option::get_option() {
  return this->name;
}

void xml_option::set_default(int value) {
  this->default_choice = value;
}

int xml_option::get_default() {
  return this->default_choice;
}

/* <choice> */
void xml_option::add_choice(xml_choice *choice) {
  this->choices->append(choice);
}

QList<xml_choice *> * xml_option::get_choice() {
  return this->choices;
}

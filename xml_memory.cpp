#include "xml_memory.h"

xml_memory::xml_memory() {
  /* <memory> attributes */
  this->offset = 0x0;
  this->value = "";
  this->valuefile = "";
  this->original = "";
}

/* <memory> attributes */
void xml_memory::set_offset(int hex) {
  this->offset = hex;
}

int xml_memory::get_offset() {
  return this->offset;
}

void xml_memory::set_value(const QString &hex) {
  this->value = hex;
}

QString xml_memory::get_value() {
  return this->value;
}

void xml_memory::set_valuefile(const QString &file) {
  this->valuefile = file;
}

QString xml_memory::get_valuefile() {
  return this->valuefile;
}

void xml_memory::set_original(const QString &hex) {
  this->original = hex;
}

QString xml_memory::get_original() {
  return this->original;
}

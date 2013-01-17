#include "xml_file.h"

xml_file::xml_file() {
  /* <file> attributes */
  this->disc_file = "";
  this->external_file = "";
  this->resize = true;
  this->create = false;
  this->offset = 0x0;
  this->length = 0x0;
}

/* <file> attributes */
void xml_file::set_disc_file(const QString &file) {
  this->disc_file = file;
}

QString xml_file::get_disc_file() {
  return this->disc_file;
}

void xml_file::set_external_file(const QString &file) {
  this->external_file = file;
}

QString xml_file::get_external_file() {
  return this->external_file;
}

void xml_file::set_resize(bool choice) {
  this->resize = choice;
}

bool xml_file::get_resize() {
  return this->resize;
}

void xml_file::set_create(bool choice) {
  this->create = choice;
}

bool xml_file::get_create() {
  return this->create;
}

void xml_file::set_offset(int hex) {
  this->offset = hex;
}

int xml_file::get_offset() {
  return this->offset;
}

void xml_file::set_length(int hex) {
  this->length = hex;
}

int xml_file::get_length() {
  return this->length;
}

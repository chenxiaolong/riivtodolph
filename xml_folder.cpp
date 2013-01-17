#include "xml_folder.h"

xml_folder::xml_folder() {
  /* <folder> attributes */
  this->disc_folder = "";
  this->external_folder = "";
  this->resize = true;
  this->create = false;
  this->recursive = true;
  this->length = 0x0;
}

/* <folder> attributes */
void xml_folder::set_disc_folder(const QString &directory) {
  this->disc_folder = directory;
}

QString xml_folder::get_disc_folder() {
  return this->disc_folder;
}

void xml_folder::set_external_folder(const QString &directory) {
  this->external_folder = directory;
}

QString xml_folder::get_external_folder() {
  return this->external_folder;
}

void xml_folder::set_resize(bool choice) {
  this->resize = choice;
}

bool xml_folder::get_resize() {
  return this->resize;
}

void xml_folder::set_create(bool choice) {
  this->create = choice;
}

bool xml_folder::get_create() {
  return this->create;
}

void xml_folder::set_recursive(bool choice) {
  this->recursive = choice;
}

bool xml_folder::get_recursive() {
  return this->recursive;
}

void xml_folder::set_length(int hex) {
  this->length = hex;
}

int xml_folder::get_length() {
  return this->length;
}

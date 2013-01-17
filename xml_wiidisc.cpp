#include "xml_wiidisc.h"

xml_wiidisc::xml_wiidisc() {
  /* <wiidisc> attribute defaults */
  this->root = "";
  this->version = 1;
  this->log = false;
  this->shiftfiles = false;

  /* <id> attribute defaults */
  this->game = "";
  this->developer = "";
  this->disc_number = 0;
  this->disc_version = 0;

  /* <region> */
  this->regions = new QList<QString>();

  /* <section> */
  this->sections = new QList<xml_section *>();

  /* <patch> */
  this->patches = new QList<xml_patch *>();
}

/* <wiidisc> attributes */
void xml_wiidisc::set_root(const QString &directory) {
  this->root = directory;
}

void xml_wiidisc::set_version(int ver) {
  this->version = ver;
}

void xml_wiidisc::set_log(bool choice) {
  this->log = choice;
}

void xml_wiidisc::set_shiftfiles(bool choice) {
  this->shiftfiles = choice;
}

QString xml_wiidisc::get_root() {
  return this->root;
}

int xml_wiidisc::get_version() {
  return this->version;
}

bool xml_wiidisc::get_log() {
  return this->log;
}

bool xml_wiidisc::get_shiftfiles() {
  return this->shiftfiles;
}

/* <id> attributes */
void xml_wiidisc::set_game(const QString &name) {
  this->game = name;
}

void xml_wiidisc::set_developer(const QString &name) {
  this->developer = name;
}

void xml_wiidisc::set_disc_number(int number) {
  this->disc_number = number;
}

void xml_wiidisc::set_disc_version(int version) {
  this->disc_version = version;
}

QString xml_wiidisc::get_game() {
  return this->game;
}

QString xml_wiidisc::get_developer() {
  return this->developer;
}

int xml_wiidisc::get_disc_number() {
  return this->disc_number;
}

int xml_wiidisc::get_disc_version() {
  return this->disc_version;
}

/* <region> */
void xml_wiidisc::add_region(const QString &region) {
  this->regions->append(region);
}

QList<QString> * xml_wiidisc::get_regions() {
  return this->regions;
}

/* <section> */
void xml_wiidisc::add_section(xml_section *section) {
  this->sections->append(section);
}

QList<xml_section *> * xml_wiidisc::get_sections() {
  return this->sections;
}

/* <patch> */
void xml_wiidisc::add_patch(xml_patch *patch) {
  this->patches->append(patch);
}

QList<xml_patch *> * xml_wiidisc::get_patches() {
  return this->patches;
}

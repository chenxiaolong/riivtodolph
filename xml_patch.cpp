#include "xml_patch.h"

xml_patch::xml_patch() {
  /* <patch> attributes */
  this->id = "";
  this->root = "";

  /* <file> */
  this->file_patches = new QList<xml_file *>();

  /* <folder> */
  this->folder_patches = new QList<xml_folder *>();

  /* <savegame> */
  this->savegame_patches = new QList<xml_savegame *>();

  /* <memory> */
  this->memory_patches = new QList<xml_memory *>();
}

/* <patch> attributes */
void xml_patch::set_id(const QString &patch) {
  this->id = patch;
}

QString xml_patch::get_id() {
  return this->id;
}

void xml_patch::set_root(const QString &directory) {
  this->root = directory;
}

QString xml_patch::get_root() {
  return this->root;
}

/* <file> */
void xml_patch::add_file_patch(xml_file *file) {
  this->file_patches->append(file);
}

QList<xml_file *> * xml_patch::get_file_patches() {
  return this->file_patches;
}

/* <folder> */
void xml_patch::add_folder_patch(xml_folder *directory) {
  this->folder_patches->append(directory);
}

QList<xml_folder *> * xml_patch::get_folder_patches() {
  return this->folder_patches;
}

/* <savegame> */
void xml_patch::add_savegame_patch(xml_savegame *savegame) {
  this->savegame_patches->append(savegame);
}

QList<xml_savegame *> * xml_patch::get_savegame_patches() {
  return this->savegame_patches;
}

/* <memory> */
void xml_patch::add_memory_patch(xml_memory *patch) {
  this->memory_patches->append(patch);
}

QList<xml_memory *> * xml_patch::get_memory_patches() {
  return this->memory_patches;
}

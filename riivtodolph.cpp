#include "riivtodolph.h"

riivtodolph::riivtodolph() {
  this->dir_config = "";
  this->dir_output = "";
  this->file_iso = "";
  this->file_riiv = "";
  this->file_wit = "";
  this->bytes = 4; // Default to dword
}

void riivtodolph::set_dir_config(const QString &directory) {
  this->dir_config = directory;
}

void riivtodolph::set_dir_output(const QString &directory) {
  this->dir_output = directory;
}

void riivtodolph::set_file_iso(const QString &filename) {
  this->file_iso = filename;
}

void riivtodolph::set_file_riiv(const QString &filename) {
  this->file_riiv = filename;
}

void riivtodolph::set_file_wit(const QString &filename) {
  this->file_wit = filename;
}

void riivtodolph::set_value_size(const QString &size) {
  if (size == "") {
    this->bytes = 0;
  }
  else if (size == "byte") {
    this->bytes = 1;
  }
  else if (size == "word") {
    this->bytes = 2;
  }
  else if (size == "dword") {
    this->bytes = 4;
  }
  else {
    this->bytes = -1;
  }
}

QString riivtodolph::get_dir_config() const {
  return this->dir_config;
}

QString riivtodolph::get_dir_output() const {
  return this->dir_output;
}

QString riivtodolph::get_file_iso() const {
  return this->file_iso;
}

QString riivtodolph::get_file_riiv() const {
  return this->file_riiv;
}

QString riivtodolph::get_file_wit() const {
  return this->file_wit;
}

QString riivtodolph::get_value_size() const {
  switch (this->bytes) {
  case 4:
    return QString("dword");
  case 2:
    return QString("word");
  case 1:
    return QString("byte");
  }
  return QString("ERROR!!!");
}

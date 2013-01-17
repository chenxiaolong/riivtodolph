#include "riivxmlparse.h"
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNamedNodeMap>
#include <QtXml/QDomNode>
#include <QtXml/QDomNodeList>

riivxmlparse::riivxmlparse(const riivtodolph *info) {
  this->xmltree = new xml_wiidisc();
  this->information = new riivtodolph();

  this->information->set_dir_config(info->get_dir_config());
  this->information->set_dir_output(info->get_dir_output());
  this->information->set_file_iso(info->get_file_iso());
  this->information->set_file_riiv(info->get_file_riiv());
  this->information->set_file_wit(info->get_file_wit());
  this->information->set_value_size(info->get_value_size());
}

bool riivxmlparse::process_attrs_wiidisc(const QDomNode &current) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "root") {
        qDebug() << "<wiidisc> Setting root to" << attrs.item(i).nodeValue();
        this->xmltree->set_root(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "version") {
        qDebug() << "<wiidisc> Setting version to" << attrs.item(i).nodeValue();
        this->xmltree->set_version(attrs.item(i).nodeValue().toInt());
      }
      else if (attrs.item(i).nodeName().toLower() == "log") {
        qDebug() << "<wiidisc> Setting log to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          this->xmltree->set_log(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          this->xmltree->set_log(false);
        }
        else {
          qDebug() << "<wiidisc> Unknown value '" << attrs.item(i).nodeValue() << "' for 'log' attribute";
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "shiftfiles") {
        qDebug() << "<wiidisc> Setting shiftfiles to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          this->xmltree->set_log(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          this->xmltree->set_log(false);
        }
        else {
          qDebug() << "<wiidisc> Unknown value '" << attrs.item(i).nodeValue() << "' for 'shiftfiles' attribute";
          return false;
        }
      }
      else {
        qDebug() << "<wiidisc> Unknown tag:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_wiidisc(const QDomNode &current) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "id") {
        qDebug() << "<wiidisc> Processing <id> tag...";
        if (!process_attrs_id(temp)) {
          return false;
        }
        if (!process_children_id(temp)) {
          return false;
        }
      }
      else if (temp.nodeName().toLower() == "options") {
        qDebug() << "<wiidisc> Processing <options> tag...";
        if (!process_children_options(temp)) {
          return false;
        }
      }
      else if (temp.nodeName().toLower() == "patch") {
        qDebug() << "<wiidisc> Processing <patch> tag...";
        xml_patch *temp_patch = new xml_patch();
        if (!process_attrs_patch(temp, temp_patch)) {
          return false;
        }
        if (!process_children_patch(temp, temp_patch)) {
          return false;
        }
        this->xmltree->add_patch(temp_patch);
      }
      else {
        qDebug() << "<wiidisc> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_id(const QDomNode &current) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "game") {
        qDebug() << "  <id> Setting game to" << attrs.item(i).nodeValue();
        this->xmltree->set_game(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "developer") {
        qDebug() << "  <id> Setting developer to" << attrs.item(i).nodeValue();
        this->xmltree->set_developer(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "disc") {
        qDebug() << "  <id> Setting disc number to" << attrs.item(i).nodeValue();
        this->xmltree->set_disc_number(attrs.item(i).nodeValue().toInt());
      }
      else if (attrs.item(i).nodeName().toLower() == "version") {
        qDebug() << "  <id> Setting disc version to" << attrs.item(i).nodeValue();
        this->xmltree->set_disc_version(attrs.item(i).nodeValue().toInt());
      }
      else {
        qDebug() << "  <id> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_id(const QDomNode &current) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "region") {
        qDebug() << "  <id> Processing <region> tag...";
        if (this->xmltree->get_game().size() == 4) {
          qDebug() << "  <id> Region included in game ID. Skipping <region>...";
        }
        else if (!process_attrs_region(temp)) {
          return false;
        }
      }
      else {
        qDebug() << "  <id> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  else {
    qDebug() << "  <id> No child nodes";
    return true;
  }
}

bool riivxmlparse::process_attrs_region(const QDomNode &current) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "type") {
        qDebug() << "    <region> Adding region" << attrs.item(i).nodeValue();
        this->xmltree->add_region(attrs.item(i).nodeValue());
      }
      else {
        qDebug() << "    <region> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_options(const QDomNode &current) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "section") {
        qDebug() << "  <options> Processing <section> tag...";
        xml_section *temp_section = new xml_section();
        if (!process_attrs_section(temp, temp_section)) {
          return false;
        }
        if (!process_children_section(temp, temp_section)) {
          return false;
        }
        this->xmltree->add_section(temp_section);
      }
      else {
        qDebug() << "  <options> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_section(const QDomNode &current, xml_section *section) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "name") {
        qDebug() << "    <section> Setting name to" << attrs.item(i).nodeValue();
        section->set_name(attrs.item(i).nodeValue());
      }
      else {
        qDebug() << "    <section> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_section(const QDomNode &current, xml_section *section) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "option") {
        qDebug() << "    <section> Processing <option> tag...";
        xml_option *temp_option = new xml_option();
        if (!process_attrs_option(temp, temp_option)) {
          return false;
        }
        if (!process_children_option(temp, temp_option)) {
          return false;
        }
        section->add_option(temp_option);
      }
      else {
        qDebug() << "    <section> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_option(const QDomNode &current, xml_option *option) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "id") {
        qDebug() << "      <option> Setting id to" << attrs.item(i).nodeValue();
        option->set_id(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "name") {
        qDebug() << "      <option> Setting name to" << attrs.item(i).nodeValue();
        option->set_name(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "default") {
        qDebug() << "      <option> Setting default to" << attrs.item(i).nodeValue();
        option->set_default(attrs.item(i).nodeValue().toInt());
      }
      else {
        qDebug() << "      <option> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_option(const QDomNode &current, xml_option *option) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "choice") {
        qDebug() << "      <option> Processing <choice> tag...";
        xml_choice *temp_choice = new xml_choice();
        if (!process_attrs_choice(temp, temp_choice)) {
          return false;
        }
        if (!process_children_choice(temp, temp_choice)) {
          return false;
        }
        option->add_choice(temp_choice);
      }
      else {
        qDebug() << "      <option> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_choice(const QDomNode &current, xml_choice *choice) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "name") {
        qDebug() << "        <choice> Setting name to" << attrs.item(i).nodeName();
        choice->set_name(attrs.item(i).nodeName());
      }
      else {
        qDebug() << "        <choice> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_choice(const QDomNode &current, xml_choice *choice) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "patch") {
        qDebug() << "        <choice> Processing <patch> tag...";
        if (!process_attrs_patch_id(temp, choice)) {
          return false;
        }
      }
      else  {
        qDebug() << "        <choice> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_patch_id(const QDomNode &current, xml_choice *choice) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "id") {
        qDebug() << "          <patch> Adding id" << attrs.item(i).nodeValue();
        choice->add_patch_id(attrs.item(i).nodeValue());
      }
      else {
        qDebug() << "          <patch> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_patch(const QDomNode &current, xml_patch *patch) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "id") {
        qDebug() << "  <patch> Setting id to" << attrs.item(i).nodeValue();
        patch->set_id(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "root") {
        qDebug() << "  <patch> Setting root to" << attrs.item(i).nodeValue();
        patch->set_root(attrs.item(i).nodeValue());
      }
      else {
        qDebug() << "  <patch> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_children_patch(const QDomNode &current, xml_patch *patch) {
  if (current.hasChildNodes()) {
    QDomNode temp = current;
    temp = temp.firstChild();
    do {
      if (temp.nodeName().toLower() == "file") {
        qDebug() << "  <patch> Processing <file> tag...";
        xml_file *temp_file = new xml_file();
        if (!process_attrs_file(temp, temp_file)) {
          return false;
        }
        patch->add_file_patch(temp_file);
      }
      else if (temp.nodeName().toLower() == "folder") {
        qDebug() << "  <patch> Processing <folder> tag...";
        xml_folder *temp_folder = new xml_folder();
        if (!process_attrs_folder(temp, temp_folder)) {
          return false;
        }
        patch->add_folder_patch(temp_folder);
      }
      else if (temp.nodeName().toLower() == "savegame") {
        qDebug() << "  <patch> Processing <savegame> tag...!";
        xml_savegame *temp_savegame = new xml_savegame();
        if (!process_attrs_savegame(temp, temp_savegame)) {
          return false;
        }
        patch->add_savegame_patch(temp_savegame);
      }
      else if (temp.nodeName().toLower() == "memory") {
        qDebug() << "  <patch> Processing <memory> tag...";
        xml_memory *temp_memory = new xml_memory();
        if (!process_attrs_memory(temp, temp_memory)) {
          return false;
        }
        patch->add_memory_patch(temp_memory);
      }
      else {
        qDebug() << "  <patch> Unknown tag:" << temp.nodeName();
        return false;
      }
      temp = temp.nextSibling();
    } while (!temp.isNull());
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_file(const QDomNode &current, xml_file *file) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "disc") {
        qDebug() << "    <file> Setting disc file to" << attrs.item(i).nodeValue();
        file->set_disc_file(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "external") {
        qDebug() << "    <file> Setting external file to" << attrs.item(i).nodeValue();
        file->set_external_file(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "resize") {
        qDebug() << "    <file> Setting resize to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          file->set_resize(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          file->set_resize(false);
        }
        else {
          qDebug() << "    <file> Unknown value '" << attrs.item(i).nodeValue() << "' for 'resize' attribute";
          return false;
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "create") {
        qDebug() << "    <file> Setting create to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          file->set_create(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          file->set_create(false);
        }
        else {
          qDebug() << "    <file> Unknown value '" << attrs.item(i).nodeValue() << "' for 'create' attribute";
          return false;
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "offset") {
        qDebug() << "    <file> Setting offset to" << attrs.item(i).nodeValue();
        file->set_create(attrs.item(i).nodeValue().toInt());
      }
      else if (attrs.item(i).nodeName().toLower() == "length") {
        qDebug() << "    <file> Setting length to" << attrs.item(i).nodeValue();
        file->set_length(attrs.item(i).nodeValue().toInt());
      }
      else {
        qDebug() << "    <file> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_folder(const QDomNode &current, xml_folder *folder) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "disc") {
        qDebug() << "    <folder> Setting disc folder to" << attrs.item(i).nodeValue();
        folder->set_disc_folder(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "external") {
        qDebug() << "    <folder> Setting external folder to" << attrs.item(i).nodeValue();
        folder->set_external_folder(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "resize") {
        qDebug() << "    <folder> Setting resize to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          folder->set_resize(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          folder->set_resize(false);
        }
        else {
          qDebug() << "    <folder> Unknown value '" << attrs.item(i).nodeValue() << "' for 'resize' attribute";
          return false;
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "create") {
        qDebug() << "    <folder> Setting create to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          folder->set_create(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          folder->set_create(false);
        }
        else {
          qDebug() << "    <folder> Unknown value '" << attrs.item(i).nodeValue() << "' for 'create' attribute";
          return false;
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "recursive") {
        qDebug() << "    <folder> Setting recursive to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          folder->set_recursive(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          folder->set_recursive(false);
        }
        else {
          qDebug() << "    <folder> Unknown value '" << attrs.item(i).nodeValue() << "' for 'recursive' attribute";
          return false;
        }
      }
      else if (attrs.item(i).nodeName().toLower() == "length") {
        qDebug() << "    <folder> Setting length to" << attrs.item(i).nodeValue();
        folder->set_length(attrs.item(i).nodeValue().toInt());
      }
      else {
        qDebug() << "    <folder> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_savegame(const QDomNode &current, xml_savegame *savegame) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "external") {
        qDebug() << "    <savegame> Setting external to" << attrs.item(i).nodeValue();
        savegame->set_external(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "clone") {
        qDebug() << "    <savegame> Setting clone to" << attrs.item(i).nodeValue();
        if (attrs.item(i).nodeValue().toLower() == "true") {
          savegame->set_clone(true);
        }
        else if (attrs.item(i).nodeValue().toLower() == "false") {
          savegame->set_clone(false);
        }
        else {
          qDebug() << "    <savegame> Unknown value '" << attrs.item(i).nodeValue() << "' for 'clone' attribute";
          return false;
        }
      }
      else {
        qDebug() << "    <savegame> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_attrs_memory(const QDomNode &current, xml_memory *memory) {
  if (current.hasAttributes()) {
    QDomNamedNodeMap attrs = current.attributes();
    for (int i = 0; i < attrs.size(); i++) {
      if (attrs.item(i).nodeName().toLower() == "offset") {
        qDebug() << "    <memory> Setting offset to" << attrs.item(i).nodeValue();
        memory->set_offset(attrs.item(i).nodeValue().toInt(NULL, 16));
      }
      else if (attrs.item(i).nodeName().toLower() == "value") {
        qDebug() << "    <memory> Setting value to" << attrs.item(i).nodeValue();
        memory->set_value(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "valuefile") {
        qDebug() << "    <memory> Setting valuefile to" << attrs.item(i).nodeValue();
        memory->set_valuefile(attrs.item(i).nodeValue());
      }
      else if (attrs.item(i).nodeName().toLower() == "original") {
        qDebug() << "    <memory> Setting original to" << attrs.item(i).nodeValue();
        memory->set_original(attrs.item(i).nodeValue());
      }
      else {
        qDebug() << "    <memory> Unknown attribute:" << attrs.item(i).nodeName();
        return false;
      }
    }
    return true;
  }
  return false;
}

bool riivxmlparse::process_tag(const QDomNode &current) {
  if (current.nodeName() == "wiidisc") {
    if (!process_attrs_wiidisc(current)) {
      return false;
    }
    if (!process_children_wiidisc(current)) {
      return false;
    }
  }
  return true;
}

bool riivxmlparse::parse() {
  QFile *xml = new QFile(information->get_file_riiv());
  if (!xml->open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Error:" << xml->errorString();
    return false;
  }

  QDomDocument doc;
  if (!doc.setContent(xml)) {
    qDebug() << "Error: Failed to parse Riivolution XML";
    return false;
  }

  QDomElement root = doc.documentElement();
  QDomNode current = root;

  bool succeeded = false;

  if (current.nodeName() != "wiidisc") {
    qDebug() << "Error: Not a Riivolution XML file";
  }
  else {
    succeeded = process_tag(current);
  }

  xml->close();

  return succeeded;
}

QString riivxmlparse::pretty_print() {
  QString output = "";

  QFile *xml = new QFile(information->get_file_riiv());
  if (!xml->open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "Error:" << xml->errorString();
    return "";
  }

  QDomDocument doc;
  if (!doc.setContent(xml)) {
    qDebug() << "Error: Failed to parse Riivolution XML";
    return "";
  }

  QDomElement root = doc.documentElement();
  QDomNode current = root;
  bool move_to_parent = false;
  int layer = 0;

  while (true) {
    if (!move_to_parent) {
      for (int i = 0; i < layer; i++) {
        output.append("| ");
      }
      output.append(current.nodeName());

      if (current.nodeValue() != "") {
        output.append(": ");
        output.append(current.nodeValue());
      }

      output.append("\n");

      if (current.hasAttributes()) {
        QDomNamedNodeMap attrs = current.attributes();
        for (int i = 0; i < attrs.size(); i++) {
          for (int j = 0; j < layer + 1; j++) {
            output.append("| ");
          }
          output.append("#attr: ");
          output.append(attrs.item(i).nodeName());
          output.append(": ");
          output.append(attrs.item(i).nodeValue());
          output.append("\n");
        }
      }
    }
    if (current.hasChildNodes() && !move_to_parent) {
      layer++;
      /* <id game="???">
       *  ^^
       *   \----> Current position (id)
       *      /-> New position (region) - first child node
       *      |
       *   <region type="P"/>
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       */
      current = current.firstChild();
      move_to_parent = false;
    }
    else if (!current.nextSibling().isNull()) {
      /* <id game="???">
       *   <region type="P"/>
       *     ^^^    ^^
       *      |      \-> New position (type) - get next node
       *      \--------> Current position (region)
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       *
       * The next loop would move the current position here:
       *
       * <id game="???">
       *   <region type="P"/>
       *            ^^
       *             \-> Current position (type)
       *      /--------> New position (region) - get next node
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       */
      current = current.nextSibling();
      move_to_parent = false;
    }
    else if (!current.parentNode().isNull()) {
      layer--;
      /* <id game="???">
       *  ^^
       *   \-> New position (id) - move to parent
       *   <region type="P"/>
       *   <region type="E"/>
       *   <region type="J"/>
       *            ^^
       *             \-> Current position (type) - last child node
       * </id>
       *
       * The traverser will NOT go back to the child nodes since
       * the move_to_parent variable is now set to true. The if
       * statement above that moves the traverser to the first
       * child node requires that the move_to_parent variable
       * be set to false.
       */
      current = current.parentNode();
      move_to_parent = true;
    }
    else {
      break;
    }
  }

  xml->close();

  return output;
}

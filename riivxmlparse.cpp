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
          qDebug() << "<wiidisc> Unknown value '" << attrs.item(i).nodeValue() << "' for 'shiftfiles' tag";
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

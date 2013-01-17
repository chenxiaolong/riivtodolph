#include "xml_patch.h"
#include "xml_section.h"

#include <QList>
#include <QString>

#ifndef XML_WIIDISC_H
#define XML_WIIDISC_H

class xml_wiidisc {
public:
  xml_wiidisc();

  /* <wiidisc> attributes */
  void set_root(const QString &directory);
  void set_version(int ver);
  void set_log(bool choice);
  void set_shiftfiles(bool choice);
  QString get_root();
  int get_version();
  bool get_log();
  bool get_shiftfiles();

  /* <id> attributes */
  void set_game(const QString &name);
  void set_developer(const QString &name);
  void set_disc_number(int number);
  void set_disc_version(int version);
  QString get_game();
  QString get_developer();
  int get_disc_number();
  int get_disc_version();

  /* <region> */
  void add_region(const QString &region);
  QList<QString> * get_regions();

  /* <section> */
  void add_section(xml_section *section);
  QList<xml_section *> * get_sections();

  /* <patch> */
  void add_patch(xml_patch *patch);
  QList<xml_patch *> * get_patches();


private:
  /*** <wiidisc> attributes ***/

  /* Treat all directories in XML relative to this directory */
  QString root;

  /* According to the spec, only version 1 is supported
   * Unused: Only affects Riivolution's XML parser */
  int version;

  /* Undocumented */
  bool log;
  bool shiftfiles;

  /*** <id> attributes ***/
  /*   Only one <id> node can exist, so let's include it here */

  /* Game ID */
  QString game;

  /* Developer */
  QString developer;

  /* Disc number */
  int disc_number;

  /* Disc version */
  int disc_version;

  /*** <region> ***/
  QList<QString> *regions;

  /*** <section> ***/
  QList<xml_section *> *sections;

  /*** <patch> ***/
  QList<xml_patch *> *patches;
};

#endif // XML_WIIDISC_H

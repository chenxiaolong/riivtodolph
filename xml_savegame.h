#include <QString>

#ifndef XML_SAVEGAME_H
#define XML_SAVEGAME_H

class xml_savegame {
public:
  xml_savegame();

  /* <savegame> attributes */
  void set_external(const QString &directory);
  QString get_external();
  void set_clone(bool choice);
  bool get_clone();

private:
  /*** <savegame> attributes ***/

  /* Directory to store game saves */
  QString external;

  /* Whether or not to copy the current save files to the external directory */
  bool clone;
};

#endif // XML_SAVEGAME_H

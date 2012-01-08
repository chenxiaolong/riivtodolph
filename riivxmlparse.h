#ifndef RIIVXMLPARSE_H
#define RIIVXMLPARSE_H

#include <QtXml/QDomDocument>
#include <QtCore/QHash>

class riivxmlparse {
private:
  /* Tags */
  static const QString
    TAG_choice,
    TAG_file,
    TAG_folder,
    TAG_id,
    TAG_macro,
    TAG_memory,
    TAG_option,
    TAG_options,
    TAG_patch,
    TAG_region,
    TAG_savegame,
    TAG_section,
    TAG_wiidisc;
  
  /* Attributes */
  static const QString
    ATTR_align,
    ATTR_clone,
    ATTR_create,
    ATTR_default,
    ATTR_developer,
    ATTR_disc,
    ATTR_external,
    ATTR_game,
    ATTR_id,
    ATTR_length,
    ATTR_name,
    ATTR_ocarina,
    ATTR_offset,
    ATTR_original,
    ATTR_patch,
    ATTR_path,
    ATTR_recursive,
    ATTR_resize,
    ATTR_root,
    ATTR_search,
    ATTR_type,
    ATTR_value,
    ATTR_valuefile,
    ATTR_version;

  void parseTag(const QDomNode &);

  struct info {
    QString root;
    QString version;
    QString game_id;
    QString game_dev;
    QString game_disc;
    QString game_ver;
  } riivinfo;

  /* The below are structures that represent the options that selected.
   * The XML structure may be a little confusing, so here's a way to
   * think of it:
   *
   * section: A class of options to modify the game
   *    Example: There could be a "Character" class that contains
   *             modifications to characters in the game and also a
   *             "Levels" class that contains modified levels to the
   *             game.
   *
   * option: A set of modifications/patches in a class/section
   *    Example: In a "Character" class, there could be a "Bob" option,
   *             a "Jeff" option, or a "David" option. Each contains
   *             modifications to change the main character to said
   *             character. Only one option can be used at a time.
   *
   * macro: A variation of an option
   *    Example: If the above example was for a multi-player game, there
   *             could be a "Player 1", Player 2", "Player 3", or
   *             "Player 4" macro that can slightly modify the option
   *             to change the character for the selected player without
   *             making four copies of the option.
   *
   * choice: A sub-option within an option
   *    Example: If the character Bob was chosen in the second example,
   *             there could be choices like "Bob With Green Shirt",
   *             "Bob With Hat", or "Bald Bob". It is, essentially, a
   *             more specific version of an option.
   *
   * --
   *
   * If a Riivolution XML file only contains one patch for the game, it
   * still needs to contain an choice in the option. This is by design.
   * The names can even be identical. For example:
   *
   * ...
   *   <section name="Levels">
   *     <option name="My new stages" ...>
   *       <choice name="My new stages>
   *         <patch .../>
   *       </choice>
   *     </option>
   *   </section>
   * ...
   */
  typedef struct {
    /* This holds information under the <param> node.
     * This is a leaf node; no other nodes can descend
     * from it. This basically holds a single key/value
     * pair, somewhat like a variable. They can be used
     * later on in the XML in the form {$variable_name).
     */
    QString name;
    QString value;
  } param;
  
  typedef struct {
    /* This holds information under the <macro> node.
     * <macro> nodes store variations of <option> nodes
     * with different parameters (<param>) so that mostly
     * duplicated <option> nodes aren't necessary.
     * Only <param> nodes can descend from it.
     */
    QString name; // Name of macro/variation showm in GUI
    QString id; // The id is used to match macros with options in the XML file
    QList<param> params; // Parameters
  } macro;

  typedef struct {
    /* This holds information under the Sub-<patch> node.
     * There are two different types of <patch> nodes
     * in the Riivolution XML file: a child of the <wiidisc>
     * node and also a <child> of the <choice> node.
     * This is the child of the <choice node> and will be
     * referred to as the "patchid" node, since it only
     * contains an id to the "real" <patch> node.
     * No other nodes can descend from it.
     */
    QString id; // The id used to match up the two types of <patch> nodes
  } patchid;

  typedef struct {
    /* This holds information under the <choice> node.
     * Sub-<patch>/patchid nodes can descend from it.
     * This node represents a choice of patches within
     * an option.
     */
    QList<patchid> patchids; // Patch id's
  } choice;

  typedef struct {
    /* This holds information under the <option> node.
     * <param> nodes and <choice> nodes descend from it.
     * While <macro> nodes are technically children of
     * <options> nodes, they will be represented here
     * (based on their id) since they are variations of
     * the options with another set of parameters.
     */
    QString name; // Name of option shown in GUI
    QString id; // The id is used to match macros with options in the XML file
    QList<param> params; // Parameters
    QList<macro> macros; // Macros/variations
    QList<choice> choices; // Choices of patches
  } option;

  typedef struct {
    /* This holds information under the <section> node.
     * Only <option> nodes descend from it.
     * This is a visual classification of a set of
     * <option> nodes.
     */
    QString name; // Name of section shown in GUI
    QList<option> options; // Options
  } section;

  /* Structures to store patches */
  typedef struct {
    QString blah;
  } PATCH_file;

  typedef struct {
    QString blah;
  } PATCH_folder;

  typedef struct {
    QString blah;
  } PATCH_memory;

  void parse_options(const QDomNode &);
  QList<PATCH_file> list_PATCH_file;
  QList<PATCH_folder> list_PATCH_folder;
  QList<PATCH_memory> list_PATCH_memory;
  //QList<OPTION_macro> list_OPTION_macro;

  void parse_id(const QDomNamedNodeMap &);
  void parse_macro(const QDomNamedNodeMap &);
  void parse_wiidisc(const QDomNamedNodeMap &);
  
public:
  riivxmlparse();
  ~riivxmlparse();
  bool readfile(const QString & filename);
};
#endif

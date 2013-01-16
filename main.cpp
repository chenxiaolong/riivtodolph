#include "riivtodolph.h"
#include "riivxmlparse.h"
#include <QCoreApplication>
#include <QString>
#include <getopt.h>




#include <QDebug>

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
    
  QString dir_config = "",
          dir_output = "",
          file_iso = "",
          file_riiv = "",
          file_wit = "",
          valuesize = "";

  int argument = 0;

  while ((argument = getopt(argc, argv, "c:o:i:r:w:s:")) != -1) {
    switch (argument) {
    case 'c':
      dir_config = optarg;
      break;
    case 'o':
      dir_output = optarg;
      break;
    case 'i':
      file_iso = optarg;
      break;
    case 'r':
      file_riiv = optarg;
      break;
    case 'w':
      file_wit = optarg;
      break;
    case 's':
      valuesize = optarg;
      break;
    default:
      exit(1);
    }
  }

  riivtodolph *test = new riivtodolph();
  test->set_dir_config(dir_config);
  test->set_dir_output(dir_output);
  test->set_file_iso(file_iso);
  test->set_file_riiv(file_riiv);
  test->set_file_wit(file_wit);
  test->set_value_size(valuesize);
  riivxmlparse *testparse = new riivxmlparse(test);

  //qDebug() << testparse->pretty_print();
  testparse->parse();
  return 0;

  return a.exec();
}

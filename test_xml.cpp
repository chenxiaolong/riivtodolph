#include "riivxmlparse.cpp"

int main(int argc, char *argv[]) {
  riivxmlparse *temp = new riivxmlparse();
  temp->readfile("/tmp/brawl.xml");
}
#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

int main() {

  Graphe a("broadway.txt");
  a.ponderation("broadway_weights_0.txt");

  Svgfile svgout;
  svgout.addDisk(100, 100, 90, "redball");
  svgout.addText(300, 300, "25;12", "black");
  return 0;
}

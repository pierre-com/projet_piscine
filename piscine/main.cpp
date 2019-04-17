#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

int main()
{
  Svgfile svgout;
  Graphe a("cubetown.txt");
  a.ponderation("cubetown_weights_0.txt");
  a.affichage(&svgout);
  return 0;
}

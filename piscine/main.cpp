#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

int main()
{
  Svgfile svgout;
  Graphe a("broadway.txt");
  a.ponderation("broadway_weights_0.txt");
  a.affichage(&svgout);
  return 0;
}

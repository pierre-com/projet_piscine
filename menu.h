#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "svgfile.h"

void menu();
int interface_principale();
int choix_kruskal();
void afficher_graphe(std::string name_graphe,std::string name_poids,Svgfile *svgout);
int choix_kruskal_fonction();
int choix_pareto_fonction();




#endif // MENU_H_INCLUDED

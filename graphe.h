#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arete.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "svgfile.h"

class Graphe
{
  public:
  Graphe (std::string);
  void affichage(Svgfile *ecran);
  void ponderation(std::string nomFichier_ponderation);
  void kruskal(int choix, Svgfile *ecran2);
  void kruskal(int choix);
  void affichage_kruskal(std::vector<Arete*> arete_pris,Svgfile &ecran);
  void pareto(Svgfile *ecran);
  ~Graphe();

  private:
  std::unordered_set< Arete*> m_aretes;
  std::unordered_map<int,Sommet*> m_sommets;
  std::unordered_set<Arete*> m_aretes_poids;
};
#endif

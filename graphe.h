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
  //void affichage_graphe_1();
  void affichage(Svgfile *ecran);

  void ponderation(std::string nomFichier_ponderation);
  void kruskal(std::string start);
  void kruskal();
    void pareto();
  //void affichage(Svgfile *ecran);
  ~Graphe();

  private:
  std::unordered_set< Arete*> m_aretes;
  std::unordered_map<int,Sommet*> m_sommets;
  std::unordered_set<Arete*> m_aretes_poids;
};
#endif

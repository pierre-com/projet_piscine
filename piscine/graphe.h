#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include "sommet.h"
#include "arete.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

class Graphe
{
  public:
  Graphe (std::string);
  void ponderation(std::string nomFichier_ponderation);
  void kruskal(std::string start);
  void kruskal();
  ~Graphe();
  private:
  std::unordered_set< Arete*> m_aretes;
  std::unordered_map<std::string,Sommet*> m_sommets;
  std::unordered_set<Arete*> m_aretes_poids;
};
#endif

#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>
#include <vector>


class Arete
{
  public:
  Arete(std::string m_id_arete, std::string sommet_x, std::string sommet_y, float poids1,float poids2);

  ~Arete();
  private:
  std::string m_id_arete;
  float m_poids1,m_poids2;
  std::string m_sommet_x, m_sommet_y; // extr�mit�s de l'aretes


};
#endif

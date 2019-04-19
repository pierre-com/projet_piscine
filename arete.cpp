#include "arete.h"
#include <iostream>

Arete::Arete(std::string id_arete, std::string sommet_x, std::string sommet_y, float poids1,float poids2):m_id_arete{id_arete},m_sommet_x{sommet_x},m_sommet_y{sommet_y},m_poids1{poids1},m_poids2{poids2} {}
float Arete::getPoids1()
{
    return m_poids1;
}

float Arete::getPoids2()
{
    return m_poids2;
}
std::string Arete::getm_id_arete()
{
  return m_id_arete;
}
std::string Arete::getm_sommet_x()
{
return m_sommet_x;
}
std::string Arete::getm_sommet_y()
{
return m_sommet_y;
}
Arete::~Arete() {}

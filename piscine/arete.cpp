#include "arete.h"
#include <iostream>

Arete::Arete(std::string id_arete, std::string sommet_x, std::string sommet_y, float poids1,float poids2):m_id_arete{id_arete},m_sommet_x{sommet_x},m_sommet_y{sommet_y},m_poids1{1},m_poids2{1} {}

Arete::~Arete(){}

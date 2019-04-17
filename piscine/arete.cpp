#include "arete.h"
#include <iostream>

Arete::Arete(int id_arete, int sommet_x, int sommet_y, float poids1,float poids2):m_id_arete{id_arete},m_sommet_x{sommet_x},m_sommet_y{sommet_y},m_poids1{poids1},m_poids2{poids2} {}

float Arete::getPoids1()
{
    return m_poids1;
}

float Arete::getPoids2()
{
    return m_poids2;
}

int Arete::getm_id_arete()
{
    return m_id_arete;
}

int Arete::getm_sommet_x()
{
    return m_sommet_x;
}

int Arete::getm_sommet_y()
{
    return m_sommet_y;
}

void Arete::setPoids1(float Poids1)
{
    m_poids1=Poids1;
}

void Arete::setPoids2(float Poids2)
{
    m_poids2=Poids2;
}


Arete::~Arete()
{

}

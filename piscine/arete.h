#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>
#include <vector>


class Arete
{
public:
    Arete(int m_id_arete, int sommet_x, int sommet_y, float poids1,float poids2);
    float getPoids1();
    float getPoids2();

    int getm_id_arete();
    int getm_sommet_x();
    int getm_sommet_y();
    void setPoids1(float poids1);
   void setPoids2(float poids2);
    ~Arete();
private:
    int m_id_arete;
    float m_poids1,m_poids2;
    int m_sommet_x, m_sommet_y; // extrémités de l'aretes


};
#endif

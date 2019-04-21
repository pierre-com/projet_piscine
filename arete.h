#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED
#include <iostream>
#include <vector>


class Arete
{
public:
    Arete(int m_id_arete, int sommet_x, int sommet_y, float poids0,float poids1);
    float getPoids(int choix);
    bool getMark();
    void setMark(bool mark);
    int getm_id_arete();
    int getm_sommet_x();
    int getm_sommet_y();
    void setPoids(float poids, int choix);
    ~Arete();
private:
    bool  m_marked;
    int m_id_arete;
    std::vector<float> m_poids;
    int m_sommet_x, m_sommet_y; // extrémités de l'aretes


};
#endif

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>

class Sommet
{
public:
    Sommet(int id,double x, double y);
    ~Sommet();
    double getm_x();
    double getm_y();
    int getm_id();

private:
    int m_id; //identifiant
    double m_x, m_y; //coordonnés


};
#endif

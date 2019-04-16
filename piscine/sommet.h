#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <string>

class Sommet
{
public:
    Sommet(std::string id,double x, double y);
    ~Sommet();
    double getm_x();
    double getm_y();
    double getm_x();
    double getm_y();
    std::string getm_id();

private:
    std::string m_id; //identifiant
    double m_x, m_y; //coordonnés


};
#endif

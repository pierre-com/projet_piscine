#include "sommet.h"

Sommet::Sommet(int id,double x, double y): m_id{id},m_x{x},m_y{y} {}

Sommet::~Sommet()
{

}

double Sommet::getm_x()
{
    return m_x;
}


double Sommet::getm_y()
{
    return m_y;
}

int Sommet::getm_id()
{
  return m_id;
}
#include "sommet.h"


/**
 * \file          graphe.cpp
 * \author        TD2 groupe 6
 * \date          21/04/2019
 * \brief         classe sommet
 *
 * \details    permet d'acceder aux valeurs stocker dans la classe sommet
*/

//constructeur de sommet
Sommet::Sommet(int id,double x, double y): m_id{id},m_x{x},m_y{y} {}

Sommet::~Sommet()
{

}

/**
 * \brief       récupérer abscisse du sommet
 * \details     on recupere la coordonnee au niveau de l'abscisse sans la modifier, lecture de donnees stockees dans le private de la classe sommet
 *
 * \param     pas de parametre
 * \return    on return l'abscisse du sommet
 *
 */
double Sommet::getm_x()
{
    return m_x;
}

/**
 * \brief       récupérer l ordonnee du sommet
 * \details     on recupere la coordonnee au niveau de l ordonnee sans la modifier, lecture de donnees stockees dans le private de la classe sommet
 *
 * \param     pas de parametre
 * \return    on return l'ordonnee du sommet
 *
 */
double Sommet::getm_y()
{
    return m_y;
}

/**
 * \brief       récupérer l identifiant du sommet
 * \details     on recupere l identifiant du sommet sans la modifier, lecture de donnees stockees dans le private de la classe sommet
 *
 * \param     pas de parametre
 * \return    on return l identifiant du sommet
 *
 */
int Sommet::getm_id()
{
  return m_id;
}

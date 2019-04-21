#include "arete.h"
#include <iostream>

/**
 * \file          arete.cpp
 * \author    TD2 groupe 6
 * \date       21/04/2019
 * \brief       permet de relier 2 sommets entre eux
 *
 * \details    suite à l'extraction des données du fichiers texte,
 *               on va devoir attribuer des sommets aux id_aretes avec des poids différents
 */


Arete::Arete(int id_arete, int sommet_x, int sommet_y, float poids0,float poids1) {

m_id_arete=id_arete;
m_sommet_x=sommet_x;
m_sommet_y=sommet_y;
m_poids.push_back(poids0);
m_poids.push_back(poids1);
m_marked = false;
}

/**
 * \brief       récupérer le poids des aretes
 * \details    récupérer le poids des aretes avec des poids différents
 *
 * \param    choix          c'est un entier qui permet de choisir quel poids on veut choisir pour effectuer un kruskal
 * \return    on return un vecteur de poids, qu'on a sauvegarder dans la classe arete au niveau du private
 *              lecture des données sans modification
 */
float Arete::getPoids(int choix)
{
    return m_poids[choix];
}

/**
 * \brief       récupérer l'identifiants de l'aretes
 * \details    permet de recuperer l identifiant de l'arete dans le private sans modifier la valeur a l'interieur
 *
 * \param     pas de parametre
 * \return    on return l'identifiant d'arete, sans le modifier
 *
 */
int Arete::getm_id_arete()
{
    return m_id_arete;
}

/**
 * \brief       récupérer la coordonnée des abcisse du sommet
 * \details    permet de recuperer la coordonnée des abcisse du sommet dans le private sans modifier la valeur a l'interieur
 *
 * \param     pas de parametre
 * \return    on return la coordonnée des abcisse du sommet, sans le modifier
 *
 */
int Arete::getm_sommet_x()
{
    return m_sommet_x;
}

/**
 * \brief       récupérer la coordonnée des ordonnées du sommet
 * \details    permet de recuperer la coordonnée des ordonnées du sommet dans le private sans modifier la valeur a l'interieur
 *
 * \param     pas de parametre
 * \return    on return la coordonnée des ordonnées du sommet, sans le modifier
 *
 */
int Arete::getm_sommet_y()
{
    return m_sommet_y;
}

/**
 * \brief       permet de changer la valeur du vecteurs poids du private
 * \details    permet de changer la valeur du vecteurs poids du private en sécurité, en utilisant une clé. Attribut un nouveau poids a poids en toute securite
 *
 * \param     prend en parametre un float Poids qui permet de connaitre le poids et un int choix qui permet de choisir quels poids on souhaite travailler avec.
 * \return    on return rien
 *
 */
void Arete::setPoids(float Poids,int choix)
{
    m_poids[choix]=Poids;
}

/**
 * \brief       savoir si l'arete a été marqué ou non
 * \details    connaitre la valeur booléeenne de l'arete, pour savoir si elle est marqué ou non et ceux sans modifier la valeur situé dans le private
 *
 * \param     ne prend rien en paramètre
 * \return    on return la valeur booléenne de m_marked
 *
 */
bool Arete::getMark()
{
    return m_marked;
}


/**
 * \brief       permet de changer la valeur de m_marked du private
 * \details    permet de changer la valeur de m_marked du private en sécurité, en utilisant une clé. Attribut une nouvelle valeur booléenne en toute securite
 *
 * \param     prend en parametre une valeur booleenne mark qui va nous permettre de savoir si l'arete est marque ou pas
 * \return    on return rien
 *
 */
void Arete::setMark(bool mark)
{
    m_marked=mark;
}

Arete::~Arete()
{

}

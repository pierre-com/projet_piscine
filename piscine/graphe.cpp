#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

Graphe::Graphe(std::string nomFichier)
{
  std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;//nombre de sommets du graphe
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;//identifiant sommet
    double x,y;// position
    for (int i=0; i<ordre; ++i)
    {
        ifs>>id; //lit le identifiant du sommet
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es sommet");
        //lit la posotion du sommet
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es sommet");
        ///si aucun soucis on insert
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");
    //lecture des aretes
    std::string id_arete;
    std::string sommet1;
    std::string sommet2;
    float poid1=1,poid2=1;
    for (int i=0; i<taille; ++i)
    {
        //on lit le nom de l'arete
        ifs>>id_arete;
        if(ifs.fail())
          throw std::runtime_error("Probleme lecture nom de l'arete");
        //lecture des ids des deux extrÈmitÈs
        ifs>>sommet1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecteur du sommet de depart");
        ifs>>sommet2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture du sommet d'arriver");
        //on crÈe l'arete avec son nom, et ses coordonnÈes
        m_aretes.insert({new Arete{id_arete,sommet1 ,sommet2 ,poid1,poid2}});



    }


ifs.close();
}

void Graphe::ponderation(std::string nomFichier_ponderation)
{
std::ifstream ifs{nomFichier_ponderation};
if (!ifs)
{
  throw std::runtime_error( "Impossible d'ouvrir en lecture11 " + nomFichier_ponderation );
}
int nb_aretes;
ifs >> nb_aretes;
if ( ifs.fail() )
{
  throw std::runtime_error("Probleme lecture nb aretes");
}
int nb_poids;//nombre de sommets du graphe
ifs >> nb_poids;
if ( ifs.fail() )
{
  throw std::runtime_error("Probleme lecture poids");
}
std::string id_arete2;//identifiant arete
float poids1,poids2;// poids arete
    for (int i=0; i<nb_aretes; ++i)
    {
        ifs>>id_arete2; //lit le identifiant de l'arete
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es arete");
        //lit la posotion de arete
        ifs>>poids1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es arete");
        ifs>>poids2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donn»es arete");
        ///si aucun soucis on insert
        m_aretes.insert({new Arete{id_arete2,"0" ,"0" ,poids1,poids2}});

    }
}


Graphe::~Graphe(){}

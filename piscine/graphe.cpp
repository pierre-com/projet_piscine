#include "graphe.h"
#include "svgfile.h"
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
            throw std::runtime_error("Probleme lecture donnÈes sommet");
        //lit la posotion du sommet
        ifs>>x;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnÈes sommet");
        ifs>>y;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnÈes sommet");
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
        //lecture des ids des deux extrémités
        ifs>>sommet1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecteur du sommet de depart");
        ifs>>sommet2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture du sommet d'arriver");
        //on crée l'arete avec son nom, et ses coordonnées
        m_aretes.insert({new Arete{id_arete,sommet1,sommet2,poid1,poid2}});
    }
    ifs.close();
}

void Graphe::ponderation(std::string nomFichier_ponderation)
{
    std::ifstream ifs{nomFichier_ponderation};
    if (!ifs)
    {
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier_ponderation );
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
            throw std::runtime_error("Probleme lecture donnÈes arete");
        //lit la posotion de arete
        ifs>>poids1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnÈes arete");
        ifs>>poids2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture donnÈes arete");
        ///si aucun soucis on insert
        m_aretes.insert({new Arete{id_arete2,"0","0",poids1,poids2}});

    }
}

void Graphe::affichage(Svgfile *ecran)
{
    for (const auto& elem : m_sommets)
        //permettre d'afficher les données des sommets
    {

        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 30, "greenball");

        //ecran->addText(300, 300, "25;12", "black");
    }

}

void Graphe::affichage(Svgfile *ecran)
{
  
  double x1, x2, y1, y2;
  for (const auto& elem1 : m_aretes)
  //affiche les aretes entre le sommets
  {
    //elem->getm_id_arete;
    for (const auto& elem2 : m_sommets)
    {
      if (elem1->getm_sommet_x()==elem2.second->getm_id())
      {
        //on recup les coord du sommet1
        x1=elem2.second->getm_x();
        y1=elem2.second->getm_y();
      }
      if (elem1->getm_sommet_y()==elem2.second->getm_id())
      {
        //on recup les coord du sommet2
        x2=elem2.second->getm_x();
        y2=elem2.second->getm_y();
      }

    }
    
    ecran->addLine(x1,y1,x2,y2, "black");
    //ecran->addText(300, 300, "25;12", "black");
  }
  for (const auto& elem : m_sommets)
   //permettre d'afficher les données des sommets
  {
    
  ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 20, "greenball");
  
    
  }
  
}



Graphe::~Graphe() {}

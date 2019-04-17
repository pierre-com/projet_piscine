#include "graphe.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "arete.h"
#include <string>
#include <stdio.h>

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;//nombre de sommets du graphe
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    int id;//identifiant sommet
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
    int id_arete;
    int sommet1;
    int sommet2;
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

    int id_arete2;//identifiant arete
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
        m_aretes_poids.insert({new Arete{id_arete2,0,0,poids1,poids2}});

    }
    ///on met le poids contenu dans aretes_poids dans m_aretes car ce dernier a tous les poids a 1;
    ///faire un vecteur pour le poids => comportant poids 1 et poids2 ==> utilisations du vecteur dans la partie en dessous
   for (auto& elem1 : m_aretes_poids)
    {
        for ( auto & elem2 : m_aretes)
        {
            if(elem1->getm_id_arete()==elem2->getm_id_arete())
            {
                elem2->setPoids1(elem1->getPoids1());
                elem2->setPoids2(elem1->getPoids2());
            }
        }
    }
}


void Graphe::affichage(Svgfile *ecran)
{
    for (const auto& elem : m_sommets)
        //permettre d'afficher les données des sommets
    {

        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 15, "greenball");


    }
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
        double x_moy=(x1+x2)/2;
        double y_moy =(y1+y2)/2;
        float p2;
        float p1;
        p1=elem1->getPoids1();
        p2=elem1->getPoids2();

        ///affichage à l'écran
        ecran->addText(x_moy-10,y_moy, p1, "red");
        ecran->addText(x_moy,y_moy, ";", "red");
        ecran->addText(x_moy+10,y_moy, p2, "red");


    }
    for (const auto& elem : m_sommets)
        //permettre d'afficher les données des sommets
    {

        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 20, "greenball");

    }

}


Graphe::~Graphe() {}

#include "graphe.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "arete.h"
#include <string>
#include <stdio.h>
#include <tgmath.h>

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

        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 10, "greenball");


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

        //faire la moyenne pour l'emplacement des poids
        double x_moy=(x1+x2)/2-20;
        double y_moy =(y1+y2)/2;
        float p2;
        float p1;
        std::string p1_next;
        std::string p2_next;
        //détermination et plaçace des poids sur la graphe de départ
        p1=elem1->getPoids1();
        p2=elem1->getPoids2();
        p1_next = std::to_string(p1);
        p1_next=p1_next.substr(0,3);
        p2_next = std::to_string(p2);
        p2_next= p2_next.substr(0,3);
        ///affichage à l'écran
        ecran->addText(x_moy,y_moy,p1_next+";"+p2_next,"red");
    }
    for (const auto& elem : m_sommets)
        //permettre d'afficher les données des sommets
    {
        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 15, "greenball");
    }

}


void Graphe::pareto()
{
  int c; // c= 2^n
int pb=0; // pb représente le n de 2^n
int nb_posibilite=pow(2,m_aretes.size());
//std::cout <<nb_posibilite;
//std::vector <tab_chiffre*>tab_combinaisons;
//std::vector <std::string> tab_chiffre;
std::vector <int> tmp;
for (c=0; c<nb_posibilite; c++)
{
  for (pb=m_aretes.size(); pb>=0; pb--)
  {
    //c>>pb ca insere autant de 0 que de pb de gauche a droite
    int val_ajoute=3;
    //std::cout<< ((c>>pb)&1);
    val_ajoute=((c>>pb)&1);
    //val_ajoute=val_ajoute+pow(10,m_aretes.size()+1);
    //std::cout<< val_ajoute;
    tmp.push_back(val_ajoute);
    // l'operateur & est une porte qui ajoute 1
  }
  //on a notre chiffre

  std::cout<< std::endl;
}

/////////////////TESTT////////
for(const auto& elem1 : tmp)
{
  std::cout<<elem1<<std::endl;
}


/*///on met le tmp dans dans tab_chiffre en le transformnt en string
std::string tampon;
int i=0;
std::vector <std::string> tab_chiffre (tmp.size());
for (auto& elem1 : tmp)
    {
      tampon=std::to_string(elem1);
      tab_chiffre[i]=tampon;
      i++;
    }
    //le tab_chiffre est rempli mais il a un 1 devant en trop
    //on lui enleve le 1 devant qui servait a la conversion de int au string pour evite les bug
for (int t=0;t<tmp.size();t++)
{
 tab_chiffre[t]=tab_chiffre[t].substr(1);
}
    //on a le tableau de string avec les vrais chiffres binaires
///maitenant on tri le tableau de toutes les possibilités
//on converti le vector en tableau classique
for(int y=0;y<2;y++)
{
    for(int i=0;i<tab_chiffre[y].size();i++)
    {

      std::cout<<tab_chiffre[i]<<std::endl;

    }
}
*/
std::cout<<" FINI";

}

Graphe::~Graphe() {}

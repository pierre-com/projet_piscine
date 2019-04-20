#include "graphe.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <tgmath.h>


void Graphe::pareto()
{
    int c; // c= 2^n
    int pb=0; // pb représente le n de 2^n
    int nb_posibilite=pow(2,m_aretes.size());
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
    // float poidsArete[2];

    for (auto& elem1 : m_aretes_poids)
    {
        for ( auto & elem2 : m_aretes)
        {
            if(elem1->getm_id_arete()==elem2->getm_id_arete())
            {
                elem2->setPoids(elem1->getPoids(0),0);
                elem2->setPoids(elem1->getPoids(1),1);
            }
        }
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
        double x_moy=(x1+x2)/2-20;
        double y_moy =(y1+y2)/2;
        //affichage des poids
        float p1;
        float p2;
        p1=elem1->getPoids(0);
        p2=elem1->getPoids(1);
        std::string p1_next;
        std::string p2_next;
        //choisir 1 chiffre après la virgule de notre float poids1, poids2
        p1_next = std::to_string(p1);
        p1_next=p1_next.substr(0,3);
        p2_next = std::to_string(p2);
        p2_next= p2_next.substr(0,3);

        //détermination et plaçace des poids sur la graphe de départ
        ecran->addText(x_moy,y_moy,p1_next+";"+p2_next,"red");
    }

    for (const auto& elem : m_sommets)
        //permettre d'afficher les données des sommets
    {
        ecran->addDisk(elem.second->getm_x(), elem.second->getm_y(), 20, "greenball");

    }

}

void Graphe::kruskal(int choix, Svgfile *ecran2)
{
    int allLinked=0;
    //m_sommets.find("1")->second->setMark(true);
    //m_aretes orderedAretes[m_aretes.size()];
    std::vector<int> orderedAretes;
    int aretePoidsMin=0;
    int idAretePoidsMin=0;
    int a=0;
    for (auto& elem1 : m_aretes)
    {
        aretePoidsMin = 100;
        for ( auto& elem2 : m_aretes)
        {
            a=0;
            //std::cout << elem1->getm_id_arete() << std::endl;
            for(auto& elem3 : orderedAretes)
            {
                if(elem3 == elem2->getm_id_arete())
                {
                    a=1;
                }
            }
            if(aretePoidsMin > elem2->getPoids(choix) && a ==0)
            {
                aretePoidsMin = elem2->getPoids(choix);
                idAretePoidsMin = elem2->getm_id_arete();
                //std::cout << idAretePoidsMin << std::endl;
            }
        }
        //std::cout << idAretePoidsMin << std::endl;
        //std::cout << aretePoidsMin << std::endl;
        //std::cout << " " << std::endl;
        orderedAretes.push_back(idAretePoidsMin);

    }

    int connexite[m_sommets.size()][2];
    //on déclare h, a -> variable itératrice pour les boucle
    int h=0;
    int x=0;
    int y=0;
    int v=0;
    //previous -> avoir valeur sommet précédent
    //sommets marqués
    int markSom1=0;
    int markSom2=0;

    //assimile les id au tableau de connexite
    for(auto& elem1: m_sommets)
    {
        connexite[h][0] = elem1.second->getm_id();
        connexite[h][1] = elem1.second->getm_id();
        h++;
    }

    for(auto& elem1: orderedAretes)  //arretes ordonés
    {
        for(auto& elem2 : m_aretes)  //arretes  -> pour les matcher
        {
            h=0;
            if(elem2->getm_id_arete() == elem1)  // si l'id de ordered = arrete m_arretes
            {
                int sommetx = elem2->getm_sommet_x(); // on match les sommets
                int sommety = elem2->getm_sommet_y();

                for(auto& elem3: m_sommets)  //on parcourt les sommets
                {
                    if(connexite[h][1] == sommetx )
                    {
                        //markSom1 = connexite[h][0]; //sommet marqué -> sommet de l'arete
                        x = h; //valeurs de son id dans le tableau
                    }
                    //same
                    if(connexite[h][1] == sommety)
                    {
                        //markSom2 = connexite[h][0];
                        y=h;
                    }
                    h++;
                }
                //si les indices des deux sommets marqués sont différent, alors on les selectionne
                if(connexite[x][0] != connexite[y][0])
                {

                    //si c'est le premier tour
                    markSom1 = connexite[x][0];
                    markSom2 = connexite[y][0];
                    connexite[y][0] = connexite[x][0];

                    for(v=0; v<m_sommets.size(); v++)
                    {
                        if(markSom2 == connexite[v][0])
                        {
                            //std::cout << connexite[v][0] << std::endl;
                            connexite[v][0] = markSom1;
                            //std::cout << connexite[v][0] << std::endl;

                        }
                    }
                    elem2->setMark(true); //on marque l'arrete
                }
            }
        }
    }

    /*-------------------Commencement de l'affichage------------------------*/
    //déclaration d'un vecteur/unordored set pour mettre les valeurs des aretes qu'on garde
    std::vector<Arete*> arete_pris;
//    affichage_kruskal(arete_pris,&ecran2);
    for(auto& elem1 : m_aretes)
    {
        if(elem1->getMark() == true)
        {
            arete_pris.push_back(elem1);
        }
    }

    //vérification des aretes qu'on push
    std::cout<<"ok1"<<std::endl;
    for(int i=0; i<arete_pris.size(); i++)
    {
        std::cout<<arete_pris[i]->getm_id_arete()<<std::endl;
    }
    //affichage de Kruskal
    //affichage des arêtes

    double x1=0, x2=0, y1=0, y2=0;
    for (int i=0; i<arete_pris.size(); i++)
        //affiche les aretes entre le sommets
    {
        //elem->getm_id_arete;
        for (const auto& elem2 : m_sommets)
        {
            if (arete_pris[i]->getm_sommet_x()==elem2.second->getm_id())
            {
                //on recup les coord du sommet1
                x1=elem2.second->getm_x();
                y1=elem2.second->getm_y();
            }
            if (arete_pris[i]->getm_sommet_y()==elem2.second->getm_id())
            {
                //on recup les coord du sommet2
                x2=elem2.second->getm_x();
                y2=elem2.second->getm_y();
            }
        }
        ecran2->addLine(x1,y1,x2,y2, "black");

        //affichage des poids des arêtes qu'on garde ! faire attention sur ce point
        double x_moy=(x1+x2)/2-20;
        double y_moy =(y1+y2)/2;
        //affichage des poids
        float p1;
        float p2;
        p1=arete_pris[i]->getPoids(0);
        p2=arete_pris[i]->getPoids(1);
        std::string p1_next;
        std::string p2_next;
        //choisir 1 chiffre après la virgule de notre float poids1, poids2
        p1_next = std::to_string(p1);
        p1_next=p1_next.substr(0,3);
        p2_next = std::to_string(p2);
        p2_next= p2_next.substr(0,3);
        //détermination et plaçace des poids sur la graphe de départ
        ecran2->addText(x_moy,y_moy,p1_next+";"+p2_next,"green");

        //affichage des sommets
        for (const auto& elem : m_sommets)
            //permettre d'afficher les données des sommets
        {
            ecran2->addDisk(elem.second->getm_x(), elem.second->getm_y(), 20, "redball");
        }
    }
}


Graphe::~Graphe() {}

#include "graphe.h"
#include "svgfile.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdio.h>
#include <tgmath.h>
#include <utility>


/**
 * \file          graphe.cpp
 * \author    TD2 groupe 6
 * \date       21/04/2019
 * \brief       permet d effectuer les differents operations sur les graphes
 *
 * \details    cette partie du code permet de faire l'affichage des graphes en mode normal, suite a un pareto et kruskal.
 *             Elle permet aussi de pouvoir traiter les algorithmes de kruskal et de pareto
*/


/**
 * \brief       récuperer les donnees du fichier texte
 * \details    récupérer les donnees du fichier texte, les mettres dans des set et map associes afin de pouvoir les reutiliser dans le cas de pareto et kruskal
 *
 * \param    std::string nomFichier          c'est une chaine de caractere qui permet aux utilisateurs d'entree et d acceder aux donnees du fichier texte en rapport avec la partie necessaire pour la suite du code
 * \return    on ne return aucune donnee
 *
 */
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


/**
 * \brief       récuperer les donnees du fichier texte avec les poids des aretes
 * \details    récupérer les donnees du fichier texte avec les poids des aretes, par rapport au identifiants des arete, on va attribuer les valeurs de poids des aretes dans le vecteur poids
 *
 * \param    std::string nomFichier_ponderation          c'est une chaine de caractere qui permet aux utilisateurs d'entree et d acceder aux donnees du fichier texte poids des aretes
 * \return    on ne return aucune donnee
 *
 */
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


/**
 * \brief       affichage du graphe original
 * \details     suite a la prise des données du fichier texte, nous allons afficher sur le svgout le graphe demander par l'utilisateur
 *
 * \param    Svgfile *ecran         création d'un écran pour pouvoir illustrer notre graphe sur un output
 * \return    on ne return aucune donnee
 *
 */
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

/**
 * \brief       faire un kruskal sur le graphe et afficher le graphe sur le svgout
 * \details     parcourir les identifiants d'arete et regarder le poids contenu par l'arete pour savoir si pour classer par poids croissant (du plus petit au plus grands)
 *              regarder les sommets qui constituent l'arete, voir si l'identifiants des aretes pris sont les mêmes
 *              si l'identiiant des sommets sont les mêmes alors on ne prend pas l'arete sinon on le prend
 *              affichage du resultat de Kruskal sur le svgout
 *
 * \param    int choix         pouvoir choisir entre le poids 1 ou le poids 2 du vecteur de poids
 * \param    Svgfile *ecran2         création d'un écran pour pouvoir illustrer notre graphe sur un output
 * \return    on ne return aucune donnee
 *
 */
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
    //afficher poids total de poids 1 et poids 0 des graphes qu'on sort
    int poids_tot1=0;
    int poids_tot2=0;
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
        poids_tot1=poids_tot1+p1;
        p2=arete_pris[i]->getPoids(1);
        poids_tot2=poids_tot2+p2;
        std::string p1_next;
        std::string p2_next;
        //choisir 1 chiffre après la virgule de notre float poids1, poids2
        p1_next = std::to_string(p1);
        p1_next=p1_next.substr(0,3);
        p2_next = std::to_string(p2);
        p2_next= p2_next.substr(0,3);
        //détermination et plaçace des poids sur la graphe de dépar
        ecran2->addText(x_moy,y_moy,p1_next+";"+p2_next,"green");

        //affichage des sommets
        for (const auto& elem : m_sommets)
            //permettre d'afficher les données des sommets
        {
            ecran2->addDisk(elem.second->getm_x(), elem.second->getm_y(), 20, "redball");
        }
    }

    std::cout<<"poids"<<std::endl;
    std::cout<<poids_tot1<<std::endl;
    std::cout<<poids_tot2<<std::endl;
    std::string p1_next_poids1;
    std::string p2_next_poids2;
    //choisir 1 chiffre après la virgule de notre float poids1, poids2
    p1_next_poids1= std::to_string(poids_tot1);
    p1_next_poids1=p1_next_poids1.substr(0,3);
    p2_next_poids2 = std::to_string(poids_tot2);
    p2_next_poids2= p2_next_poids2.substr(0,3);
    ecran2->addText(50,50,"couts totaux : ["+p1_next_poids1+";"+p2_next_poids2+"]","green");

    //ecran2->addText(50,50,"coucou"+" salut","green");
}

/**
 * \brief       faire un pareto sur le graphe
 * \details     ??
 *
 * \param    ??
 * \return    on ne return aucune donnee
 *
 */
void Graphe::pareto()
{
    int c; // c= 2^n
    int pb=1; // pb représente le n de 2^n
    int tmp=0;
    std::vector<std::vector <int> > combinaisons;
    std::vector <int> tempo;
    for (c=0; c<pow(2,m_aretes.size()); c++)
    {
        for (pb=(m_aretes.size()-1); pb>=0; pb--)
        {
            tmp=((c>>pb)&1);
            //std::cout<<tmp;
            if(tmp==1)
            {
                tempo.push_back(1);
            }
            if(tmp==0)
            {
                tempo.push_back(0);
            }
        }

        combinaisons.push_back(tempo);
        tempo.clear();
        //std::cout<< std::endl;
    }
///test affichage
    /*
    for (int f=0;f<combinaisons.size();f++)
    {
      for(int s=0;s<m_aretes.size();s++)
      {
        std::cout<<combinaisons[f][s]<< " ";
      }
      std::cout<< std::endl;
    }
    */
////tri des combinaison///
    int comp=0;
    for (int f=0; f<combinaisons.size(); f++)
    {
        for(int s=0; s<m_aretes.size(); s++)
        {
            comp=comp+combinaisons[f][s];
        }
        if(comp!=(m_sommets.size()-1))////m_sommet.size()-1
        {
            combinaisons.erase(combinaisons.begin()+f);
            f=0;
        }
        comp=0;

    }
//on attribue les 1 a des aretes
    std::vector <int> arete_exist;
    std::vector< std::pair<float,float> > solut_pareto;
    std::vector< std::pair<float,float> > solut_pareto_ordered;
    std::pair <float,float> poids_graphe;  //poids total de 1 graphe
    for (int f=0; f<combinaisons.size(); f++)
    {
        for(int s=0; s<m_aretes.size(); s++)
        {
            if(combinaisons[f][s]==1)
            {
                //l'arete numero s existe
                arete_exist.push_back(s);
            }
        }
        //////TRI du graphe f (on regarde si c'est une sol° de pareto) /////////////////////////

        int allLinked=0;
        int connexite[m_sommets.size()][2];
        //on déclare h, a -> variable itératrice pour les boucle
        int h=0;
        int x, y, v;
        //previous -> avoir valeur sommet précédent
        //sommets marqués
        int markSom1;
        int markSom2;

        //on met toutes les mark a false
        for(auto& elem2 : m_aretes)  //arretes  -> pour les matcher
        {
            elem2->setMark(false);

        }
        //assimile les id au tableau de connexite
        for(auto& elem1: m_sommets)
        {
            connexite[h][0] = elem1.second->getm_id();
            connexite[h][1] = elem1.second->getm_id();
            h++;
        }

        for(auto& elem1: arete_exist)  //arretes ordonés
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
        int o, u=0;
        for(o=0; o<m_sommets.size()-1; o++)
        {
            if(connexite[o][0] != connexite[o+1][0])
            {
                u=1;
            }
        }
        if(u==1)
        {
            // std::cout << f << std::endl;
            // std::cout << "Graphe non connexe" << std::endl;
        }
        else
        {
            /////LES SOLUTIONS //////////
            // std::cout << f << std::endl;
            // std::cout << "Graphe connexe" << std::endl;
            float sommePoids1=0;
            float sommePoids2=0;
            for(auto& elem2 : m_aretes)
            {
                //arretes  -> pour les matcher
                if(elem2->getMark() == true)
                {
                    sommePoids1 = elem2->getPoids(0) + sommePoids1;
                    sommePoids2 = elem2->getPoids(1) + sommePoids2;
                }
            }
            poids_graphe.first=sommePoids1;
            poids_graphe.second=sommePoids2;
            solut_pareto.push_back(poids_graphe);
            // std::cout << sommePoids1 << std::endl;
            // std::cout << sommePoids2 << std::endl;
        }

        //Vide le arete_existe
        arete_exist.clear();
// std::cout<< std::endl;
    }
///////////////////TRI des solution de pareto///////////////
    for(int i=0 ; i<solut_pareto.size() ; i++)
    {
        int a=0;
        for(int j=0 ; j<solut_pareto.size() ; j++)
        {

            if(a==0 && solut_pareto[i].first>solut_pareto[j].first && solut_pareto[i].second>solut_pareto[j].second )
            {
                solut_pareto_ordered.push_back(solut_pareto[j]);
                a=1;
            }
            for(int k=0; k<solut_pareto_ordered.size(); k++)
            {
                if(a==1 && solut_pareto_ordered[k].first>solut_pareto[j].first && solut_pareto_ordered[k].second>solut_pareto[j].second)
                {
                    solut_pareto_ordered.erase(solut_pareto_ordered.begin()+k);
                    solut_pareto_ordered.push_back(solut_pareto[j]);
                    a=0;
                    j=0;
                }
            }

        }


    }
    std::cout << "okkk";
    for(int l=0; l<solut_pareto_ordered.size(); l++)
    {
        std::cout << solut_pareto_ordered[l].first << " ; " << solut_pareto[l].second << std::endl;
    }

}


Graphe::~Graphe() {}

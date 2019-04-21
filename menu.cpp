#include "menu.h"
#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

/**
 * \file          graphe.cpp
 * \author    TD2 groupe 6
 * \date       21/04/2019
 * \brief       interface sur la console
 *
 * \details    cette partie du code permet aux utilisateurs de choisir se qu'ils souhaite faire afficher sur la console, sous forme d'interface intéractive
*/


/**
 * \brief       interface principale entre l'utilisateur et la console
 * \details     interface principale entre l'utilisateur et la console, permet aux personnes de faire leur choix pour l'execution d'une partie du code
 *
 * \param     on ne prend rien en paramètre
 * \return    on ne return aucune donnee
 *
 */
//affichage du menu
void menu()
{
    std::cout<<"\n            Les bycyclettes de Triville\n    Optimisation multi-objectif et circulation douce\n\n   By Pierre Buteaux & Camille Eung & Antoine Lambert\n\n\n"<<std::endl;

    int choix=-1;
    do
    {
        choix=interface_principale();
        system("cls");
        switch(choix)
        {
        case 1:
        {
            ///affichage du graphe normal et sur un autre svg j'affiche le kruscal
            Svgfile svgout;
            system("cls");
            int choix1;
            choix1=choix_kruskal_fonction();
            switch(choix1)
            {
            case 1:
            {
                system("cls");
                std::cout<<"Vous aviez choisi de faire un Kruskal\n"<<std::endl;
                std::string name_graphe;
                std::string name_poids;
                afficher_graphe(name_graphe,name_poids,&svgout);
                break;
            }

            case 2 :
            {
                system("cls");
                int choix;
                std::cout<<"Vous aviez choisi de faire un Kruskal\nVeuillez saisir le nom du fichier_graphe"<<std::endl;
                std::string name_graphe;
                std::cin>>name_graphe;
                Graphe a(name_graphe);
                std::cout<<"Veuillez saisir le nom du fichier_poids"<<std::endl;
                std::string name_poids;
                std::cin>>name_poids;
                a.ponderation(name_poids);
                choix = choix_kruskal();
                a.kruskal(choix,&svgout);
                break;
            }
            }
            break;

        }
        case 2:
        {
            ///affichage du graphe normal et sur un autre svg j'affiche le kruscal
            Svgfile svgout;
            system("cls");
            int choix1;
            choix1=choix_pareto_fonction();

            switch(choix1)
            {
            case 1:
            {
                system("cls");
                std::cout<<"Vous aviez choisi de faire un Pareto\n"<<std::endl;
                std::string name_graphe;
                std::string name_poids;
                afficher_graphe(name_graphe,name_poids,&svgout);
                break;
            }
            case 2 :
            {
                system("cls");
                std::cout<<"Vous aviez choisi de faire un Pareto\nVeuillez saisir le nom du fichier_graphe"<<std::endl;
                std::string name_graphe;
                std::cin>>name_graphe;
                Graphe a(name_graphe);
                std::cout<<"Veuillez saisir le nom du fichier_poids"<<std::endl;
                std::string name_poids;
                std::cin>>name_poids;
                a.ponderation(name_poids);
                a.pareto(&svgout);
                break;
            }
            }
            break;
        }
        case 3:
        {
            system("cls");
            std::cout<<"Vous aviez choisi de faire un disjktra\n"<<std::endl;
            break;
        }
        case 4:
        {
            system("cls");
            std::cout<<"Vous venez de quitter l'application !\n Bye Bye !\n"<<std::endl;
            break;
        }
        }
    }
    while (choix==1 || choix==2 || choix==3);

}


/**
 * \brief       première interface avec l'utilisateur
 * \details     l'utilisateur va pourvoir choisir de faire un kruskal, un pareto, un dijktra ou quitter l'application
 *
 * \param     on ne prend rien en paramètre
 * \return    on  return le choix de l'utilisateur
 *
 */
//interface de depart, choisir ce qu'on souhaite faire
int interface_principale()
{
    int choix;
    do
    {
        std::cout<<"Que souhaitez vous effectuer? (Entrer le numéro de votre choix)\n1. Faire un Kruscal\n2. Faire un Pareto\n3. Faire un Dijktra\n4. Quitter"<<std::endl;
        std::cin>>choix;
    }
    while (choix<0 && choix>4);
    return choix;
}


/**
 * \brief       choix du poids de Kruskal
 * \details     l'utilisateur va pourvoir choisir de faire un kruskal, selon le poids de son choix
 *
 * \param     on ne prend rien en paramètre
 * \return    on return le choix de l'utilisateur
 *
 */
//choisir entre le poids 1 et 2 de kruskal
int choix_kruskal()
{
    int choix;
    do
    {
        std::cout<<"Choisir sur quel poids vous voulez le kruskal (entrer le numero)\n0. poids 1\n1. poids 2\n"<<std::endl;
        std::cin>>choix;

    }
    while(choix<0 || choix>1);
    return choix;
}


/**
 * \brief       saisir le nom du graphe et le poids qu'on souhaite
 * \details     l'utilisateur va pourvoir choisir de faire le graphe qu'il souhaite utiliser
 *
 * \param     std::string name_graphe       permet d'entrer le nom du gaphe avec les positions des sommets
 * \param     std::string name_poids        permet d'entrer le nom du fichier poids des aretes
 * \param     Svgfile *ecran3               permet de renvoyer sur le output le graphe
 * \return    on ne return rien
 *
 */
//récuperer les fichiers texte a lire
void afficher_graphe(std::string name_graphe,std::string name_poids,Svgfile *ecran3)
{
    std::cout<<"Veuillez saisir le nom du fichier_graphe"<<std::endl;
    std::cin>>name_graphe;
    Graphe a(name_graphe);
    std::cout<<"Veuillez saisir le nom du fichier_poids"<<std::endl;
    std::cin>>name_poids;
    a.ponderation(name_poids);
    a.affichage(ecran3);
    std::cout<<"Affichage du graphe sur svgout reussi"<<std::endl;
}

/**
 * \brief       choix de la fonction dans Kruskal
 * \details     l'utilisateur va pourvoir choisir de faire un kruskal, ou d'fficher le graphe de depart
 *
 * \param     on ne prend rien en paramètre
 * \return    on return le choix de l'utilisateur
 *
 */
//faire le choix entre affichage di graphe de deparx VS graphe qui a subi kruskal
int choix_kruskal_fonction()
{
    int choix1;
    do
    {
        std::cout<<"Que souhaitez vous afficher?\n1. Graphe de départ\n2. Afficher Kruskal\n"<<std::endl;
        std::cin>>choix1;
    }
    while (choix1<1 ||choix1>2);
    return choix1;
}

/**
 * \brief       choix de la fonction via pareto
 * \details     l'utilisateur va pourvoir choisir de faire un pareto ou afficher le graphe de depart
 *
 * \param     on ne prend rien en paramètre
 * \return    on return le choix de l'utilisateur
 *
 */
//faire le choix entre affichage di graphe de deparx VS graphe qui a subi pareto
int choix_pareto_fonction()
{
    int choix1;
    do
    {
        std::cout<<"Que souhaitez vous afficher?\n1. Graphe de depart\n2. Afficher Pareto\n"<<std::endl;
        std::cin>>choix1;
    }
    while (choix1<1 ||choix1>2);
    return choix1;
}

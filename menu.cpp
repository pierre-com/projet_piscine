#include "menu.h"
#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

//affichage du menu
void menu()
{
    std::cout<<"\n            Les bycyclettes de Triville\n    Optimisation multi-objectif et circulation douce\n\n   By Pierre Buteaux & Camille Eung & Antoine Lambert\n\n\n"<<std::endl;

    int choix=-1;
    do
    {
        choix=interface_principale();
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
                break;
            }
            break;
            }
        }
        case 3:
        {
            system("cls");
            std::cout<<"Vous venez de quitter l'application !\n Bye Bye !\n"<<std::endl;
            break;
        }
        }
    }
    while (choix==1 || choix==2);

}



//interface de depart, choisir ce qu'on souhaite faire
int interface_principale()
{
    int choix;
    do
    {
        std::cout<<"Que souhaitez vous effectuer? (Entrer le numéro de votre choix)\n1. Faire un Kruscal\n2. Faire un Pareto"<<std::endl;
        std::cout<<"3. Quitter"<<std::endl;
        std::cin>>choix;
    }
    while (choix<0 && choix>3);
    return choix;
}

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

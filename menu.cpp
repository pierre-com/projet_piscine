#include "menu.h"
#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>


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
            std::cout<<"Vous aviez choisi de faire un Kruscal\nVeuillez saisir le nom du fichier_graphe"<<std::endl;
            std::string name_graphe;
            std::cin>>name_graphe;
            Graphe a(name_graphe);
            std::cout<<"Veuillez saisir le nom du fichier_poids"<<std::endl;
            std::string name_poids;
            std::cin>>name_poids;
            a.ponderation(name_poids);
            a.affichage(&svgout);
            std::cout<<"Affichage de Kruscal effectue et reussi"<<std::endl;
            system("cls");
            break;

        }
        case 2:
            {
                system("cls");
                break;


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

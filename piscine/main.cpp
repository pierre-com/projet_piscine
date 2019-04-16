#include <iostream>
#include "svgfile.h"
#include "graphe.h"
#include <string>

int main()
{


    Svgfile svgout;
    Graphe a("broadway.txt");
    //std::cout<<"fichier 1 ouvert"<<std::endl;
    a.ponderation("broadway_weights_0.txt");
    //std::cout<<"fichier 2 ouvert"<<std::endl;

    a.affichage(&svgout);

//Svgfile svgout;
    // a.affichage_graphe_1();
    //svgout.addDisk(100, 100, 90, "greyball");
    //svgout.addText(300, 300, "25;12", "green");
    return 0;
}

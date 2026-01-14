#include<iostream>
#include"pixel.h"
#include"graphe.h"
#include<string.h>

using namespace std;

int main()
{
    srand(time(NULL));
    Pixel p;
    p.test_fonctionement_pixel();
    
    Graph g(2,2);
    g.test_graphe();
    Graph gr;
    gr.charger_image("data/baboon.png");
    gr.binariser_image();
    gr.sauvegarder_image("data/baboon.bin.png");
    
    return 0;
}
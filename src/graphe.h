#ifndef GRAPHE_
#define GRAPHE_


const double alpha = 1;
const double gamma = 50;
const int H = 100;

#include "pixel.h"
#include<string.h>

class Graph
{
    private:
        unsigned int hauteur;
        unsigned int largeur;
        Pixel *image = nullptr; 

        enum Direction { OUEST, EST, NORD, SUD, SOURCE, PUIT, AUCUN };

        struct Noeud 
        {
            int predecesseur;    
            Direction direction; 
            bool visite;    
            Noeud() : predecesseur(-1), direction(AUCUN), visite(false) {}     
        };

    public:
        //Constructeur - Destructeur
        Graph();
        Graph(unsigned int h, unsigned int l);
        ~Graph();

        //Fonctions g_v [entiers x y ] - traduit les coordonnes de tableau 2D dans la coordonne 1D
        unsigned int g_v(unsigned int x, unsigned int y);

        //Pour récupérer les coodronnais voisins:
        unsigned int get_nord(Pixel &p);
        unsigned int get_sud(Pixel &p);
        unsigned int get_est(Pixel &p);
        unsigned int get_ouest(Pixel &p);

        //procedure calculer_capacites_pixel_avec_des_voisins [pixel p] - prend le pixel en parametres 
        //et calcule les capacites de ce pixel avec des voisins s`ils existent
        void calculer_capacites_pixel_avec_des_voisins(Pixel &p);

        //fonction calculer_capacite_entre_deux_pixels [pixel p1, p2] - prend en parametres deux pixels
        //et return le capacite entre les deux
        unsigned int calculer_capacite_entre_deux_pixels(Pixel &p1, Pixel &p2);

        //procedure remplir_capacite_image - remplis les valeurs de capacite de voisins dans toutes 
        //les pixels d`image
        void remplir_capacite_image();

        //procedure affichage - affiche les donnes de image
        void afficher();

        //procedure charger_image [const char * nom_i] - ouvre l`image et le reecrit dans le mode de classe 
        void charger_image(const char * nom_i);
        //procedure sauvegarder_image [const char * nom_i] - souvgarde les changement de l`image
        void sauvegarder_image(const char * nom_i);


        void changer_couleur_pixel(unsigned int x , unsigned int y, unsigned char col);
        //procedure test_graphe - test les fonctions et procedures de class
        void test_graphe();

        bool trouver_chemin_non_sature(int& capacite_minimale ,Noeud* bfs_info , int * file);

        int calculer_capacite_minimale_chemin(Noeud* bfs_info, int puit_index);
        
        std::string direction_vers_chaine(Direction dir);

        //finction calculer_capacite_source_vers_pixel[puit] [pixel p] - prend en parametres un pixel, calcule et return le puit de ce pixel
        unsigned int calculer_capacite_source_vers_pixel(Pixel &p);
        unsigned int calculer_capacite_pixel_vers_puit(Pixel &p);

        
        void calculer_flot_maximal(Noeud* bfs_info , int* file);
       
        void binariser_image();

       
        void changeer_les_capasites_par_min(Noeud* bfs_info, int puit_index , int cap_min);

};

#endif
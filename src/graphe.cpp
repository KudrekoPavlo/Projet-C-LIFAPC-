#include<iostream>
#include<math.h>
#include "graphe.h"
#include <cmath>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include<fstream>
#include "lodepng.h"


using namespace std;
Graph::Graph()
{
}
Graph::Graph(unsigned int h, unsigned int l)
{
    largeur = l;
    hauteur = h;
    image = new Pixel [largeur*hauteur];
}

Graph::~Graph()
{
    if(image != nullptr)
    {
        delete [] image;
    }
}

unsigned int  Graph::g_v(unsigned int x, unsigned int y)
{   
    return y*largeur+x;
}

unsigned int Graph::get_nord(Pixel &p)
{
    unsigned int x = p.return_x();
    unsigned int y = p.donner_nord();
    return g_v(x,y); 
}

unsigned int Graph::get_sud(Pixel &p)
{
    unsigned int x = p.return_x();
    unsigned int y = p.donner_sud();
    return g_v(x,y); 
}

unsigned int Graph::get_est(Pixel &p)
{
    unsigned int x = p.donner_est();
    unsigned int y = p.return_y();
    return g_v(x,y); 
}

unsigned int Graph::get_ouest(Pixel &p)
{
    unsigned int x = p.donner_ouest();
    unsigned int y = p.return_y();
    return g_v(x,y); 
}

unsigned int Graph::calculer_capacite_entre_deux_pixels(Pixel &p1, Pixel &p2)
{
    double diff = p1.return_color() - p2.return_color();
    double valeur = exp(- pow(diff,2) / (2 * pow(gamma,2)));

    return (unsigned int)std::lround(valeur * H);
}


void Graph::calculer_capacites_pixel_avec_des_voisins(Pixel &p)
{
   unsigned int tab[4] = {0, 0, 0, 0};
    
    if(p.return_x() > 0)
    {
        Pixel& p_ouest = image[get_ouest(p)]; 
        tab[0] = calculer_capacite_entre_deux_pixels(p, p_ouest);
    }
    
    if(p.return_x() < largeur - 1)
    {
        Pixel& p_est = image[get_est(p)]; 
        tab[1] = calculer_capacite_entre_deux_pixels(p, p_est);
    }
    
    if(p.return_y() > 0)
    {
        Pixel& p_nord = image[get_nord(p)]; 
        tab[2] = calculer_capacite_entre_deux_pixels(p, p_nord);
    }
    
    if(p.return_y() < hauteur - 1)
    {
        Pixel& p_sud = image[get_sud(p)]; 
        tab[3] = calculer_capacite_entre_deux_pixels(p, p_sud);
    }

    p.changer_capacite_source(calculer_capacite_source_vers_pixel(p));
    p.changer_capacite_puit(calculer_capacite_pixel_vers_puit(p));
    p.remplir_capacite(tab[0], tab[1], tab[2], tab[3]);

}


void Graph::remplir_capacite_image()
{
    for(unsigned int i = 0; i < hauteur;i++)
    {
        for(unsigned int j =0;j < largeur; j++)
        {
            calculer_capacites_pixel_avec_des_voisins(image[g_v(j,i)]);
        }
    }
}


void Graph::afficher()
{
    for(unsigned int i = 0; i < hauteur;i++)
    {
        for(unsigned int j =0;j < largeur; j++)
        {
            cout << "col : "<< image[g_v(j,i)].return_color()<< " [c_ou:  "<<image[g_v(j,i)].donner_capacite_ouest()<< " c_e: " << image[g_v(j,i)].donner_capacite_est();
            cout << " c_n: " << image[g_v(j,i)].donner_capacite_nord()<<" c_s: "<<image[g_v(j,i)].donner_capacite_sud()<<"] | ";
        }
        cout<< endl;
    }
    cout << endl;
}



void Graph::test_graphe()
{
    
    cout<< endl<< "FONCTION TEST GRAPHE EST LANCE "<< endl<<endl;
    unsigned char x; 
    //remplissage de pixels avec x y et couleur
    for(unsigned int i = 0; i < hauteur;i++)
    {
        for(unsigned int j = 0;j < largeur; j++)
        {
            x = rand()%256;
            image[g_v(j,i)].refair_pixel(j ,i , x);
            image[g_v(j,i)].afficher_donnes_pixel();
        }
    }

    afficher();

    //remplissage de pixels avec des capacites
    remplir_capacite_image();
    this->remplir_capacite_image();
    //calculer_capacites_pixel_avec_des_voisins(image[g_v(largeur-1,hauteur-1)]);
    afficher();
    

}



void Graph::charger_image(const char * nom_i)
{
    std::vector<unsigned char> png;
    std::vector<unsigned char> image_raw;

    unsigned new_width, new_height;

    unsigned error = lodepng::load_file(png, nom_i);
    if (error)
    {
        std::cout << "ERROR: impossible de lire fichier PNG : "<< lodepng_error_text(error) << std::endl;
        exit(1);
    }

    error = lodepng::decode(image_raw, new_width, new_height, png, LCT_GREY, 8);
    if (error)
    {
        std::cout << "ERROR: PNG decode : "<< lodepng_error_text(error) << std::endl;
        exit(1);
    }

    largeur = new_width;
    hauteur = new_height;

    if (image != nullptr)
    {
        delete[] image;
    }

    image = new Pixel[largeur * hauteur];

    for(unsigned y = 0; y < hauteur; y++)
    {
        for(unsigned x = 0; x < largeur; x++)
        {
            unsigned char I = image_raw[y * largeur + x];
            image[g_v(x,y)].refair_pixel(x, y, I);
        }
    }

    std::cout << "PNG charge : " << largeur << "x" << hauteur << std::endl;

    remplir_capacite_image();
}


void Graph::sauvegarder_image(const char * nom_i)
{
    std::vector<unsigned char> image_raw(largeur * hauteur);

    for(unsigned y = 0; y < hauteur; y++)
    {
        for(unsigned x = 0; x < largeur; x++)
        {
            image_raw[y * largeur + x] = image[g_v(x,y)].return_color();
        }
    }

    std::vector<unsigned char> png;

    unsigned error = lodepng::encode(png, image_raw, largeur, hauteur, LCT_GREY, 8);

    if (error)
    {
        std::cout << "Erreur encode PNG : "
                  << lodepng_error_text(error) << std::endl;
        exit(1);
    }

    lodepng::save_file(png, nom_i);

    std::cout << "PNG sauvegarde : " << nom_i << std::endl;
}


void Graph::changer_couleur_pixel(unsigned int x , unsigned int y, unsigned char col)
{
    if(x >= largeur || y >= hauteur)
    {
        cout << "pixel ("<<x<<","<<y<<") - n`appartient pas a cette image" << endl;
        return;
    }else
    {
        image[g_v(x,y)].remplir_couleur_pixel(col);
    }
}

int Graph::calculer_capacite_minimale_chemin(Noeud* bfs_info, int puit_index)
{
    int capacite_minimale = 1000000; 
    int courant = puit_index;
        
    // Parcourir le chemin a l'envers du puit a la source
    while(bfs_info[courant].predecesseur != -1)
    {
        int precedent = bfs_info[courant].predecesseur;
        Direction dir = bfs_info[courant].direction;
        int res= 0;
        
        if(precedent == largeur * hauteur)
        {
            //S -> Pixel
            Pixel& p = image[courant];
            res = calculer_capacite_source_vers_pixel(p) - p.donner_flot_source();
        }
        else if(courant == largeur * hauteur + 1)
        {
            //Pixel -> P
            Pixel& p = image[precedent];
            res = calculer_capacite_pixel_vers_puit(p) - p.donner_flot_puit();
        }
        else
        {
            //Pixel ->P
            Pixel& from = image[precedent];
            Pixel& to = image[courant];
            
            switch(dir)
            {
                case OUEST:
                    res = from.donner_capacite_ouest() - from.donner_flot_ouest() + to.donner_flot_est();
                    break;
                case EST:
                    res = from.donner_capacite_est() - from.donner_flot_est() + to.donner_flot_ouest();
                    break;
                case NORD:
                    res = from.donner_capacite_nord() - from.donner_flot_nord() + to.donner_flot_sud();
                    break;
                case SUD:
                    res = from.donner_capacite_sud() - from.donner_flot_sud() + to.donner_flot_nord();
                    break;
            }
        }
        
        if(res < capacite_minimale)
        {
            capacite_minimale = res;
        }
        
        courant = precedent;
    }
    
    return capacite_minimale;
}

void Graph::changeer_les_capasites_par_min(Noeud* bfs_info, int puit_index , int cap_min)
{
    int courant = puit_index;

   while(bfs_info[courant].predecesseur != -1)
    {
        int precedent = bfs_info[courant].predecesseur;
        Direction dir = bfs_info[courant].direction;
        
        if(precedent == largeur * hauteur)
        {
            //S -> Pixel
            Pixel& p = image[courant];
            p.changer_flot_source(p.donner_flot_source() + cap_min);
        }
        else if(courant == largeur * hauteur + 1)
        {
            //Pixel -> P
            Pixel& p = image[precedent];
            p.changer_flot_puit(p.donner_flot_puit() + cap_min);

        }
        else
        {
            //Pixel ->P
            Pixel& from = image[precedent];
            Pixel& to = image[courant];
            
            switch(dir)
            {
                case OUEST:
                    from.changer_flot_ouest(from.donner_flot_ouest() + cap_min);
                    if((from.donner_flot_ouest() + cap_min - from.donner_capacite_ouest())>0)
                    {
                        to.changer_flot_est(to.donner_flot_est() - (from.donner_flot_ouest() + cap_min - from.donner_capacite_ouest()));
                    }
                    break;
                case EST:
                    from.changer_flot_est(from.donner_flot_est() + cap_min);
                    if((from.donner_flot_est() + cap_min - from.donner_capacite_est())>0)
                    {
                        to.changer_flot_ouest(to.donner_flot_ouest() - (from.donner_flot_est() + cap_min - from.donner_capacite_est()));
                    }
                    break;
                case NORD:
                    from.changer_flot_nord(from.donner_flot_nord() + cap_min);
                    if((from.donner_flot_nord() + cap_min - from.donner_capacite_nord())>0)
                    {
                        to.changer_flot_sud(to.donner_flot_sud() - (from.donner_flot_nord() + cap_min - from.donner_capacite_nord()));
                    }                    break;
                case SUD:
                    from.changer_flot_sud(from.donner_flot_sud() + cap_min);
                    if((from.donner_flot_sud() + cap_min - from.donner_capacite_sud())>0)
                    {
                        to.changer_flot_nord(to.donner_flot_nord() - (from.donner_flot_sud() + cap_min - from.donner_capacite_sud()));
                    }                    break;
            }
        }
        
        courant = precedent;
    } 
}


unsigned int Graph::calculer_capacite_source_vers_pixel(Pixel &p) 
{
    double col = (double)p.return_color();
    if (col <= 0.0) return alpha * 20;
    double valeur = -alpha * log((0.0000000001 + col) / 255.0000000002);
    if (valeur < 0)
    {
        valeur = 0;
    }
    return (unsigned int)std::round(valeur);
}

unsigned int Graph::calculer_capacite_pixel_vers_puit(Pixel &p)
{
    double col = (double)p.return_color();
    if (col >= 255.0) return alpha * 20;
    double valeur = -alpha * log((255.0000000001 - col) / 255.0000000002);
    if (valeur < 0)
    {
        valeur = 0;
    }
    return (unsigned int)std::round(valeur);
}



bool Graph::trouver_chemin_non_sature(int& capacite_minimale , Noeud* info , int* file ) 
{

    int N = largeur * hauteur;
    int source = N;
    int puit = N + 1;

    
    int debut = 0, fin = 0;

    file[debut++] = source;
    info[source].visite = true;

    bool trouve = false;

    while (fin < debut)
    {
        int u = file[fin++];

        if (u == puit) 
        { 
            trouve = true; 
            break; 
        }

        //src->pix
        if (u == source)
        {
            for (int i = 0; i < N; i++)
            {
                Pixel &p = image[i];

                unsigned int cap = p.donner_capacite_source() - p.donner_flot_source();
                if (cap > 0 && !info[i].visite)
                {
                    info[i].visite = true;
                    info[i].predecesseur = u;
                    info[i].direction = SOURCE;

                    file[debut++] = i;
                }
            }
            continue;
        }

        //pix->pix
        if (u < N)
        {
            Pixel &p = image[u];

            int x = p.return_x();
            int y = p.return_y();

            //ouest
            if (x > 0)
            {
                int v = get_ouest(p);
                Pixel &q = image[v];

                
                unsigned int cap_fwd = p.donner_capacite_ouest() - p.donner_flot_ouest();
                if (cap_fwd > 0 && !info[v].visite)
                {
                    info[v].visite = true;
                    info[v].predecesseur = u;
                    info[v].direction = OUEST;
                    file[debut++] = v;
                }

            }

            //est
            if (x < (int)largeur - 1)
            {
                int v = get_est(p);
                Pixel &q = image[v];

                unsigned int cap_fwd = p.donner_capacite_est() - p.donner_flot_est();
                if (cap_fwd > 0 && !info[v].visite)
                {
                    info[v].visite = true;
                    info[v].predecesseur = u;
                    info[v].direction = EST;
                    file[debut++] = v;
                }

            }

           //nord
            if (y > 0)
            {
                int v = get_nord(p);
                Pixel &q = image[v];

                unsigned int cap_fwd = p.donner_capacite_nord() - p.donner_flot_nord();
                if (cap_fwd > 0 && !info[v].visite)
                {
                    info[v].visite = true;
                    info[v].predecesseur = u;
                    info[v].direction = NORD;
                    file[debut++] = v;
                }

            }

           //sud
            if (y < (int)hauteur - 1)
            {
                int v = get_sud(p);
                Pixel &q = image[v];

                unsigned int cap_fwd = p.donner_capacite_sud() - p.donner_flot_sud();
                if (cap_fwd > 0 && !info[v].visite)
                {
                    info[v].visite = true;
                    info[v].predecesseur = u;
                    info[v].direction = SUD;
                    file[debut++] = v;
                }

            }

            //Pixel -> puit
            unsigned int capP = p.donner_capacite_puit() - p.donner_flot_puit();
            if (capP > 0 && !info[puit].visite)
            {
                info[puit].visite = true;
                info[puit].predecesseur = u;
                info[puit].direction = PUIT;

                file[debut++] = puit;
            }
        }
    }

    if (!trouve)
    {
        return false;
    }

    return true;

}



void Graph::calculer_flot_maximal(Noeud* info , int* file)
{

    int add = 0;

    while (trouver_chemin_non_sature(add, info, file))
    {
        int N = largeur * hauteur;
        int puit = N + 1;
        changeer_les_capasites_par_min(info,puit,calculer_capacite_minimale_chemin(info, puit));
    }
    
}


void Graph::binariser_image()
{    
    Noeud *info = new Noeud [hauteur*largeur +3];
    int* file = new int[largeur*hauteur +7];
    calculer_flot_maximal(info, file);
    
    for(int i = 0 ; i<hauteur; i++)
    {
        for(int j = 0; j < largeur ; j++)
        {
            int cor = g_v(j,i);
            if(info[cor].visite)
            {
                image[g_v(j,i)].remplir_couleur_pixel(0);
            }
            else
            {
               image[g_v(j,i)].remplir_couleur_pixel(255); 
            }
        }
    }

    delete [] info;
    delete [] file;
    
}



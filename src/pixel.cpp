#include<iostream>
#include"pixel.h"
#include<math.h>
using namespace std;


Pixel::Pixel()
{
    x = 1000;
    y = 1000;

    niveau_de_gris = 0;

    ouest = 0;
    est = 0;
    nord = 0;
    sud = 0;

    capacite_est = 0;
    capacite_nord = 0;
    capacite_ouest = 0;
    capacite_sud = 0;

    flot_est = 0;
    flot_nord = 0;
    flot_ouest = 0;
    flot_sud = 0;


    flot_source = 0;
    flot_puit = 0;
    capacite_source = 0;
    capacite_puit = 0;

}

Pixel::Pixel(unsigned int x1, unsigned int y1, unsigned char ndg)
{
    x = x1;
    y = y1;

    niveau_de_gris = ndg;
    
    flot_source = 0;
    flot_puit = 0;
    capacite_source = 0;
    capacite_puit = 0;

    this->remplir_voisins_pixel(x1,y1);
}

Pixel::~Pixel()
{
    //pas de pointeurs sur tas donc destr. ne fait rien
}

unsigned int Pixel::return_x()
{
    return x;
}

unsigned int Pixel::return_y()
{
    return y;
}

void Pixel::remplir_couleur_pixel(unsigned char ndg)
{
    niveau_de_gris = ndg;
}


void Pixel::remplir_voisins_pixel(unsigned int x ,unsigned int y)
{

        if(x-1>=0)
        {
            ouest = x - 1;
        }
        
        est = x + 1;
        
        if(y-1>=0)
        {
            nord = y - 1;
        }
        
        sud = y + 1;     
    
}


void Pixel::remplir_coordonnes(unsigned int x1 , unsigned int y1)
{
    x = x1; 
    y = y1;
    this->remplir_voisins_pixel(x,y);
}


void Pixel::refair_pixel(unsigned int x1 , unsigned int y1, unsigned char ndg)
{
    niveau_de_gris = ndg;
    this->remplir_coordonnes(x1, y1);
}

void Pixel::operator =(Pixel pix)
{
    niveau_de_gris = pix.niveau_de_gris;
    x = pix.x;
    y = pix.y;
    this->remplir_voisins_pixel(pix.x,pix.y);
}



bool Pixel::operator ==(Pixel pix)
{
    if(niveau_de_gris == pix.niveau_de_gris && x == pix.x && y == pix.y)
    {
        return true;
    }else
    {
        return false;
    }
}



bool Pixel::verifier_voisines(Pixel pix)
{
    if((x == pix.x && nord == pix.y) || (x == pix.x && sud == pix.y) || (ouest == pix.x && y == pix.y) || (est == pix.x && y == pix.y))
    {
        return true;
    }
    return false;
}



void Pixel::afficher_donnes_pixel()
{
    cout << "couleur: " << niveau_de_gris << "; x: " << x << "; y: "<< y << " voisins: ";
    cout <<"Nord(" << x << "," << nord <<") ";
    cout <<"Sud(" << x << "," << sud <<") ";
    cout <<"Est(" << est << "," << y <<") ";
    cout <<"Ouest(" << ouest << "," << y <<") "<<endl; 
}


void Pixel::remplir_capacite(unsigned int c_ou, unsigned int c_es, unsigned int c_no, unsigned int c_su)
{
    this -> changer_capacite_est(c_es);
    this -> changer_capacite_sud(c_su);
    this -> changer_capacite_nord(c_no);
    this -> changer_capacite_ouest(c_ou);
}



void Pixel::remplir_flot(unsigned int f_ou, unsigned int f_es, unsigned int f_no, unsigned int f_su)
{
    if(f_ou >= capacite_ouest || f_es >= capacite_est || f_no >= capacite_nord || f_su >= capacite_sud)
    {
        cout << "ERROR : une ou plusueur valeurs de flot >= capacite, processus de remplissage abandone" << endl;
    }
    else
    {
        this -> changer_flot_est(f_es);
        this -> changer_flot_sud(f_su);
        this -> changer_flot_nord(f_no);
        this -> changer_flot_ouest(f_ou);
    }
}



unsigned int Pixel::arc_capacite(Pixel p1)
{
    if(x == p1.x && y == p1.y)
    {

        cout << "ERROR : il n`y a pas de capacite entre le meme pixel" << endl << "Valeur retourne 0"<< endl;
        return 0;

    }else
    {

        if(this->verifier_voisines(p1))
        {
            //si nord
            if(x == p1.x && nord == p1.y)
            {
                return capacite_nord;
            }
            else
            {
                //si sud
                if(x == p1.x && sud == p1.y)
                {
                    return capacite_sud;
                }
                else
                {
                    //si ouest
                    if(ouest == p1.x && y == p1.y)
                    {
                        return capacite_ouest;
                    }
                    else
                    {
                        //si est
                        if(est == p1.x && y == p1.y)
                        {
                            return capacite_est;
                        }
                        else
                        {
                            //si error dans le code 
                            cout << "ERROR : fonction arc_capacite fonction mal, this->verifier_voisines(p1) = true mais pixel ne sont pas les voisins" << endl << "valeur retourne 0"<<endl;
                            return 0;
                        }
                    }
                }
            }


        }
        else
        {

            cout << "ERROR : les pixels choisis ne sont pas de voisins"<< endl << "Valeur retourne 0"<< endl; 
            return 0;

        }

    }
}


unsigned int Pixel::arc_flot(Pixel p1)
{
    if(x == p1.x && y == p1.y)
    {

        cout << "ERROR : il n`y a pas de flot entre le meme pixel" << endl << "Valeur retourne 0"<< endl;
        return 0;

    }else
    {

        if(this->verifier_voisines(p1))
        {
            //si nord
            if(x == p1.x && nord == p1.y)
            {
                return flot_nord;
            }
            else
            {
                //si sud
                if(x == p1.x && sud == p1.y)
                {
                    return flot_sud;
                }
                else
                {
                    //si ouest
                    if(ouest == p1.x && y == p1.y)
                    {
                        return flot_ouest;
                    }
                    else
                    {
                        //si est
                        if(est == p1.x && y == p1.y)
                        {
                            return flot_est;
                        }
                        else
                        {
                            //si error dans le code 
                            cout << "ERROR : fonction arc_flot fonction mal, this->verifier_voisines(p1) = true mais pixel ne sont pas les voisins" << endl << "valeur retourne 0"<<endl;
                            return 0;
                        }
                    }
                }
            }


        }
        else
        {

            cout << "ERROR : les pixels choisis ne sont pas de voisins"<< endl << "Valeur retourne 0"<< endl; 
            return 0;

        }

    }
}


unsigned char Pixel::return_color()
{
    return niveau_de_gris;
}

void Pixel::test_fonctionement_pixel()
{
    Pixel p1;
    Pixel p2(10,11,124);
    cout << "p1 ";
    p1.afficher_donnes_pixel();
    cout << "p2 ";
    p2.afficher_donnes_pixel();

    p1.remplir_couleur_pixel(224);
    cout << "p1 changer couleur ";
    p1.afficher_donnes_pixel();
    p1.remplir_coordonnes(10,12);
    cout << "p1 ajouter coordonnes ";
    p1.afficher_donnes_pixel();

    p1.refair_pixel(44,43,11);
    cout << "p1 pixel refait ";
    p1.afficher_donnes_pixel();

    Pixel p3;
    p3 = p2;
    if(p3 == p2)
    {
        p3.afficher_donnes_pixel();
    }
    p3.refair_pixel(10,10,192);
    cout << "p3 change  " ;
    p3.afficher_donnes_pixel();
    if(p3.verifier_voisines(p2))
    {
        cout << "p1 et p2 voisins" << endl;
        p3.remplir_capacite(1,2,3,4);
        p2.remplir_capacite(2,2,4,4);
        cout << "arc_capacite entre meme pixel p3(10.10) " <<endl<<  p3.arc_capacite(p3) << endl;
        cout << "arc_capacite entre p3(10.10) et p2(10.11) est : " << p3.arc_capacite(p2) << endl;
        p3.remplir_flot(1,2,3,1);
        p2.remplir_flot(2,3,1,1);
        cout << "arc_flot entre p3(10.10) et p2(10.11) est : " << p3.arc_flot(p2) << endl;

    }
}



void Pixel::changer_capacite_ouest(unsigned int cap_ou)
{
    capacite_ouest = cap_ou;
}

void Pixel::changer_capacite_est(unsigned int cap_es)
{
    capacite_est = cap_es;
}

void Pixel::changer_capacite_nord(unsigned int cap_no)
{
    capacite_nord = cap_no;
}

void Pixel::changer_capacite_sud(unsigned int cap_su)
{
    capacite_sud = cap_su;
}




void Pixel::changer_flot_ouest(unsigned int flot_ou)
{
    flot_ouest = flot_ou;
}

void Pixel::changer_flot_est(unsigned int flot_es)
{
    flot_est = flot_es;
}

void Pixel::changer_flot_nord(unsigned int flot_no)
{
    flot_nord = flot_no;
}

void Pixel::changer_flot_sud(unsigned int flot_su)
{
    flot_sud = flot_su;
}



unsigned int Pixel::donner_flot_ouest()
{
    return flot_ouest;
}

unsigned int Pixel::donner_flot_est()
{
    return flot_est;
}

unsigned int Pixel::donner_flot_nord()
{
    return flot_nord;
}

unsigned int Pixel::donner_flot_sud()
{
    return flot_sud;
}


unsigned int Pixel::donner_capacite_ouest()
{
    return capacite_ouest;
}
unsigned int Pixel::donner_capacite_est()
{
    return capacite_est;
}
unsigned int Pixel::donner_capacite_nord()
{
    return capacite_nord;
}
unsigned int Pixel::donner_capacite_sud()
{
    return capacite_sud;
}



unsigned int Pixel::arc_capacite(Pixel *p1)
{
    if(x == p1->x && y == p1->y)
    {

        cout << "ERROR : il n`y a pas de capacite entre le meme pixel" << endl << "Valeur retourne 0"<< endl;
        return 0;

    }else
    {

        if(this->verifier_voisines(p1))
        {
            //si nord
            if(x == p1->x && nord == p1->y)
            {
                return capacite_nord;
            }
            else
            {
                //si sud
                if(x == p1->x && sud == p1->y)
                {
                    return capacite_sud;
                }
                else
                {
                    //si ouest
                    if(ouest == p1->x && y == p1->y)
                    {
                        return capacite_ouest;
                    }
                    else
                    {
                        //si est
                        if(est == p1->x && y == p1->y)
                        {
                            return capacite_est;
                        }
                        else
                        {
                            //si error dans le code 
                            cout << "ERROR : fonction arc_capacite fonction mal, this->verifier_voisines(p1) = true mais pixel ne sont pas les voisins" << endl << "valeur retourne 0"<<endl;
                            return 0;
                        }
                    }
                }
            }


        }
        else
        {

            cout << "ERROR : les pixels choisis ne sont pas de voisins"<< endl << "Valeur retourne 0"<< endl; 
            return 0;

        }

    }
}


unsigned int Pixel::arc_flot (Pixel *p1)
{
    if(x == p1->x && y == p1->y)
    {

        cout << "ERROR : il n`y a pas de flot entre le meme pixel" << endl << "Valeur retourne 0"<< endl;
        return 0;

    }else
    {

        if(this->verifier_voisines(p1))
        {
            //si nord
            if(x == p1->x && nord == p1->y)
            {
                return flot_nord;
            }
            else
            {
                //si sud
                if(x == p1->x && sud == p1->y)
                {
                    return flot_sud;
                }
                else
                {
                    //si ouest
                    if(ouest == p1->x && y == p1->y)
                    {
                        return flot_ouest;
                    }
                    else
                    {
                        //si est
                        if(est == p1->x && y == p1->y)
                        {
                            return flot_est;
                        }
                        else
                        {
                            //si error dans le code 
                            cout << "ERROR : fonction arc_flot fonction mal, this->verifier_voisines(p1) = true mais pixel ne sont pas les voisins" << endl << "valeur retourne 0"<<endl;
                            return 0;
                        }
                    }
                }
            }


        }
        else
        {

            cout << "ERROR : les pixels choisis ne sont pas de voisins"<< endl << "Valeur retourne 0"<< endl; 
            return 0;

        }

    }
}


bool Pixel::verifier_voisines(Pixel *pix)
{
    if((x == pix->x && nord == pix->y) || (x == pix->x && sud == pix->y) || (ouest == pix->x && y == pix->y) || (est == pix->x && y == pix->y))
    {
        return true;
    }
    return false;
}


bool Pixel::operator ==(Pixel *pix)
{
    if(niveau_de_gris == pix->niveau_de_gris && x == pix->x && y == pix->y)
    {
        return true;
    }else
    {
        return false;
    }
}


void Pixel::operator =(Pixel *pix)
{
    niveau_de_gris = pix->niveau_de_gris;
    x = pix->x;
    y = pix->y;
    this->remplir_voisins_pixel(pix->x, pix->y);
}

unsigned int Pixel::donner_ouest()
{
    return ouest;
}

unsigned int Pixel::donner_est()
{
    return est;
}

unsigned int Pixel::donner_nord()
{
    return nord;
}

unsigned int Pixel::donner_sud()
{
    return sud;
}


void Pixel::changer_flot_source(unsigned int flot_s) 
{
    flot_source = flot_s;
}

void Pixel::changer_flot_puit(unsigned int flot_p) 
{
    flot_puit = flot_p;
}

unsigned int Pixel::donner_flot_source() 
{
    return flot_source;
}

unsigned int Pixel::donner_flot_puit() {
    return flot_puit;
}

void Pixel::changer_capacite_source( int cap_s) 
{
    capacite_source = cap_s;
}

void Pixel::changer_capacite_puit( int cap_p) 
{
    capacite_puit = cap_p;
}

unsigned int Pixel::donner_capacite_source() 
{
    return capacite_source;
}

unsigned int Pixel::donner_capacite_puit() 
{
    return capacite_puit;
}
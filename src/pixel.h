#ifndef Pixel_
#define Pixel_


class Pixel
{
    private:

    //couleur de pixel
    unsigned char niveau_de_gris;

    //cordonnais de pixel
    unsigned int x;
    unsigned int y;


    // les valeurs de voisins
    unsigned int ouest;
    unsigned int capacite_ouest;
    unsigned int flot_ouest;


    unsigned int est;
    unsigned int capacite_est;
    unsigned int flot_est;

    unsigned int nord;
    unsigned int capacite_nord;
    unsigned int flot_nord;

    unsigned int sud;
    unsigned int capacite_sud;
    unsigned int flot_sud;

    unsigned int flot_source;   
    unsigned int flot_puit;     
 
    unsigned int capacite_source; 
    unsigned int capacite_puit;   

    public:

    //Constructeur par defaut toutes les voisins sont -1 et les 
    //valeus de couleur mets en 0
    Pixel();

    //Constructeur par recopie, prend en parametres les valeurs de 
    //niveau_de_gris, ouest, est, nord, sud 
    Pixel(unsigned int x, unsigned int y, unsigned char ndg);

    //Destructeur par desaut
    ~Pixel();

    //procedure remplir_Pixel [entier bdg] - prend en parametre le 
    //niveau de gris et remplit la valeur dans Pixel 
    void remplir_couleur_pixel(unsigned char ndg);

    // procedure remplir_voisins_Pixel [entiers posotoves ou , es, no ,su]
    //remplit les voisinages de Pixel
    void remplir_voisins_pixel(unsigned int x ,unsigned int y);  

    //fonctions donner_ouest[est,sud,nord] - return les coordonnes de voisins
    unsigned int donner_ouest();
    unsigned int donner_est();
    unsigned int donner_nord();
    unsigned int donner_sud();

    //fonction return_color - return la valeur de niveau de gris de pixel appelent
    unsigned char return_color();

    //Procedure deconstruir_Pixel  - remplit les couleurs et des voisins de 
    void refair_pixel( unsigned int x1 , unsigned int y1, unsigned char ndg);

    // procedure remplir_coordonnes [entiers x y ] - identifie la place 
    //de Pixel dans la grille 
    void remplir_coordonnes(unsigned int x1 , unsigned int y1);

    // Operator =
    void operator =(Pixel pix);
    void operator =(Pixel *pix);
    //Operator == return true si deux Pixels sont egaux
    bool operator ==(Pixel pix);
    bool operator ==(Pixel *pix);

    //return true si les deux pixels sont des voisins 
    bool verifier_voisines(Pixel pix);
    bool verifier_voisines(Pixel *pix);

    //procedudes de changement des capacites
    void changer_capacite_ouest(unsigned int cap_ou);
    void changer_capacite_est(unsigned int cap_es);
    void changer_capacite_nord(unsigned int cap_no);
    void changer_capacite_sud(unsigned int cap_su);

    //procedudes de changement des flots
    void changer_flot_ouest(unsigned int flot_ou);
    void changer_flot_est(unsigned int flot_es);
    void changer_flot_nord(unsigned int flot_no);
    void changer_flot_sud(unsigned int flot_su);

    //fonctions qui return les flots de deux voisins 
    unsigned int donner_flot_ouest();
    unsigned int donner_flot_est();
    unsigned int donner_flot_nord();
    unsigned int donner_flot_sud();

    //fonctions qui return les flots de deux voisins 
    unsigned int donner_capacite_ouest();
    unsigned int donner_capacite_est();
    unsigned int donner_capacite_nord();
    unsigned int donner_capacite_sud();

    //remplir_capacite [entiers c_ou c_es c_no c_su] - remplit les capacites avec des voisinages
    void remplir_capacite(unsigned int c_ou, unsigned int c_es, unsigned int c_no, unsigned int c_su); 

    //remplir_flot [entiers f_ou f_es f_no f_su] - remplit les flots avec des voisinages
    void remplir_flot(unsigned int f_ou, unsigned int f_es, unsigned int f_no, unsigned int f_su); 

    //forction arc_capacite [pixel p1] - prend en parametres un pixel et return la capasite entre ce pixel 
    //et celui qui appel la fonction 
    unsigned int arc_capacite(Pixel p1);
    unsigned int arc_capacite(Pixel *p1);

    //forction arc_flot [pixel p1] - prend en parametres un pixel et return la flot entre ce pixel 
    //et celui qui appel la fonction 
    unsigned int arc_flot (Pixel p1);
    unsigned int arc_flot(Pixel *p1);

    //fonctions return_x[y] - return les coordonnais de pixel
    unsigned int return_x();
    unsigned int return_y();

    //affiche les coordonnes , niveau de gris et voisins de Pixel 
    void afficher_donnes_pixel();


    void test_fonctionement_pixel();

    void changer_flot_source(unsigned int flot_s);
    void changer_flot_puit(unsigned int flot_p);
    unsigned int donner_flot_source();
    unsigned int donner_flot_puit();
    
    void changer_capacite_source( int cap_s);
    void changer_capacite_puit( int cap_p);
    unsigned int donner_capacite_source();
    unsigned int donner_capacite_puit();




    unsigned int& donner_flot_ouest_lien() { return flot_ouest; }
    unsigned int& donner_flot_est_lien()  { return flot_est; }
    unsigned int& donner_flot_nord_lien() { return flot_nord; }
    unsigned int& donner_flot_sud_lien()  { return flot_sud; }

    unsigned int& donner_capacite_ouest_lien() { return capacite_ouest; }
    unsigned int& donner_capacite_est_lien()  { return capacite_est; }
    unsigned int& donner_capacite_nord_lien() { return capacite_nord; }
    unsigned int& donner_capacite_sud_lien()  { return capacite_sud; }

};

#endif
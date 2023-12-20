const float dt = 0.1f;
const int DIMW = 500;
const float FRICTION = 0.4f;
const float G = 9.81f;
const int MAX_PART = 300;
/// code de base sur les particules est donné
struct Vec2
{
    float x,y;
};


struct Particule
{
    Vec2 sommeForces;
    Vec2 acceleration;
    Vec2 vitesse;
    Vec2 position;
    float masse;
};

Vec2 make_Vec2(float x,float y)
{
    Vec2 z;
    z.x=x;
    z.y=y;
    return z;
}


void partInit(Particule & part,Vec2 pos,Vec2 vit,float m)
{
    part.sommeForces=make_Vec2(0,0);
    part.acceleration=make_Vec2(0,0);
    part.position=pos;
    part.vitesse=vit;
    part.masse=m;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Cible
{
    Vec2 centre;
    float rayon;
};


struct Monde
{
 Particule part[MAX_PART];
 int nb ;
 Vec2 v_init[MAX_PART];// vitesse en m/s initiale de toutes les particules
 Cible cible;
};
//Initialise toutes les particules du tableau "part" avec une vitesse initiale issue de m.v_init[i].
void initToutesLesParticules(Monde& m){
 int i;
 m.nb=300 ;
 for(i=0;i<m.nb;++i)
 {
    partInit( m.part[i], m.v_init[i].x, m.v_init[i].y);
 }
}
// La procédure initVInit initialise le tableau v_init.
// Le tableau v_init contient les vitesses initiales de toutes les particules.
// La vitesse est tirée au hasard pour x entre vxmin et vxmax ET pour y entre vymin et vymax
void initVInit(Monde& m, float vxmin, float vymin, float vxmax, float vymax){
 int i;
 for(i=0;i<m.nb;++i)
 {
 m.v_init[i].x = frand( vxmin, vxmax);
 m.v_init[i].y = frand( vymin, vymax);
 }
}
void initCible(Monde& m)
{
    m.cible.centre.x=rand()%200+250;
    m.cible.centre.y=rand()%200+250;
    m.cible.rayon=20;

}

float distance(Complex v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

bool estDansCible(Particle p, Cible c)
{
    return distance(p.position,c.centre);
}

void drawMonde(Monde m){ /// a compléter
 int i;
 color( 255,0,0);
 for(i=0;i< m.nb;++i)
 {
    drawParticle( m.part[i] );
 }
 color(134,164,34);
 circleFill(m.cible.centre.x,m.cible.centre.y,m.cible.rayon);
}
void updateMonde(Monde& m)
{
 int i ;
 for(i=0;i< m.nb;++i)
 {
    updateParticle(m.part[i]);
    if(estDansCible(m.part[i],m.cible))
        m.part[i].masse=-1;
 }
 m.cible.centre.x += rand()%5-2;
 m.cible.centre.y += rand()%5-2;
 if(isKeyPressed(SDLK_t))
 {
     int nb=0;
     Vec2 somme=make_Vec2(0,0);
     for(i=0;i<m.nb;i++)
     {
         if(m.part[i].masse==-1)
         {
             nb++;
             somme = somme + m.v_init[i];
         }
     }
     if(nb==0)
     {
         initVInit(m,-100,-100,100,100);
     }
     else{
        float range=nb;
        Vec2 moy=somme/nb;
        initVInit(m,moy.x-range,moy.y-range,moy.x+range,moy.y+range);
     }
     initToutesLesParticules(m);
 }
}


int main(int, char ** ){
 bool stop=false;
 winInit("CibleA", DIMW, DIMW);
 setKeyRepeatMode(false);
 backgroundColor( 100, 50, 200 );
 /// a compléter
 Monde m;
 initVInit(m, -100, -100, 100, 100);
 initToutesLesParticules(m);
 while( !stop )
 {
 winClear();
 drawMonde(m);
 updateMonde(m);
 stop = winDisplay();
 }
 winQuit();
 return 0;
}

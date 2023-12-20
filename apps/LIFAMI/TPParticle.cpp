// apps/LIFAMI/TPParticle.cpp
#include<Grapic.h>
#include <math.h>
#include <iostream>

using namespace grapic;
using namespace std;

const int DIMW=1000;
const int MAX=100;

struct Vec2
{
    float x,y;
};

float toRad(float a)
{
    return a*M_PI/180.0;
}

float toDeg(float a)
{
    return a*180.0/M_PI;
}

Vec2 make_Vec2(float x,float y)
{
    Vec2 z;
    z.x=x;
    z.y=y;
    return z;
}

Vec2 make_Vec2_exp(float r,float th)
{
    Vec2 z;
    z.x=r*cos(toRad(th));
    z.y=r*sin(toRad(th));
    return z;
}

Vec2 operator+(Vec2 opg,Vec2 opd)
{
    Vec2 res;
    res.x=opg.x+opd.x;
    res.y=opg.y+opd.y;
    return res;
}

Vec2 operator-(Vec2 opg,Vec2 opd)
{
    Vec2 res;
    res.x=opg.x-opd.x;
    res.y=opg.y-opd.y;
    return res;
}

Vec2 operator*(float opg, Vec2 opd)
{
    return make_Vec2(opg*opd.x,opg*opd.y);
}

Vec2 operator*(Vec2 opg, float opd)
{
    return opd*opg;
}

Vec2 operator/(Vec2 opg, float opd)
{
    return opg * (1.0 / opd);
}

Vec2 Scale(Vec2 p,float cx,float cy,float lambda)
{
    Vec2 res;
    Vec2 reff=make_Vec2(cx,cy);
    res=lambda*(p-reff+reff);
    return res;
}

Vec2 operator*(Vec2 opg,Vec2 opd)
{
    Vec2 res;
    res.x=opg.x*opd.x-opg.y*opd.y;
    res.y=opg.x*opd.y+opg.y*opd.x;
    return res;
}

struct Particule
{
    Vec2 sommeForces;
    Vec2 acceleration;
    Vec2 vitesse;
    Vec2 position;
    float masse;
};
//=======================================================================================
struct Spring
{
    float l;
    float k;
    unsigned int P1;
    unsigned int P2;
};

struct World
{
    int nbp;
    Particule tab[MAX];
    int nbr;
    Spring tabr[MAX];
};
//=======================================================================================
void partInit(Particule & part,Vec2 pos,Vec2 vit,float m)
{
    part.sommeForces=make_Vec2(0,0);
    part.acceleration=make_Vec2(0,0);
    part.position=pos;
    part.vitesse=vit;
    part.masse=m;
}

void partAddForce(Particule & part,Vec2 force)
{
    part.sommeForces=part.sommeForces+force;
}

void partUpdatePV(Particule & part,float dtlance)
{
    float FRICTION=0.6;
    part.acceleration=part.sommeForces/part.masse;
    part.vitesse=part.vitesse+part.acceleration*dtlance;
    part.position=part.position+part.vitesse*dtlance;
    part.sommeForces=make_Vec2(0,0);
    if(part.position.x<0)
    {
        part.position.x=part.position.x*(-1);
        part.vitesse.x=part.vitesse.x*(-1);
        part.vitesse=FRICTION*part.vitesse;

    }
    if(part.position.y<0)
    {
        part.position.y=part.position.y*(-1);
        part.vitesse.y=part.vitesse.y*(-1);
        part.vitesse=FRICTION*part.vitesse;

    }
    if(part.position.x>DIMW)
    {
        part.position.x=DIMW-(part.position.x-DIMW);
        part.vitesse.x=part.vitesse.x*(-1);
        part.vitesse=FRICTION*part.vitesse;
    }
    if(part.position.y>DIMW)
    {
        part.position.y=DIMW-(part.position.y-DIMW);
        part.vitesse.y=part.vitesse.y*(-1);
        part.vitesse=FRICTION*part.vitesse;
    }
}

void partDraw(Particule & part)
{
    color(50,50,250);
    circleFill(part.position.x,part.position.y,10);
}
//================================================================================================================
void updatePartPV(Particule & P,float dt)
{
    if(P.masse>0)
    {
        P.acceleration=P.sommeForces/P.masse;
        P.vitesse=P.vitesse+P.acceleration*dt;
        P.position=P.position+P.vitesse*dt;
    }
    P.sommeForces=make_Vec2(0,0);
}

float distance(Vec2 A,Vec2 B)
{
    Vec2 d=B-A;
    float d2=d.x*d.x+d.y*d.y;
    return sqrtf(d2);
}

void initRessort(Spring &r,float k,unsigned int P1,unsigned int P2,World W)
{
    r.l=distance(W.tab[P1].position,W.tab[P2].position);
    r.k=k;
    r.P1=P1;
    r.P2=P2;
}

void init(World &W)
{
    W.nbp=4;
    partInit(W.tab[0],make_Vec2(DIMW/4,DIMW/2),make_Vec2(0,0),10);
    partInit(W.tab[1],make_Vec2(DIMW/2,DIMW/2),make_Vec2(0,0),10);         //PARTICULES CARRE
    partInit(W.tab[2],make_Vec2(DIMW/4,DIMW/2+200),make_Vec2(0,0),10);
    partInit(W.tab[3],make_Vec2(DIMW/2,DIMW/2+200),make_Vec2(0,0),10);

    W.nbp+=6;
    partInit(W.tab[4],make_Vec2(DIMW/2+200,DIMW/2+40),make_Vec2(0,0),10);     //PARTICULES CERCLE
    partInit(W.tab[5],make_Vec2(DIMW/2+250,DIMW/2+75),make_Vec2(0,0),10);
    partInit(W.tab[6],make_Vec2(DIMW/2+250,DIMW/2+150),make_Vec2(0,0),10);
    partInit(W.tab[7],make_Vec2(DIMW/2+200,DIMW/2+180),make_Vec2(0,0),10);
    partInit(W.tab[8],make_Vec2(DIMW/2+150,DIMW/2+150),make_Vec2(0,0),10);
    partInit(W.tab[9],make_Vec2(DIMW/2+150,DIMW/2+75),make_Vec2(0,0),10);

    W.nbr=4;
    initRessort(W.tabr[0],30,0,1,W);                                        //RESSORTS CARRE
    initRessort(W.tabr[1],30,1,2,W);
    initRessort(W.tabr[2],30,2,3,W);
    initRessort(W.tabr[3],30,3,0,W);
    W.nbr+=2;
    initRessort(W.tabr[4],30,0,2,W);
    initRessort(W.tabr[5],30,1,3,W);

    W.nbr+=6;
    initRessort(W.tabr[6],300,4,5,W);                                        //RESSORTS CERCLE
    initRessort(W.tabr[7],300,5,6,W);
    initRessort(W.tabr[8],300,6,7,W);
    initRessort(W.tabr[9],300,7,8,W);
    initRessort(W.tabr[10],300,8,9,W);
    initRessort(W.tabr[11],300,9,4,W);
    W.nbr+=3;
    initRessort(W.tabr[12],300,4,7,W);
    initRessort(W.tabr[13],300,5,8,W);
    initRessort(W.tabr[14],300,6,9,W);
    W.nbr+=6;
    initRessort(W.tabr[15],300,5,9,W);
    initRessort(W.tabr[16],300,6,8,W);
    initRessort(W.tabr[17],300,4,6,W);
    initRessort(W.tabr[18],300,4,8,W);
    initRessort(W.tabr[19],300,7,5,W);
    initRessort(W.tabr[20],300,7,9,W);


}

Vec2 normaliser(Vec2 v)
{
    float n=sqrtf(v.x*v.x+v.y*v.y);
    return v*(1.0/n);
}

void update(World &W,float dt)
{
    float G=9.81;
    int i;
    for(i=0;i<W.nbp;i++)
    {
        partAddForce(W.tab[i],G*W.tab[i].masse*make_Vec2(0,-1));
    }
    for(i=0;i<W.nbr;i++)
    {
        Vec2 P1=W.tab[W.tabr[i].P1].position;
        Vec2 P2=W.tab[W.tabr[i].P2].position;

        float l=distance(P1,P2);
        Vec2 lr=normaliser(P2-P1);
        float dl=l-W.tabr[i].l;
        partAddForce(W.tab[W.tabr[i].P1],    lr*dl*W.tabr[i].k);
        partAddForce(W.tab[W.tabr[i].P2],-1* lr*dl*W.tabr[i].k);
    }
    for(i=0;i<W.nbp;i++)
    {
        partUpdatePV(W.tab[i],dt);
    }
}

void draw(World W)
{
    int i;
    for(i=0;i<W.nbp;i++)
    {
        color(0,0,255);                                                                //couleur des particules
        circleFill(W.tab[i].position.x,W.tab[i].position.y,3);
        Vec2 v=normaliser(W.tab[i].vitesse)*10;
        color(0,255,0);
        line(W.tab[i].position.x,W.tab[i].position.y,W.tab[i].position.x+v.x,W.tab[i].position.y+v.y);
    }
    for(i=0;i<W.nbr;i++)
    {

        Vec2 P1=W.tab[W.tabr[i].P1].position;
        Vec2 P2=W.tab[W.tabr[i].P2].position;
        color(0,100,200);
        line(P1.x,P1.y,P2.x,P2.y);                                                      //cotés

        float l=distance(P1,P2);
        float dl=W.tabr[i].l-l;

         //color(255,255,255)
        //line(P1.x,P1.y,P1.x+dl*normaliser(P2-P1).x,P1.y+dl*normaliser(P2-P1).y);    //trait des forces
    }
}
//=====================================================
int main(int argc, char**argv)
{
    Menu men;
    menu_add(men,"LANCE");
    menu_add(men,"STOP");
    menu_add(men,"PRET");
    menu_add(men,"RESSORT");

    float dtlance=0.008;   //temps pour balle
    float dt=0.025;    //temps pour ressort
    bool stop=false;
    winInit("Particule",DIMW,DIMW);
    backgroundColor(220,220,220);
    Particule P;
    partInit(P,make_Vec2(DIMW/2-200,DIMW/2),make_Vec2(100,200),10);
    partAddForce(P,make_Vec2(0,0));

    World Wo;
    init(Wo);

    while(!stop)
    {
        winClear();
        menu_draw(men,5,5,100,150);
        partAddForce(P,make_Vec2(0.0,-9.81*P.masse));
        cout << P.vitesse.y << endl;
        partUpdatePV(P,dtlance);

        switch(menu_select(men))
        {
            case 0 : partDraw(P); break;
            case 1 : partInit(P,make_Vec2(DIMW/2-200,DIMW/2),make_Vec2(0,0),10); init(Wo); partDraw(P); break;
            case 2 : partInit(P,make_Vec2(DIMW/2-200,DIMW/2),make_Vec2(-100,-300),10); partDraw(P);break;
            case 3 : partInit(P,make_Vec2(DIMW/2-200,DIMW/2),make_Vec2(100,0),10); update(Wo,dt); draw(Wo);break;
            default: partDraw(P); break;
        }
        if (menu_select(men)==1)
        {
            partDraw(P);
            menu_setSelect(men,2);
        }
        stop=winDisplay();
    }
winQuit();
return 0;
}


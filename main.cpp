#include <GL\glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <map>
#include <sys/time.h>

#include <Automobile.h>
#include <Route.h>


#include <iostream>
#define ESCAPE 27



using namespace std;

//flags: CONDITIONS sur l'existance des objets

int routeIsEnabled=0; // switch car driving <-> car only
int dayIsEnabled=1; // 1:DAY 0:NIGHT to switch night and day
int pluieIsEnabled=0; // FOG EFFECT 0:enable/1:disable/2:nothing

int sideroadObjectsEnabled=0;   //if whhelflag draw road barrières et les arbres and wheel effect

//Determiner la position de la camera
int cameraLibreEnabled = 1;
int cameraFixeEnabled = 0;
int animationStarted = 0;

float DistanceCameraFixed = 5.;

//Propriétés de la fenêtre
GLint window;
GLint Xsize=1000;
GLint Ysize=800;

float i,theta;


//Variables de translation et de rotation de la camera
GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0,
        xs=1.0,ys=1.0,zs=1.0,
        xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0;

//Variables de coloration des objets
GLfloat r=0,g=0,b=0;
int count=1;

//structure pour obtenir le timestamp actuel
struct timeval tp;
//le timestamp lors du lancement de l'animation
long int previous_timestamp = 0;
//le timestamp actuel
long int current_timestamp;
//combien de frames maximum
int frames = 100;
int frames_counter = 0;
//la durée de chaque frame
const long int duree_frame = 100;//diff
//rayon de l'animation
float rayon_animation = 5.;
float ray_elem = 0.2;



GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y );

///revenir à l'etat initial de la camera
void reset()
{
    xt=0.0;
    yt=0.0;
    zt=0.0;
    xw=0.0;
    xs=1.0;
    ys=1.0;
    zs=1.0;
    xangle=0.0;
    yangle=0.0;
    zangle=0.0;
    angle=0.0;

}

///Fonction principal de l'animation exemplaire
void animation_frame()
{
    int maximum;
    if(!sideroadObjectsEnabled) maximum = 90;
    else maximum = 180;


    if(yangle<maximum)
    {
        if(!sideroadObjectsEnabled)
        {
            if(xt<5){
            xt += 0.08;
            cout << "xt changed"<<xt<<endl;

            }

        }

        if(sideroadObjectsEnabled)
        {

                angle-=5;
                xw+=0.2;
                cout << "xw changed"<<xw<<endl;
                cout << "angle changed"<<angle<<endl;


        }

        if(yt>-1)
        {
            yt -= 0.04;
            cout << "yt changed"<<yt<<endl;

        }

        yangle += 1.2;
        cout << "yangle changed "<<yangle <<endl;

    }
    else
    {

        animationStarted = 0;
        reset();
        xangle += 5.0;
    }


}
GLvoid Transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,Width/Height,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
}


GLvoid InitGL(GLfloat Width, GLfloat Height)
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0);              /* Add line width,   ditto */
    Transform( Width, Height ); /* Perform the transformation */
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);


    //configuration des sources de la lumière

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

}

///Fonction de dessin principale
GLvoid DrawGLScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(count==1)
        InitGL(Xsize,Ysize);


    if(dayIsEnabled==1) //initialiser la fenetre
        glClearColor(1,1,1,1);
    else
        glClearColor(0.1,0.1,0.1,0);

    glPushMatrix();
    glLoadIdentity();


    //Position de la camera
    if(cameraLibreEnabled)
    {
        if(animationStarted)
        {
            animation_frame();
        }

        glTranslatef(-1.0,0.0,-3.5);
        glRotatef(xangle,1.0,0.0,0.0);
        glRotatef(yangle,0.0,1.0,0.0);
        glRotatef(zangle,0.0,0.0,1.0);
        glTranslatef(xt,yt,zt);
        glScalef(xs,ys,zs);

    }
    else if(cameraFixeEnabled)
    {

        gluLookAt(DistanceCameraFixed,2,0, -0.5,0.,0., 0., 1., 0.);
        glRotatef(yangle,0.0,1.0,0.0);

    }



    //Configuration de Joournée/nuit/pluie
    glEnable(GL_COLOR_MATERIAL);

    if(pluieIsEnabled==1)
    {
        GLfloat fogcolour[4]= {1.0,1.0,1.0,1.0};

        glFogfv(GL_FOG_COLOR,fogcolour);
        glFogf(GL_FOG_DENSITY,0.1);
        glFogi(GL_FOG_MODE,GL_EXP);
        glFogf(GL_FOG_START,3.0);
        glFogf(GL_FOG_END,100.0);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);
    }
    if(pluieIsEnabled==0)
    {
        glDisable(GL_FOG);
    }


    if(!dayIsEnabled)
    {
        glClearColor(0.1,0.1,0.1,0);
        GLfloat fogcolour[4]= {0.0,0.0,0.0,1.0};

        glFogfv(GL_FOG_COLOR,fogcolour);
        glFogf(GL_FOG_DENSITY,0.2);
        glFogi(GL_FOG_MODE,GL_EXP);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);
    }

    //Dessin

    //Dessin de la voiture
    Automobile(t).drawAutomobile(r, g, b, angle);

    //Dessin de l'environnement
    Route().drawRoad(xw, routeIsEnabled, sideroadObjectsEnabled);


    //Affichage du dessin
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);


    glutPostRedisplay();
    glutSwapBuffers();

}

///Gestion du clavier
void keyDown(GLubyte key, GLint x, GLint y)
{

    switch ( key )
    {
    case ESCAPE :
        printf("escape pressed. exit.\n");
        exit(0);
        break;

    case 'x':
        xangle += 5.0;
        glutPostRedisplay();
        break;

    case 'X':
        xangle -= 5.0;
        glutPostRedisplay();
        break;

    case 'z':
        zangle += 5.0;
        glutPostRedisplay();
        break;

    case 'Z':
        zangle -= 5.0;
        glutPostRedisplay();
        break;

    case '8':
        yt -= 0.2;
        glutPostRedisplay();
        break;
    case '2':
        yt += 0.2;                      /* Move down */
        glutPostRedisplay();
        break;

    case '6':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

    case '4':
        yangle += 5.0;
        glutPostRedisplay();
        break;

    default:
        break;
    }

}

static void SpecialKeyFunc( int Key, int x, int y )
{

    switch ( Key )
    {
    case GLUT_KEY_DOWN:
        if(!sideroadObjectsEnabled)
            xt += 0.2;
        if(sideroadObjectsEnabled)
        {
            angle-=5;
            xw-=0.2;
        }
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:
        if(!sideroadObjectsEnabled)
            xt -= 0.2;
        if(sideroadObjectsEnabled)
        {
            angle+=5;
            xw+=0.2;
        }
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        xt += 0.2;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        xt -= 0.2;
        glutPostRedisplay();
        break;
    }
}

///Gestion du menu (click droit de la souris)
void myMenu(int id)
{
    if (id==1)
    {

        routeIsEnabled=0; //Disable la route
        sideroadObjectsEnabled=0; //Disable les arbres et les barrieres

        dayIsEnabled = 1; //Journée


        glutPostRedisplay();

    }
    if(id ==2)
    {
        routeIsEnabled=1; //La route
        pluieIsEnabled=0; //disable la pluie: Fog Effect

        sideroadObjectsEnabled=1; //dessiner les arbres ...

        xangle += 5.0;
        glutPostRedisplay();
    }

    if(id==12) //journée
    {
        dayIsEnabled=1;
        pluieIsEnabled=0;

        glutPostRedisplay();
    }

    if(id==13) //nuit
    {
        dayIsEnabled=0;
        pluieIsEnabled=0;



        glutPostRedisplay();
    }

    if(id==14)//pluie
    {
        dayIsEnabled=1;
        pluieIsEnabled = 1;


        glClearColor(1,1,1,1);
        glDisable(GL_FOG);
        glutPostRedisplay();
    }

    if(id==15)
    {
        cameraLibreEnabled = 1;
        cameraFixeEnabled = 0;
        glutPostRedisplay();
    }
    if(id==16)
    {
        cameraLibreEnabled = 0;
        cameraFixeEnabled = 1;
        yangle = 0;
        glutPostRedisplay();
    }

    if(id==17) //start animation
    {

        animationStarted = 1;
        cameraFixeEnabled = 0;
        cameraLibreEnabled = 1;
        glutPostRedisplay();


    }
}

///Gestion des couleur de la voiture
void colorMenu(int id)
{
    if (id==6)
    {
        r=g=0;
        b=1;
        glutPostRedisplay();

    }
    if(id ==7)
    {
        r=0.8;
        b=g=0;
        glutPostRedisplay();
    }
    if(id==8)
    {
        g=1;
        r=b=0;
        glutPostRedisplay();
    }
    if (id==9)
    {
        r=b=g=0;
        glutPostRedisplay();
    }
    if(id==10)
    {
        b=0;
        r=g=1;
        glutPostRedisplay();
    }
    if(id==11)
    {
        b=r=g=.7;
        glutPostRedisplay();
    }

}

///Gestion des click de la souris
void mouseClick(int button, int state, int x, int y)
{
    if (button == 0) ///click gauche de la souris
    {
        if(cameraLibreEnabled)
        {
            zt += 0.2;
            glutPostRedisplay();
        }
        else
        {

            if(DistanceCameraFixed>3)
            {
                DistanceCameraFixed -= 0.2;
                glutPostRedisplay();
            }
        }
    }
    else ///click droit et milieu de la souris
    {
        if(cameraLibreEnabled) ///en mode libre
        {

            zt -= 0.2;
            glutPostRedisplay();
        }
        else ///en mode camera fixe
        {
            if(DistanceCameraFixed<10) ///distance maximal de 10 entre la camera et la voiture
            {
                DistanceCameraFixed += 0.2;
                glutPostRedisplay();

            }
        }
    }
}

///Affichage du guide dans la console
void print(string key, string details)
{
    cout<< key << " <-> " << details <<endl;
}
void ShowGuide()
{

    print("8", "translation positive suivant y" );
    print("2", "translation negative suivant y" );
    print("4", "rotation positive autour de y");
    print("6", "rotation negative autour de y");

    print("Xx--Zz","Pour les rotations correspondantes");
    print("U-F"," FOR CAMERA VIEW SETTINGS");
    print("Left & Right Arrows","se déplacer suivant l'axe x horizontal (l'image affichée dépend du mode choisi)");

    print("Up & Down Arrows","Déplacer la voiture");



    print("Left Click on Mouse", "Zoom IN");
    print("Center Click on Mouse || Double Right Click on Mouse", "Zoom Out");
    print("Right Click on Mouse", "Menu");

    print("ESC || CTRL+C", "ESCAPE TO EXIT");
}


///Fonction principale
int main(int argc, char **argv)
{
    ///Affichage du guide dans la console
    ShowGuide();

    ///initiation de la fenêtre
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(Xsize,Ysize);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Mini-Projet: Animation 3D d'une voiture");

    //Dessin
    glutDisplayFunc(DrawGLScene);

    //Les fonctions du clavier
    glutKeyboardFunc(keyDown);
    glutSpecialFunc( SpecialKeyFunc );

    //Les fonctions de la souris
    glutMouseFunc(mouseClick);

    //Menu en click droit de la souris
    InitGL(Xsize,Ysize);
    int submenu=glutCreateMenu(colorMenu);

    glutAddMenuEntry("Gris",11);
    glutAddMenuEntry("Bleu", 6);

    glutAddMenuEntry("Noir",9);
    glutAddMenuEntry("Jaune",10);

    glutAddMenuEntry("Vert",8);
    glutAddMenuEntry("Rouge", 7);

    glutCreateMenu(myMenu);

    glutAddMenuEntry("Voir l'automobile seulement", 1);
    glutAddMenuEntry("Conduite de l'automobile", 2);

    glutAddMenuEntry("Journée",12);
    glutAddMenuEntry("Nuit",13);
    glutAddMenuEntry("Pluie",14);



    //Choix de la position de la caméra

    //position libre
    glutAddMenuEntry("Camera Libre",15);
    //position fixe
    glutAddMenuEntry("Camera derriere l'automobile",16);

    //demarrer l'animation
    glutAddMenuEntry("Demarrer l'exemple d'animation",17);

    //couleur de la voiture
    glutAddSubMenu("Couleur de l'automobile",submenu);


    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 1;
}


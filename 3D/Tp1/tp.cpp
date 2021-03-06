// -------------------------------------------
// gMini : a minimal OpenGL/GLUT application
// for 3D graphics.
// Copyright (C) 2006-2008 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <algorithm>
#include <GL/glut.h>
#include <float.h>
#include "src/Vec3.h"
#include "src/Camera.h"

int nX = 50;
int nY = 50;

int cpt = 0;

float globalSuper;
float zaman = 10.0; 

enum DisplayMode{ WIRE=0, SOLID=1, LIGHTED_WIRE=2, LIGHTED=3 };

struct Triangle {
    inline Triangle () {
        v[0] = v[1] = v[2] = 0;
    }
    inline Triangle (const Triangle & t) {
        v[0] = t.v[0];   v[1] = t.v[1];   v[2] = t.v[2];
    }
    inline Triangle (unsigned int v0, unsigned int v1, unsigned int v2) {
        v[0] = v0;   v[1] = v1;   v[2] = v2;
    }
    unsigned int & operator [] (unsigned int iv) { return v[iv]; }
    unsigned int operator [] (unsigned int iv) const { return v[iv]; }
    inline virtual ~Triangle () {}
    inline Triangle & operator = (const Triangle & t) {
        v[0] = t.v[0];   v[1] = t.v[1];   v[2] = t.v[2];
        return (*this);
    }
    // membres :
    unsigned int v[3];
};


struct Mesh {
    std::vector< Vec3 > vertices;
    std::vector< Vec3 > normals;
    std::vector< Triangle > triangles;
};

Mesh mesh;

//Mesh to generate
Mesh unit_sphere;
Mesh unit_cube;
Mesh unit_tore;
Mesh unit_super_shape;

bool display_normals;
bool display_loaded_mesh;
bool display_unit_sphere;
bool display_unit_cube;
bool display_unit_tore;
bool display_unit_super_shape;
DisplayMode displayMode;

// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;
static unsigned int SCREENWIDTH = 1600;
static unsigned int SCREENHEIGHT = 900;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static bool fullScreen = false;

//To complete
void setUnitSphere( Mesh & o_mesh, int nX = 20, int nY=20 )
{
    o_mesh.vertices.clear();
    o_mesh.triangles.clear();
    o_mesh.normals.clear();

    float deltaTeta = 2*M_PI / (float)nX;
    float deltaPhi = M_PI / (float)nY;


    

    for(int i=0; i < nX; i++){
        for(int j=0; j < nY; j++){
            float teta = deltaTeta * i;
            float phi = deltaPhi * j - M_PI/2;

            o_mesh.vertices.push_back(Vec3(std::cos(teta)*std::cos(phi), std::sin(teta)*std::cos(phi), std::sin(phi)));
            o_mesh.normals.push_back(Vec3(std::cos(teta)*std::cos(phi), std::sin(teta)*std::cos(phi), std::sin(phi)));
        }
    }

    for(int i=0; i < nX ; i++){
        for(int j=0; j < nY-1; j++){
            if(i == nX -1){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, j));
                o_mesh.triangles.push_back(Triangle(j+1, j, i*nY+j+1));

                //std::cout<<"if T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<<j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"if T2 C1 :"<< j + 1<< "T2 C2: "<< j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }else{
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, (i+1)*nY+j));
                o_mesh.triangles.push_back(Triangle((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1));

                //std::cout<<"T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<<(i+1)*nY+j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"T2 C1 :"<< (i+1)*nY+j+1 << "T2 C2: "<< (i+1)*nY+j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }
        }
    }
    //std::cout<<"nombre vertices : "<<o_mesh.vertices.size()<<std::endl;
}

void setUnitCube( Mesh & o_mesh, int nX = 5, int nY=5)
{
    o_mesh.vertices.clear();
    o_mesh.triangles.clear();

    o_mesh.vertices.push_back(Vec3(0,0,0));
    o_mesh.vertices.push_back(Vec3(0,0,1));
    o_mesh.vertices.push_back(Vec3(0,1,0));
    o_mesh.vertices.push_back(Vec3(0,1,1));
    o_mesh.vertices.push_back(Vec3(1,0,0));
    o_mesh.vertices.push_back(Vec3(1,0,1));
    o_mesh.vertices.push_back(Vec3(1,1,0));
    o_mesh.vertices.push_back(Vec3(1,1,1));

    o_mesh.triangles.push_back(Triangle(0,1,2));
    o_mesh.triangles.push_back(Triangle(2,1,3));
    o_mesh.triangles.push_back(Triangle(3,1,5));
    o_mesh.triangles.push_back(Triangle(3,5,7));
    o_mesh.triangles.push_back(Triangle(7,5,6));
    o_mesh.triangles.push_back(Triangle(6,5,4));
    o_mesh.triangles.push_back(Triangle(7,6,3));
    o_mesh.triangles.push_back(Triangle(2,3,6));
    o_mesh.triangles.push_back(Triangle(2,6,0));
    o_mesh.triangles.push_back(Triangle(6,4,0));
    o_mesh.triangles.push_back(Triangle(0,4,1));
    o_mesh.triangles.push_back(Triangle(4,5,1));


    
    //o_mesh.normals.clear();

    /*
    //pour y = Nx
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(i/nX,1,j/nX));
        }
    }

     // pour z = nX
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(j/nX,i/nX,1));
        }
    }
    
    // pour x = nX
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(1,j/nX,i/nX));
        }
    }

    // pour x = 0 
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(0,i/nX,j/nX));
        }
    }


    //pour y = 0
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(j/nX,0,i/nX));
        }
    }

    // pour z = 0 
    for(float i = 0; i < nX+1; i ++){
        for(float j = 0; j < nX+1; j ++){
            o_mesh.vertices.push_back(Vec3(j/nX,i/nX,0));
        }
    }

    std::cout<<"nombre vertices : "<<o_mesh.vertices.size()<<std::endl;
    
    
    for(int i = 0; i < (nX+1)*6; i ++){
        for(int j = 0; j < (nX+1)*6; j ++){
            if( (i % (nX+1) == nX)  || (j % (nX+1) == nX)){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, j));
                //o_mesh.triangles.push_back(Triangle(j+1, j, i*nY+j+1));
            }
            
            o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, (i+1)*nY+j));
            //o_mesh.triangles.push_back(Triangle((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1));
        }
    }*/
}

void setUnitTore( Mesh & o_mesh, int nX = 50, int nY= 50 ){
    float R = 1.5;
    float r = 0.5;
    float angleChqEtp = 2*M_PI / (float)nX;
    //float deltaPhi = M_PI / (float)nY;

    for(int i=0; i < nX; i++){ //u
        for(int j=0; j < nY; j++){ // v
            float Q = angleChqEtp * i;
            float P = angleChqEtp * j;

            o_mesh.vertices.push_back(Vec3((R + r*cos(Q))*cos(P), (R + r*cos(Q))*sin(P), r*sin(Q)));
            o_mesh.normals.push_back(Vec3((R + r*cos(Q))*cos(P), (R + r*cos(Q))*sin(P), r*sin(Q)));
        }
    }

    for(int i = 0; i < nX; i++){
        for(int j = 0; j < nY; j++){
            if (j == nY-1 && i == nY-1){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY, j));
                o_mesh.triangles.push_back(Triangle(i*nY, j+1, i));

                //std::cout<<"if T1 C1 :"<< i*nY << "T1 C2: "<< 48 << "T1 C3: "<< i <<" i: "<<i<<" j: "<<j<<std::endl;
            }
            else if (j == nY-1){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY, (i+1)*nY+j));
                o_mesh.triangles.push_back(Triangle((i+1)*nY, (i+1)*nY+j, i*nY));

                //std::cout<<"else if1 T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+1 << "T1 C3: "<<(i+1)*nY+j<<" i: "<<i<<" j: "<<j<<std::endl;
            }
            else if(i == nY-1){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, j));
                o_mesh.triangles.push_back(Triangle(j+1, j, i*nY+j+1));
                
                
                //std::cout<<"else if T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<< j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"if T2 C1 :"<< j + 1<< "T2 C2: "<< j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }else{
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, (i+1)*nY+j));
                o_mesh.triangles.push_back(Triangle((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1));
                
                //std::cout<<"T1 C1 :"<< i*nY+j << "T1 C2: "<< i*nY+j+1 << "T1 C3: "<<(i+1)*nY+j<<" i: "<<i<<" j: "<<j<<std::endl;
                //std::cout<<"T2 C1 :"<< (i+1)*nY+j+1 << "T2 C2: "<< (i+1)*nY+j << "T2 C3: "<<i*nY+j+1<<"i: "<<i<<"j: "<<j<<std::endl;
            }
        }
    }
    //std::cout<<"nombre vertices : "<<o_mesh.vertices.size()<<std::endl;
}


float supershape(float degree, float m, float n1, float n2, float n3){
    float a = 1;
    float b = 1;

    float t1 = abs((1/a)*cos(m * degree/4));
    t1 = pow (t1,n2);

    float t2 = abs((1/b)*sin(m * degree/4));
    t2 = pow(t2,n3);

    float t3 = t1 + t2;

    float res = pow(t3, -1 / n1);

    return res;
}

void setUnitSuperShape ( Mesh & o_mesh, int nX = 50, int nY= 50, float z = sin(zaman)){
    o_mesh.vertices.clear();
    o_mesh.triangles.clear();

    float D = 3;
    float m,n1,n2,n3;
    m = 7;
    n1 = 0.2;
    n2 = 1.7;
    n3 = 1.7;

    float deltaTeta = M_PI / (float)nY;
    
    float deltaPhi = 2*M_PI / (float)nX;

    for(int i=0; i < nX; i++){
        float teta = deltaPhi * i - M_PI/2;
        float r1 = supershape(teta, m, n1, n2, n3);
        for(int j=0; j < nY; j++){
            float phi = deltaTeta * j - M_PI;
            float r2 = supershape(phi, m, n1, n2, n3);

            o_mesh.vertices.push_back(Vec3(D * r1*std::cos(teta)*r2*std::cos(phi), D * r1*std::sin(teta)*r2*std::cos(phi), D * r2*std::sin(phi)));
            //o_mesh.normals.push_back(Vec3(std::cos(teta)*std::cos(phi), std::sin(teta)*std::cos(phi), std::sin(phi)));
        }
    }

    for(int i=0; i < nX ; i++){
        for(int j=0; j < nY-1; j++){
            if(i == nY -1){
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, j));
                o_mesh.triangles.push_back(Triangle(j+1, j, i*nY+j+1));
            }else{
                o_mesh.triangles.push_back(Triangle(i*nY+j, i*nY+j+1, (i+1)*nY+j));
                o_mesh.triangles.push_back(Triangle((i+1)*nY+j+1, (i+1)*nY+j, i*nY+j+1));
            }
            
        }
    }
}

bool saveOFF( const std::string & filename ,
              std::vector< Vec3 > & i_vertices ,
              std::vector< Vec3 > & i_normals ,
              std::vector< Triangle > & i_triangles,
              bool save_normals = true ) {
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open()) {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "OFF" << std::endl ;

    unsigned int n_vertices = i_vertices.size() , n_triangles = i_triangles.size();
    myfile << n_vertices << " " << n_triangles << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v ) {
        myfile << i_vertices[v][0] << " " << i_vertices[v][1] << " " << i_vertices[v][2] << " ";
        if (save_normals) myfile << i_normals[v][0] << " " << i_normals[v][1] << " " << i_normals[v][2] << std::endl;
        else myfile << std::endl;
    }
    for( unsigned int f = 0 ; f < n_triangles ; ++f ) {
        myfile << 3 << " " << i_triangles[f][0] << " " << i_triangles[f][1] << " " << i_triangles[f][2];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}

void openOFF( std::string const & filename,
              std::vector<Vec3> & o_vertices,
              std::vector<Vec3> & o_normals,
              std::vector< Triangle > & o_triangles,
              bool load_normals = true )
{
    std::ifstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return;
    }

    std::string magic_s;

    myfile >> magic_s;

    if( magic_s != "OFF" )
    {
        std::cout << magic_s << " != OFF :   We handle ONLY *.off files." << std::endl;
        myfile.close();
        exit(1);
    }

    int n_vertices , n_faces , dummy_int;
    myfile >> n_vertices >> n_faces >> dummy_int;

    o_vertices.clear();
    o_normals.clear();

    for( int v = 0 ; v < n_vertices ; ++v )
    {
        float x , y , z ;

        myfile >> x >> y >> z ;
        o_vertices.push_back( Vec3( x , y , z ) );

        if( load_normals ) {
            myfile >> x >> y >> z;
            o_normals.push_back( Vec3( x , y , z ) );
        }
    }

    o_triangles.clear();
    for( int f = 0 ; f < n_faces ; ++f )
    {
        int n_vertices_on_face;
        myfile >> n_vertices_on_face;

        if( n_vertices_on_face == 3 )
        {
            unsigned int _v1 , _v2 , _v3;
            myfile >> _v1 >> _v2 >> _v3;

            o_triangles.push_back(Triangle( _v1, _v2, _v3 ));
        }
        else if( n_vertices_on_face == 4 )
        {
            unsigned int _v1 , _v2 , _v3 , _v4;
            myfile >> _v1 >> _v2 >> _v3 >> _v4;

            o_triangles.push_back(Triangle(_v1, _v2, _v3 ));
            o_triangles.push_back(Triangle(_v1, _v3, _v4));
        }
        else
        {
            std::cout << "We handle ONLY *.off files with 3 or 4 vertices per face" << std::endl;
            myfile.close();
            exit(1);
        }
    }

}


// ------------------------------------

void initLight () {
    GLfloat light_position1[4] = {22.0f, 16.0f, 50.0f, 0.0f};
    GLfloat direction1[3] = {-52.0f,-16.0f,-50.0f};
    GLfloat color1[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat ambient[4] = {0.3f, 0.3f, 0.3f, 0.5f};

    glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, color1);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
}

void init () {
    camera.resize (SCREENWIDTH, SCREENHEIGHT);
    initLight ();
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
    glClearColor (0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);

    displayMode = LIGHTED;
    display_normals = false;
    display_unit_sphere = false;
    display_unit_cube = false;
    display_unit_tore = false;
    display_unit_super_shape = false;

    display_loaded_mesh = true;

    glLineWidth(1.);
    glPointSize(4.);
}




// ------------------------------------
// rendering.
// ------------------------------------


void drawVector( Vec3 const & i_from, Vec3 const & i_to ) {

    glBegin(GL_LINES);
    glVertex3f( i_from[0] , i_from[1] , i_from[2] );
    glVertex3f( i_to[0] , i_to[1] , i_to[2] );
    glEnd();
}

void drawVertices( Mesh const & i_mesh ) {
    glBegin(GL_POINTS); //Fonction OpenGL de dessin de points
    for(unsigned int vIt = 0 ; vIt < i_mesh.vertices.size(); ++vIt) {
        Vec3 p = i_mesh.vertices[vIt];

        glVertex3f( p[0] , p[1] , p[2] );
    }
    glEnd();
}


void drawTriangleMesh( Mesh const & i_mesh ) {

    if( i_mesh.triangles.size() > 0 ){
        if( i_mesh.normals.size() > 0 ){
            //Fonction de dessin en utilisant les normales au sommet
            glBegin(GL_TRIANGLES); //Fonction OpenGL de dessin de triangles
            for(unsigned int tIt = 0 ; tIt < i_mesh.triangles.size(); ++tIt) {
                Vec3 p0 = i_mesh.vertices[i_mesh.triangles[tIt][0]];
                Vec3 n0 = i_mesh.normals[i_mesh.triangles[tIt][0]];

                Vec3 p1 = i_mesh.vertices[i_mesh.triangles[tIt][1]];
                Vec3 n1 = i_mesh.normals[i_mesh.triangles[tIt][1]];

                Vec3 p2 = i_mesh.vertices[i_mesh.triangles[tIt][2]];
                Vec3 n2 = i_mesh.normals[i_mesh.triangles[tIt][2]];
                glColor3f( n0[0], n0[1], n0[2] );
                glNormal3f( n0[0] , n0[1] , n0[2] );
                glVertex3f( p0[0] , p0[1] , p0[2] );

                glColor3f( n1[0], n1[1], n1[2] );
                glNormal3f( n1[0] , n1[1] , n1[2] );
                glVertex3f( p1[0] , p1[1] , p1[2] );

                glColor3f( n2[0], n2[1], n2[2] );
                glNormal3f( n2[0] , n2[1] , n2[2] );
                glVertex3f( p2[0] , p2[1] , p2[2] );
            }
            glEnd();
        } else {
            //Fonction de dessin en utilisant sans normales
            glBegin(GL_TRIANGLES); //Fonction OpenGL de dessin de triangles
            for(unsigned int tIt = 0 ; tIt < i_mesh.triangles.size(); ++tIt) {
                Vec3 p0 = i_mesh.vertices[i_mesh.triangles[tIt][0]];
                Vec3 p1 = i_mesh.vertices[i_mesh.triangles[tIt][1]];
                Vec3 p2 = i_mesh.vertices[i_mesh.triangles[tIt][2]];

                //Dessin des trois sommets formant le triangle avec colors
                glColor3f( p0[0], p0[1], p0[2] );
                glVertex3f( p0[0] , p0[1] , p0[2] );

                glColor3f( p1[0], p1[1], p1[2] );
                glVertex3f( p1[0] , p1[1] , p1[2] );

                glColor3f( p2[0], p2[1], p2[2] );
                glVertex3f( p2[0] , p2[1] , p2[2] );
            }
            glEnd();
        }
    } else {
        drawVertices(i_mesh);
    }

    if(display_normals){

        glColor3f(1.,0.,0.);
        for(unsigned int pIt = 0 ; pIt < i_mesh.normals.size() ; ++pIt) {
            Vec3 to = i_mesh.vertices[pIt] + 0.02*i_mesh.normals[pIt];
            drawVector(i_mesh.vertices[pIt], to);
        }

    }

}



void draw () {

    if(displayMode == LIGHTED || displayMode == LIGHTED_WIRE){

        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_LIGHTING);

    }  else if(displayMode == WIRE){

        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        glDisable (GL_LIGHTING);

    }  else if(displayMode == SOLID ){
        glDisable (GL_LIGHTING);
        glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

    }

    if( display_unit_sphere ){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(unit_sphere);
    }

    if (display_unit_cube){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(unit_cube);
    }

    if (display_unit_tore){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(unit_tore);
    }

    if (display_unit_super_shape){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(unit_super_shape);
    }

    if( display_loaded_mesh ){
        glColor3f(0.8,0.8,1);
        drawTriangleMesh(mesh);
    }

    if(displayMode == SOLID || displayMode == LIGHTED_WIRE){
        glEnable (GL_POLYGON_OFFSET_LINE);
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth (1.0f);
        glPolygonOffset (-2.0, 1.0);

        glColor3f(0.,0.,0.);
        if( display_unit_sphere )
            drawTriangleMesh(unit_sphere);

        if( display_loaded_mesh )
            drawTriangleMesh(mesh);

        glDisable (GL_POLYGON_OFFSET_LINE);
        glEnable (GL_LIGHTING);
    }


}

void changeDisplayMode(){
    if(displayMode == LIGHTED)
        displayMode = LIGHTED_WIRE;
    else if(displayMode == LIGHTED_WIRE)
        displayMode = SOLID;
    else if(displayMode == SOLID)
        displayMode = WIRE;
    else
        displayMode = LIGHTED;
}

void display() {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply ();
    draw ();
    glFlush ();
    glutSwapBuffers ();
    zaman = 0.5 + zaman;
    globalSuper = sin(zaman);
}

void idle () {
    glutPostRedisplay ();
}

void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'f':
        if (fullScreen == true) {
            glutReshapeWindow (SCREENWIDTH, SCREENHEIGHT);
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;


    case 'w': //Change le mode d'affichage
        changeDisplayMode();
        break;


    case 'n': //Press n key to display normals
        display_normals = !display_normals;
        break;

    case '1': //Toggle loaded mesh display
        display_loaded_mesh = !display_loaded_mesh;
        break;

    case 'c': //Toggle unit sphere mesh display
        if (cpt % 3 == 0){
            display_unit_tore = !display_unit_tore;
            if (display_unit_cube) display_unit_cube = !display_unit_cube;
            if (display_unit_sphere) display_unit_sphere = !display_unit_sphere;
        }
        else if((cpt+1)%3 == 0){
            display_unit_sphere = !display_unit_sphere;
            if (display_unit_cube) display_unit_cube = !display_unit_cube;
            if (display_unit_tore) display_unit_tore = !display_unit_tore;
        }
        else{
            display_unit_cube = !display_unit_cube;
            if (display_unit_sphere) display_unit_sphere = !display_unit_sphere;
            if (display_unit_tore) display_unit_tore = !display_unit_tore;
        }
        cpt ++;
        break;

    case '-':
        nY--;
        nX--;
        setUnitSphere( unit_sphere , nX, nY);
        setUnitCube( unit_cube, nX, nY);
        break;

    case '+':
        nY++;
        nX++;
        setUnitSphere( unit_sphere , nX, nY);
        setUnitCube( unit_cube, nX, nY);
        break;

    case 's':
        display_unit_super_shape = !display_unit_super_shape;
        if (display_unit_sphere) display_unit_sphere = !display_unit_sphere;
        if (display_unit_tore) display_unit_tore = !display_unit_tore;
        if (display_unit_cube) display_unit_cube = !display_unit_cube;
        break;

    default:
        break;
    }
    idle ();
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
    idle ();
}

void motion (int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate (x, y);
    }
    else if (mouseMovePressed == true) {
        camera.move ((x-lastX)/static_cast<float>(SCREENWIDTH), (lastY-y)/static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom (float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize (w, h);
}



int main (int argc, char ** argv) {
    if (argc > 2) {
        exit (EXIT_FAILURE);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ("TP HAI714I");

    init ();
    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);
    key ('?', 0, 0);

    //Unit sphere mesh loaded with precomputed normals
    openOFF("data/unit_sphere_n.off", mesh.vertices, mesh.normals, mesh.triangles);

    //Uncomment to see other meshes
    //openOFF("data/elephant_n.off", mesh.vertices, mesh.normals, mesh.triangles);
    setUnitSphere( unit_sphere , nX, nY);
    setUnitCube( unit_cube );
    setUnitTore( unit_tore );
    setUnitSuperShape( unit_super_shape);
    
    
    glutMainLoop ();
    return EXIT_SUCCESS;
}


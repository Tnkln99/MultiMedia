// --------------------------------------------------------------------------
// gMini,
// a minimal Glut/OpenGL app to extend                              
//
// Copyright(C) 2007-2009                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but WITHOUT ANY WARRANTY; without even the implied warranty of             
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
//                                                                          
// --------------------------------------------------------------------------
uniform float ambientRef;
uniform float diffuseRef;
uniform float specRef;
uniform float shininess;
uniform float time;

varying vec4 p;
varying vec3 n;

float hash(float p) { p = fract(p * 0.011); p *= p + 7.5; p *= p + p; return fract(p); }
float hash(vec2 p) {vec3 p3 = fract(vec3(p.x, p.y, p.x) * 0.13); p3 += dot(p3, p3.yzx + 3.333); return fract((p3.x + p3.y) * p3.z); }
 
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}
float noise(float x) {
    float i = floor(x);
    float f = fract(x);
    float u = f * f * (3.0 - 2.0 * f);
    return mix(hash(i), hash(i + 1.0), u);
}
float noise2 (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);
 
    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));
 
    vec2 u = f * f * (3.0 - 2.0 * f);
 
    return 0; /*mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;*/
}
float noise3(vec3 x) {
    const vec3 step = vec3(110, 241, 171);
 
    vec3 i = floor(x);
    vec3 f = fract(x);
 
    // For performance, compute the base input to a 1D hash from the integer part of the argument and the
    // incremental change to the 1D based on the 3D -> 1D wrapping
    float n = dot(i, step);
 
    vec3 u = f * f * (3.0 - 2.0 * f);
    return mix(mix(mix( hash(n + dot(step, vec3(0, 0, 0))), hash(n + dot(step, vec3(1, 0, 0))), u.x),
                   mix( hash(n + dot(step, vec3(0, 1, 0))), hash(n + dot(step, vec3(1, 1, 0))), u.x), u.y),
               mix(mix( hash(n + dot(step, vec3(0, 0, 1))), hash(n + dot(step, vec3(1, 0, 1))), u.x),
                   mix( hash(n + dot(step, vec3(0, 1, 1))), hash(n + dot(step, vec3(1, 1, 1))), u.x), u.y), u.z);
}
 
float fbm (in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitud = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < 6; i++) {
        value += amplitud * noise(st);
        st *= 2.;
        amplitud *= .5;
    }
    return value;
}
float fbm3 (in vec3 st) {
    // Initial values
    float value = 0.0;
    float amplitud = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < 6; i++) {
        value += amplitud * noise3(st);
        st *= 2.;
        amplitud *= .5;
    }
    return value;
}
 
vec2 fbmToVec2(in vec2 st) {
    return vec2(fbm(st), fbm(st + 100.0));
}
vec2 fbm3ToVec2(in vec3 st) {
    return vec2(fbm3(st), fbm3(st + 100.0));
}
vec3 fbmToVec3(in vec2 st) {
    return vec3(fbm(st), fbm(st + 18.0), fbm(st - 10.0));
}
vec3 fbm3ToVec3(in vec3 st) {
    return vec3(fbm3(st), fbm3(st + 18.0), fbm3(st - 10.0));
}



void main (void) {
    vec3 P = vec3 (gl_ModelViewMatrix * p); //Position du point à éclairer
    vec3 N = normalize (gl_NormalMatrix * n); //Normal en ce point
    vec3 V = normalize (-P); //Vecteur de vue
    float timeIntervale = cos(time);

    float coeffBruit = 5.00; 
    vec3 fragment = coeffBruit * P;
    vec3 monRandomVec = fbm3ToVec3(fragment);
    //N += monRandomVec;  // decommenter pour faire de bruit

    /*float xRotateMatrice[4][4] = {1,0,0,0
                                0, cos(20), -sin(20), 0
                                0, sin(20), cos(20), 0
                                0,0,0,1};*/
    
    vec4 refAmb = ambientRef * gl_LightModel.ambient*gl_FrontMaterial.ambient ;
    vec4 lightContribution = refAmb;
    for(int i = 0; i < 3; i++){
        
        vec3 L = normalize(gl_LightSource[i].position.xyz - P); //Vecteur de la lumière
        vec3 R = 2.00*dot(N,L)*N - L; //Vecteur de réflexion

              
        float toonShading;

        if (max(dot(L,N),0.0) > 0.5)//pour cartoonish look
            toonShading = 1.0;
        else if (max(dot(L,N),0.0) > 0.3)
            toonShading = 0.5;
        else if ((max(dot(L,N),0.0) > 0.0))
            toonShading = 0.33;
        else 
            toonShading = 0.1;

        vec4 refDiff = diffuseRef * gl_LightSource[i].diffuse * gl_FrontMaterial.diffuse * max( dot(L,N) ,0.0);
        lightContribution += refDiff;

        vec4 refSpec = specRef * gl_LightSource[i].specular * gl_FrontMaterial.specular * pow(max(dot(R,V),0.0),shininess);
        lightContribution += refSpec;
    
        //lightContribution *= toonShading;
    }
    
    ////////////////////////////////////////////////
    //Eclairage de Phong à calculer en utilisant
    ///////////////////////////////////////////////
    // gl_LightSource[i].position.xyz Position de la lumière i
    // gl_LightSource[i].diffuse Couleur diffuse de la lumière i
    // gl_LightSource[i].specular Couleur speculaire de la lumière i
    // gl_FrontMaterial.diffuse Matériaux diffus de l'objet
    // gl_FrontMaterial.specular Matériaux speculaire de l'objet


    float rouge = lightContribution.x;
    float green = lightContribution.y;
    float blue = lightContribution.z;

    double nombreSeuillage = 2.000;

    int aChangeR = 0;
    int aChangeB = 0;
    int aChangeG = 0;

    for(int i = 0;i < nombreSeuillage;i++){    
        if(lightContribution.r > i/nombreSeuillage && lightContribution.r < (i+1)/nombreSeuillage){
            rouge = (i+1)/nombreSeuillage;
            //aChangeR = 1;
        }
        if(lightContribution.b > i/nombreSeuillage && lightContribution.b < (i+1)/nombreSeuillage){
            blue = (i+1)/nombreSeuillage;
            //aChangeB = 1;
        }
        if(lightContribution.g > i/nombreSeuillage && lightContribution.g < (i+1)/nombreSeuillage){
            green = (i+1)/nombreSeuillage;
            //aChangeG = 1;
        }
    }
    //gl_FragColor =vec4(lightContribution.xyz,1.0);
    gl_FragColor =vec4(rouge , green , blue , 1.0);
    
}
 

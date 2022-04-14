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

varying vec4 p;
varying vec3 n;

void main (void) {
    vec3 P = vec3 (gl_ModelViewMatrix * p); //Position du point à éclairer
    vec3 N = normalize (gl_NormalMatrix * n); //Normal en ce point
    vec3 V = normalize (-P); //Vecteur de vue
    
    vec4 refAmb = ambientRef * gl_LightModel.ambient*gl_FrontMaterial.ambient ;
    vec4 lightContribution;

    for(int i = 0; i < 3; i++){
        vec3 L = P - gl_LightSource[i].position.xyz; //Vecteur de la lumière
        vec3 R = 2*dot(N,L)*N - L; //Vecteur de réflexion
        vec4 refDiff = diffuseRef * gl_LightSource[i].diffuse*gl_FrontMaterial.diffuse*max(dot(normalize(L),N),0.0);
        float toonShading;
        if (max(dot(normalize(L),N),0.0) > 0.5)//pour cartoonish look
            toonShading = 1.0;
        else if (max(dot(normalize(L),N),0.0) > 0.3)
            toonShading = 0.5;
        else if ((max(dot(normalize(L),N),0.0) > 0.0))
            toonShading = 0.33;
        else 
            toonShading = 0.1;
        
        vec4 refSpec = specRef * gl_LightSource[i].specular*gl_FrontMaterial.specular*pow(max(dot(normalize(R),V),0.0),shininess);

        lightContribution += (refAmb + refDiff + refSpec);//*toonShading; //add color coeff for Toon Shading
    }
    
    ////////////////////////////////////////////////
    //Eclairage de Phong à calculer en utilisant
    ///////////////////////////////////////////////
    // gl_LightSource[i].position.xyz Position de la lumière i
    // gl_LightSource[i].diffuse Couleur diffuse de la lumière i
    // gl_LightSource[i].specular Couleur speculaire de la lumière i
    // gl_FrontMaterial.diffuse Matériaux diffus de l'objet
    // gl_FrontMaterial.specular Matériaux speculaire de l'objet

    //Pour rouge 
    float rouge = lightContribution.r; 
    if (rouge > 0.666){
        rouge = 1.0;
    }
    else if (rouge > 0.333){
        rouge = 0.666;
    }
    else{
        rouge = 0.333;
    }
    //Pour vert
    float green = lightContribution.y;
    if (green > 0.666){
        green = 1.0;
    }
    else if (green > 0.333){
        green = 0.666;
    }
    else{
        green = 0.333;
    }
    //Pour bleu 
    float blue = lightContribution.z;
    if (blue > 0.666){
        blue = 1.0;
    }
    else if (blue > 0.333){
        blue = 0.666;
    }
    else{
        blue = 0.333;
    }

    

    gl_FragColor =vec4 (rouge,blue,green, 1.0);
    //gl_FragColor =vec4(lightContribution.xyz,1.0);
    
}
 

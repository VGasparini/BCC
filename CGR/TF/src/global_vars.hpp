#ifndef __RT_GLOBAL__
#define __RT_GLOBAL__

#include "commons.hpp"
#include "objects.hpp"

unsigned W = 640, H = 480;
unsigned rW = W, rH = H;
unsigned linesCompleted;
char outfile[256];
bool toFile = false;
bool rerender = false;
bool die = false;
bool resize = false;
sf::Image image;
sf::Texture texture;
sf::Uint8 *pixels; // 0 - 255 para cada canal (RGBA)
sf::Sprite sprite;
std::mutex mut;
std::mutex rmut;
std::mutex dmut;

unsigned MAXTRACE = 2; // Maximum trace level
unsigned SURFACE_SAMPLES = 1; // For sampling roughness
unsigned SHADOW_RES = 1;
double LIGHT_FALLOFF = 34.0;

XYZ AmbientLight  = {{  0.20, 0.20,  0.20}};
XYZ camangle	  = {{  0.00, 0.00,  0.00}};
XYZ camlook       = {{  0.04, 0.00,  0.00}};
XYZ campos        = {{  0.00, 9.00,-70.00}};
Matrix camrotatematrix, camlookmatrix;
double zoom       = 1.0;
double contrast   = 3.2;

std::vector<Plane> Planes;
std::vector<Sphere> Spheres;
std::vector<LightSource> Lights;

#endif

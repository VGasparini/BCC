#ifndef __RT_HEADERS__
#define __RT_HEADERS__

#include "commons.hpp"
#include "utilities.hpp"
#include "objects.hpp"
#include <cstdio>
#include <math.h>
#include <cstdlib>
#include <ctime>

/* Actual raytracing! */

int RayFindObstacle	(const XYZ& eye, const XYZ& dir, double& HitDist, int& HitIndex,
	 XYZ& HitLoc, XYZ& HitNormal)
{
	double ERR_LOW = 1e-6;
	unsigned NumSpheres = Spheres.size();
	unsigned NumPlanes  = Planes.size();
	
	int HitType = -1;
	for(unsigned i=0; i<NumSpheres; ++i)
	{
		XYZ V (eye - Spheres[i].center);
		double r = Spheres[i].radius,
			DV = dir.Dot(V),
			D2 = dir.Squared(),
			SQ = DV*DV
			   - D2*(V.Squared() - r*r);
		if(SQ < ERR_LOW) continue;
		double SQt = sqrt(SQ),
			Dist = MIN(-DV-SQt,
						-DV+SQt) / D2;
		if(Dist<ERR_LOW || Dist >= HitDist)
			continue;
		HitType = 1; HitIndex = i;
		HitDist = Dist;
		HitLoc = eye + (dir * HitDist);
		HitNormal =
			(HitLoc - Spheres[i].center)
				* (1/r);
	}
	for(unsigned i=0; i<NumPlanes; ++i)
	{
		double DV = -Planes[i].normal.Dot(dir);
		if(DV > -ERR_LOW) continue;
		double D2 =
			Planes[i].normal.Dot(eye),
			Dist = (D2+Planes[i].offset) / DV;
		if(Dist<ERR_LOW || Dist>HitDist)
			continue;
		HitType = 0; HitIndex = i;
		HitDist = Dist;
		HitLoc = eye + (dir * HitDist);
		HitNormal = -Planes[i].normal;
	}
	return HitType;
}

XYZ *ArealightVectors;
void InitArealightVectors()
{
	if (ArealightVectors != NULL) delete ArealightVectors;
	ArealightVectors = new XYZ[SHADOW_RES];
	for(unsigned i=0; i<SHADOW_RES; ++i)
		for(unsigned n=0; n<3; ++n)
			ArealightVectors[i].d[n] =
				2.0 * (rand() / double(RAND_MAX) - 0.5);
}

XYZ refract(XYZ I, XYZ N, float ior) 
{ 
	float cosi = MIN(1.0, MAX(-1.0, I.Dot(N)));
	float etai, etat; 
	XYZ n = N;

	if(cosi > 0.0)
	{
	    etai = ior;
	    etat = 1.0;
	    n = -N;
	}
	else
	{
	    etai = 1.0;
	    etat = ior;
	    cosi = -cosi;
	}

	float eta = etai / etat;
	float k = 1 - eta * eta * (1 - cosi * cosi); 
	return k < 0 ? XYZ{{0,0,0}} : I * eta + n * (eta * cosi - sqrtf(k));
} 


float fresnel(XYZ I, XYZ N, float ior) 
{ 
	float kr;
	float cosi = MIN(1.0, MAX(-1.0, I.Dot(N)));
	float etai = 1.0, etat = ior; 
	if (cosi > 0.0)
	{
		etai = ior;
		etat = 1.0;
	} 
	// Compute sini using Snell's law
	float sint = etai / etat * sqrtf(MAX(0.0, 1 - cosi * cosi));
	// Total internal reflection
	if (sint >= 1)
	{ 
		kr = 1;
 	} 
	else
	{ 
		float cost = sqrtf(MAX(0.0, 1 - sint * sint)); 
		cosi = fabsf(cosi); 
		float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost)); 
		float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost)); 
		kr = (Rs * Rs + Rp * Rp) / 2; 
	} 
	return kr;
}

void RayTrace(XYZ& resultcolor, const XYZ& eye, const XYZ& dir, int k)
{
	unsigned NumLights = Lights.size();

	unsigned XadrexSize = 4;

	double HitDist = 1e6;
	XYZ HitLoc, HitNormal;
	int HitIndex, HitType;
	HitType = RayFindObstacle(eye, dir, HitDist, HitIndex, HitLoc, HitNormal);
	if(HitType != -1)
	{
		XYZ DiffuseLight {{0,0,0}}, SpecularLight {{0,0,0}},
		    RefractionLight {{0,0,0}}, Pigment;
		double Roughness, Shininess, MtlRefraction, Sf = 1.0, Rf = 0.0;
		bool MtlIsTranslucent = false;
		switch (HitType)
		{
			case 0:
				Roughness = Planes[HitIndex].mtl.roughness;
				Pigment = Planes[HitIndex].mtl.color;
				if (HitIndex == 3) {
					XYZ pos(HitLoc);
					if (((int)pos.d[0]/XadrexSize + (int)pos.d[2]/XadrexSize)%2) {
						Pigment = {{0, 0, 0}};
					} else {
						Pigment = {{0.8, 0.8, 0.8}};
					}
				}
				Shininess = Planes[HitIndex].mtl.shininess;
				break;
			case 1:
				Roughness = Spheres[HitIndex].mtl.roughness;
				Pigment = Spheres[HitIndex].mtl.color;
				Shininess = Spheres[HitIndex].mtl.shininess;
				MtlIsTranslucent = Spheres[HitIndex].mtl.translucent;
				MtlRefraction = Spheres[HitIndex].mtl.refraction;
				break;
		}

		// DIRECT
		for(unsigned i=0; i<NumLights; i++)
		{
			for(unsigned j=0; j<SHADOW_RES; ++j)
			{
				XYZ V((Lights[i].center + ArealightVectors[j]) - HitLoc);
				double LightDist = V.Len();
				V.Normalize();
				double DiffuseEffect = HitNormal.Dot(V) / (double)SHADOW_RES;
				double Attenuation = (1 + pow(LightDist / LIGHT_FALLOFF, 2.0));
				DiffuseEffect /= Attenuation;
				if (DiffuseEffect > 1e-3)
				{
					double ShadowDist = LightDist - 1e-4;
					XYZ a,b;
					int q, t = RayFindObstacle(HitLoc + V*1e-4, V, ShadowDist, q, a, b);
					if (t == -1)
						DiffuseLight += Lights[i].colour * DiffuseEffect;
				}
			}
		}
		// END DIRECT

		// SPECULAR
		if(k > 1)
		{
			// Add specular light/reflection, unless recursion depth is at max
			XYZ V(-dir); V.MirrorAround(HitNormal);
			int roughnessSamples = SURFACE_SAMPLES;
			int decay = MAX(MAXTRACE - k, 0);
			int kn = MAX(roughnessSamples - decay, 1);
			XYZ resultColor {{0.0,0.0,0.0}}, auxColor, auxV;
			while (kn--)
			{
				auxV.Set(rand()%1001 / 500.0 - 1.0,
						 rand()%1001 / 500.0 - 1.0,
						 rand()%1001 / 500.0 - 1.0);
				auxV.Normalize();
				if (auxV.Dot(V) < 0)
					auxV *= -1;
				auxV *= Roughness;
				RayTrace(auxColor, HitLoc + HitNormal*1e-12, V + auxV, k-1);
				resultColor += auxColor;
			}
			resultColor   *= 1.0/double(roughnessSamples);
			DiffuseLight  *= 1.0 - Shininess;
			SpecularLight  = resultColor * Shininess;
		}
		// END SPECULAR

		// REFRACTION
		if(MtlIsTranslucent)
		{
			HitNormal.Normalize();
			XYZ auxColor;
			double movRay = 0;
			XYZ V = refract(dir, HitNormal, MtlRefraction);
			V.Normalize();
			if (V.Dot(HitNormal) > 0)
				movRay = -1e-4;
			else
				movRay =  1e-4;
			RayTrace(auxColor, HitLoc + V*movRay, V, k-1);
			RefractionLight = auxColor;
			Sf = fresnel(dir, HitNormal, MtlRefraction);
			Rf = 1.0 - Sf;
		}
		// END REFRACTION

		resultcolor = (DiffuseLight + 
					   (SpecularLight * Sf + RefractionLight * Rf)
					  ) * Pigment;
	}
}

void progress()
{
	float progress, estimate;
	sf::Clock clock;
	sf::Time start = clock.getElapsedTime(), elapsed;
	while (linesCompleted < rH)
	{
		progress = (linesCompleted * 100) / float(rH);
		elapsed  = clock.getElapsedTime();
		estimate = (elapsed - start).asSeconds() * (100.0/progress);
		estimate -= elapsed.asSeconds(); 

		printf("\r                                                        "
			   "\rCompleted: %5.1f%%; Remaining: %5.1f seconds",
			   progress, estimate);
		fflush(stdout);
		sleep(53);
	}
	estimate = clock.getElapsedTime().asSeconds();
	printf("\r                                                           "
		   "\rFrame finished! Time: %.3f seconds\n", estimate);
	fflush(stdout);
}

/* RayTracing */
void render(unsigned W, unsigned H, sf::Uint8 *pixels)
{
	double AR = W/double(H);
	linesCompleted = 0;
	std::thread progressThread(progress);

	// Rotate it around the center
	camrotatematrix.InitRotate(camangle);
	camrotatematrix.Transform(campos);
	camlookmatrix.InitRotate(camlook);

  #pragma omp parallel for collapse(2)
	for(unsigned y=0; y<H; ++y)
	{
		for(unsigned x=0; x<W; ++x)
		{
			XYZ camray = {{ x / double(W) - 0.5,
							y / double(H) - 0.5,
							zoom }};
			camray.d[0] *= AR; // Aspect ratio correction
			camray.Normalize();
			camlookmatrix.Transform(camray);
			XYZ campix;
			RayTrace(campix, campos, camray, MAXTRACE);
			campix *= 0.5;
			campix = campix * contrast;
			campix.ClampWithDesaturation();

			// Draw pixel
			{
				pixels[((y*W) + x)*4 + 0] = unsigned(campix.d[0]*255); // Red
				pixels[((y*W) + x)*4 + 1] = unsigned(campix.d[1]*255); // Green
				pixels[((y*W) + x)*4 + 2] = unsigned(campix.d[2]*255); // Blue
				pixels[((y*W) + x)*4 + 3] = 255; // Alpha
			}
			#pragma omp critical
			{
				#pragma omp flush(linesCompleted)
				if (x == W-1) linesCompleted++;
				#pragma omp flush(linesCompleted)
			}
		}
	}

	progressThread.join();
}

#endif

#ifndef __RT_OBJECTS__
#define __RT_OBJECTS__

#include "commons.hpp"
#include "material.hpp"

struct Plane { XYZ normal; double offset; Material mtl; };
struct Sphere { XYZ center; double radius; Material mtl; };
struct LightSource { XYZ center, colour; };

#endif

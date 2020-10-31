#ifndef __RT_SCENE__
#define __RT_SCENE__

#include "objects.hpp"

void InitDefaultScene()
{
	Planes.push_back({{{ 1, 0, 0}}, -30, {{{1.00, 0.25, 0.25}}, 0.20, 0.11, true, 1}});
	Planes.push_back({{{ 0,-1, 0}}, -30, {{{1.00, 1.00, 1.00}}, 0.20, 0.11, true, 1}});
	Planes.push_back({{{-1, 0, 0}}, -30, {{{0.25, 1.00, 0.25}}, 0.20, 0.11, true, 1}});
	Planes.push_back({{{ 0, 1, 0}}, -30, {{{0.06, 0.06, 0.05}}, 0.40, 0.05, true, 1}});
	Planes.push_back({{{ 0, 0, 1}}, -30, {{{0.25, 0.25, 1.00}}, 0.20, 0.11, true, 1}});
	Planes.push_back({{{ 0, 0,-1}}, -90, {{{1.00, 0.25, 1.00}}, 0.20, 0.11, true, 1}});
}

#endif

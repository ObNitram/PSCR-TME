#pragma once

#include "Vec3D.hpp"

namespace pr {

// Un POD (plain old data) qui lie la camera au point de l'ecran.
class Rayon {
public:
	Vec3D ori; // origine
	Vec3D dest; // destination

	Rayon(const Vec3D & ori, const Vec3D & dest) : ori(ori),dest(dest) {}
};

} /* namespace pr */



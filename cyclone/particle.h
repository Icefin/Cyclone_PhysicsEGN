#pragma once
#include "core.h"

namespace cyclone
{
	class Particle
	{
		protected:
			Vector3 position;
			Vector3 velocity;
			Vector3 acclertation;
			real damping;
			real inverseMass;
	};
}
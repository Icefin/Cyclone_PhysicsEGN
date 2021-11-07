#pragma once
#include "core.h"

namespace cyclone
{
	class Particle
	{
		protected:
			Vector3 position;
			Vector3 velocity;
			Vector3 acceleration;
			real damping;
			real inverseMass;

		public :
			Vector3 getPosition() const;
			
			void setPosition(real x, real y, real z);
			void setVelocity(real x, real y, real z);
			void setAcceleration(real x, real y, real z);
			void setDamping(real damping);
			void setMass(real mass);

			void integrate(real duration);
			

	};
}
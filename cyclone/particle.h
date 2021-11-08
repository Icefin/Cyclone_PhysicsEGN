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

			Vector3 forceAccum;

		public :
			Vector3 getPosition() const;
			Vector3 getVelocity() const;
			real getMass() const;

			void setPosition(real x, real y, real z);
			void setVelocity(real x, real y, real z);
			void setAcceleration(real x, real y, real z);
			void setDamping(real damping);
			void setMass(real mass);

			bool hasFiniteMass();

			void integrate(real duration);
			void addForce(const Vector3& force);
			void clearAccumulator();
	};
}
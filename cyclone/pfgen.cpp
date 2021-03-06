#include "pfgen.h"

using namespace cyclone;

//힘 발생기는 프레임마다 업데이트 하기 전에 호출되어야한다.
void ParticleForceRegistry::updateForces(real duration)
{
	Registry::iterator i = registrations.begin();	//vector의 시작점을 가리킴
	for (; i != registrations.end(); i++)
	{
		i->fg->updateForce(i->particle, duration);
	}
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{

}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{

}

void ParticleForceRegistry::clear()
{

}

#pragma region ParticleGravity

ParticleGravity::ParticleGravity(const Vector3& gravity)
{
	this->gravity = gravity;
}

void ParticleGravity::updateForce(Particle* particle, real duration)
{
	if (!particle->hasFiniteMass()) return;
	particle->addForce(gravity * particle->getMass());
}

#pragma endregion

#pragma region ParticleDrag

ParticleDrag::ParticleDrag(real k1, real k2)
{
	this->k1 = k1;
	this->k2 = k2;
}

void ParticleDrag::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getVelocity();

	real dragCoeff = force.magnitude();
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
	
	force.normalize();
	force *= -dragCoeff;	//f_drag = -v(k1*|v|+k2*|v|^2)
	particle->addForce(force);
}
#pragma endregion

#pragma region ParticleUpLift
ParticleUpLift::ParticleUpLift(const Vector3& position, Vector3& force, real distance)
{
	this->position = position;
	this->force = force;
	this->distance = distance;
}

void ParticleUpLift::updateForce(Particle* particle, real duration)
{
	Vector3 pos_particle = particle->getPosition();
	real distance = sqrt(pow((pos_particle.x - position.x), 2)+pow((pos_particle.z - position.z), 2));
	
	if (distance <= this->distance)
	{
		particle->addForce(force);
	}
}
#pragma endregion

#pragma region ParticleSink
ParticleSink::ParticleSink(const Vector3& position, real power)
{
	this->position = position;
	this->power = power;
}

void ParticleSink::updateForce(Particle* particle, real duration)
{
	Vector3 pos_particle = particle->getPosition();
	Vector3 direction = Vector3((position.x - pos_particle.x), (position.y - pos_particle.y), (position.z - pos_particle.z));
	direction.normalize();

	Vector3 force = (direction * power) / pow(direction.magnitude(), 2);

	if (force.magnitude() <= power)
	{
		particle->addForce(force);
	}
}
#pragma endregion

#pragma region ParticleSpring
ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength)
{
	this->other = other;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void ParticleSpring::updateForce(Particle* particle, real duration)
{
	Vector3 origin = other->getPosition();
	Vector3 pos_mass = particle->getPosition();
	Vector3 force = origin - pos_mass;

	real magnitude = force.magnitude();
	magnitude = real_abs(magnitude - restLength);
	magnitude *= springConstant;

	force.normalize();
	force *= -magnitude;		//f_spring = -k(l' - l) by Hooke's law
	particle->addForce(force);
}
#pragma endregion

#pragma region ParticleAnchoredSpring
ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength)
{
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void ParticleAnchoredSpring::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getPosition() - *anchor;	//anchor to particle dir

	real magnitude = force.magnitude();
	magnitude = (restLength - magnitude) * springConstant;	//if mag > rest : dir to anchor

	force.normalize();
	force *= magnitude;
	particle->addForce(force);

}
#pragma endregion

#pragma region ParticleBungee
ParticleBungee::ParticleBungee(Particle* other, real springConstant, real restLength)
{
	this->other = other;
	this->springConstant = springConstant;
	this->restLength = restLength;
}
void ParticleBungee::updateForce(Particle* particle, real duration)
{
	Vector3 force = particle->getPosition() - other->getPosition(); //other to particle dir

	real magnitude = force.magnitude();
	if (magnitude <= restLength) return;	//mag < rest이면 힘x
	
	magnitude = springConstant * (magnitude - restLength);
	force.normalize();
	force *= magnitude;
	particle->addForce(force);
}
#pragma endregion

#pragma region ParticleBuoyancy
ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f)
{
	this->maxDepth = maxDepth;
	this->volume = volume;
	this->waterHeight = waterHeight;
	this->liquidDensity = liquidDensity;
}
void ParticleBuoyancy::updateForce(Particle* particle, real duration)
{
	real depth = particle->getPosition().y;

	if (depth >= waterHeight + maxDepth) return;	//물 밖이라면 힘x

	Vector3 force(0, 0, 0);

	//물체가 물 속에 완전히 잠긴 경우
	if (depth <= waterHeight - maxDepth)
	{
		force.y = liquidDensity * volume;
		particle->addForce(force);
		return;
	}

	force.y = liquidDensity * volume * (depth - maxDepth - waterHeight) / (2 * maxDepth);	//volume_ratio = (y - y_w - y_f / 2y_f)
	particle->addForce(force);
}
#pragma endregion



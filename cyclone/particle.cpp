#include <assert.h>
#include "particle.h"

using namespace cyclone;

#pragma region Get/Set
Vector3 Particle::getPosition() const
{
	return this->position;
}
Vector3 Particle::getVelocity() const
{
	return this->velocity;
}
Vector3 Particle::getAcceleration() const
{
	return this->acceleration;
}
real Particle::getMass() const
{
	return 1 / this->inverseMass;
}
real Particle::getInverseMass() const
{
	return inverseMass;
}

void Particle::setPosition(real x, real y, real z)
{
	this->position = Vector3(x, y, z);
}
void Particle::setVelocity(real x, real y, real z)
{
	this->velocity = Vector3(x, y, z);
}
void Particle::setVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}
void Particle::setAcceleration(real x, real y, real z)
{
	this->acceleration = Vector3(x, y, z);
}
void Particle::setDamping(real damping)
{
	this->damping = damping;
}
void Particle::setMass(real mass)
{
	assert(mass > 0.0f);
	this->inverseMass = 1 / mass;
}

#pragma endregion


void Particle::integrate(real duration)
{
	if (inverseMass <= 0.0f) return;

	assert(duration > 0.0);

	//위치를 업데이트한다.
	//프레임당 time interval을 가정시 가속도에 의한 영향은 적으므로(t^2항) 무시한다.
	position.addScaledVector(velocity, duration); // p = p + duration * p'

	//가속도로부터 속도를 업데이트한다.
	Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);	//a = a + F/m
	velocity.addScaledVector(resultingAcc, duration);	//p' = p' + duration * p"

	//드래그를 적용한다.
	velocity *= real_pow(damping, duration);

	//힘 항목을 지운다.
	clearAccumulator();
}

void Particle::addForce(const Vector3& force)
{
	forceAccum += force;
}

bool Particle::hasFiniteMass()
{
	if (this->inverseMass == 0.0f) return false;
	
	return true;
}

void Particle::clearAccumulator()
{
	forceAccum.clear();
}
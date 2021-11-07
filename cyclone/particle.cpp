#include <assert.h>
#include "particle.h"

using namespace cyclone;

Vector3 Particle::getPosition() const
{
	return this->position;
}

void Particle::setPosition(real x, real y, real z)
{
	this->position = Vector3(x, y, z);
}
void Particle::setVelocity(real x, real y, real z)
{
	this->velocity = Vector3(x, y, z);
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

void Particle::integrate(real duration)
{
	if (inverseMass <= 0.0f) return;

	assert(duration > 0.0);

	//위치를 업데이트한다.
	//프레임당 time interval을 가정시 가속도에 의한 영향은 적으므로(t^2항) 무시한다.
	position.addScaledVector(velocity, duration); // p = p + duration * p'

	//가속도로부터 속도를 업데이트한다.
	Vector3 resultingAcc = acceleration;	//이거 필요한건가??
	velocity.addScaledVector(resultingAcc, duration);	//p' = p' + duration * p"

	//드래그를 적용한다.
	velocity *= real_pow(damping, duration);

	//힘 항목을 지운다.
	clearAccumulator();		//후에 추가 필요.
}


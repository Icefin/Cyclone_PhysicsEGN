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

	//��ġ�� ������Ʈ�Ѵ�.
	//�����Ӵ� time interval�� ������ ���ӵ��� ���� ������ �����Ƿ�(t^2��) �����Ѵ�.
	position.addScaledVector(velocity, duration); // p = p + duration * p'

	//���ӵ��κ��� �ӵ��� ������Ʈ�Ѵ�.
	Vector3 resultingAcc = acceleration;
	resultingAcc.addScaledVector(forceAccum, inverseMass);	//a = a + F/m
	velocity.addScaledVector(resultingAcc, duration);	//p' = p' + duration * p"

	//�巡�׸� �����Ѵ�.
	velocity *= real_pow(damping, duration);

	//�� �׸��� �����.
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
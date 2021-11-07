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

	//��ġ�� ������Ʈ�Ѵ�.
	//�����Ӵ� time interval�� ������ ���ӵ��� ���� ������ �����Ƿ�(t^2��) �����Ѵ�.
	position.addScaledVector(velocity, duration); // p = p + duration * p'

	//���ӵ��κ��� �ӵ��� ������Ʈ�Ѵ�.
	Vector3 resultingAcc = acceleration;	//�̰� �ʿ��Ѱǰ�??
	velocity.addScaledVector(resultingAcc, duration);	//p' = p' + duration * p"

	//�巡�׸� �����Ѵ�.
	velocity *= real_pow(damping, duration);

	//�� �׸��� �����.
	clearAccumulator();		//�Ŀ� �߰� �ʿ�.
}


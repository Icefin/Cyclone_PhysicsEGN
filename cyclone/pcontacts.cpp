#include "pcontacts.h"

using namespace cyclone;

void ParticleContact::resolve(real duration)
{
	resolveVelocity(duration);
	resolveInterpenetration(duration);
}

void ParticleContact::resolveInterpenetration(real duration)
{
	if (penetration <= 0) return;

	real totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	if (totalInverseMass <= 0) return;

	Vector3 movePerIMass = contactNormal * (penetration / totalInverseMass);

	particleMovement[0] = movePerIMass * particle[0]->getInverseMass();
	if (particle[1])
	{
		particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
	}
	else
	{
		particleMovement[1].clear();
	}

	particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);
	if(particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
	}
}

real ParticleContact::calculateSeparatingVelocity() const
{
	Vector3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) relativeVelocity = relativeVelocity - particle[1]->getVelocity();
	return relativeVelocity * contactNormal;
}
void ParticleContact::resolveVelocity(real duration)
{
	real separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0) return;

	real newSepVelocity = -separatingVelocity * restitution;
	//속도가 가속도만에 의한 것인지 검사
	Vector3 accCausedVelocity = particle[0]->getAcceleration();
	if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();

	if (accCausedVelocity < 0)
	{
		newSepVelocity += restitution * accCausedVelocity;

		if (newSepVelocity < 0) newSepVelocity = 0;
	}

	real deltaVelocity = newSepVelocity - separatingVelocity;

	real totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	if (totalInverseMass <= 0) return;

	real impulse = deltaVelocity / totalInverseMass;

	Vector3 impulsePerIMass = contactNormal * impulse;

	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass());

	if (particle[1])
	{
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass());
	}
}
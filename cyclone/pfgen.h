#pragma once
#include <vector>
#include "particle.h"

namespace cyclone
{
	class ParticleForceGenerator
	{
		public:
			virtual void updateForce(Particle* particle, real duration) = 0;
	};

	//�� �߻���� �����ϴ� ��� ������ ��� ����� ����Ѵ�.
	class ParticleForceRegistry
	{
		protected :
			struct ParticleForceRegistration
			{
				Particle* particle;
				ParticleForceGenerator* fg;
			};

			typedef std::vector<ParticleForceRegistration> Registry;
			Registry registrations;

		public :
			//�־��� �� �߻��⸦ �־��� ���ڿ� ���
			void add(Particle* particle, ParticleForceGenerator* fg);
			//�־��� ��ϵ� ���� ��Ͽ��� ����
			void remove(Particle* particle, ParticleForceGenerator* fg);
			//��� ��� �׸�(���Ἲ)�� ����
			void clear();

			//�ش� ������ ���� ������Ʈ�ϵ��� ��� �� �߻��⸦ ȣ��
			void updateForces(real duration);
	};
	//�߷¹߻���
	class ParticleGravity : public ParticleForceGenerator
	{
		Vector3 gravity;

		public :
			ParticleGravity(const Vector3& gravity);
			virtual void updateForce(Particle* particle, real duration);
	};
	//�巡�׹߻���
	class ParticleDrag : public ParticleForceGenerator
	{
		real k1, k2;

		public :
			ParticleDrag(real k1, real k2);
			virtual void updateForce(Particle* particle, real duration);
	};
	//��¹߻���
	class ParticleUpLift : public ParticleForceGenerator
	{
		Vector3 position;
		Vector3 force;
		real distance;

		public :
			ParticleUpLift(const Vector3& position, Vector3& force, real distance);
			virtual void updateForce(Particle* particle, real duration);
	};
	//���߷¹߻���
	class ParticleSink : public ParticleForceGenerator
	{
		Vector3 position;
		real power;

		public :
			ParticleSink(const Vector3& position, real power);
			virtual void updateForce(Particle* particle, real duration);
	};
	//���ڰ� ������
	class ParticleSpring : public ParticleForceGenerator
	{
		Particle* other;
		real springConstant;
		real restLength;

		public :
			ParticleSpring(Particle* other, real springConstant, real restLength);
			virtual void updateForce(Particle* particle, real duration);
	};
	//���� ������
	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
		protected :
			Vector3* anchor;
			real springConstant;
			real restLength;

		public :
			ParticleAnchoredSpring(Vector3* anchor, real springConstant, real restLength);
			virtual void updateForce(Particle* particle, real duration);
	};
}

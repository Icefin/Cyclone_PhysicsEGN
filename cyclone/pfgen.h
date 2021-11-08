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

	//힘 발생기와 적용하는 대상 입자의 모든 목록을 기록한다.
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
			//주어진 힘 발생기를 주어진 입자에 등록
			void add(Particle* particle, ParticleForceGenerator* fg);
			//주어진 등록된 쌍을 목록에서 제거
			void remove(Particle* particle, ParticleForceGenerator* fg);
			//모든 등록 항목(연결성)을 제거
			void clear();

			//해당 입자의 힘을 업데이트하도록 모든 힘 발생기를 호출
			void updateForces(real duration);
	};
	//중력발생기
	class ParticleGravity : public ParticleForceGenerator
	{
		Vector3 gravity;

		public :
			ParticleGravity(const Vector3& gravity);
			virtual void updateForce(Particle* particle, real duration);
	};
	//드래그발생기
	class ParticleDrag : public ParticleForceGenerator
	{
		real k1, k2;

		public :
			ParticleDrag(real k1, real k2);
			virtual void updateForce(Particle* particle, real duration);
	};
	//양력발생기
	class ParticleUpLift : public ParticleForceGenerator
	{
		Vector3 position;
		Vector3 force;
		real distance;

		public :
			ParticleUpLift(const Vector3& position, Vector3& force, real distance);
			virtual void updateForce(Particle* particle, real duration);
	};
	//점중력발생기
	class ParticleSink : public ParticleForceGenerator
	{
		Vector3 position;
		real power;

		public :
			ParticleSink(const Vector3& position, real power);
			virtual void updateForce(Particle* particle, real duration);
	};
	//입자간 스프링
	class ParticleSpring : public ParticleForceGenerator
	{
		Particle* other;
		real springConstant;
		real restLength;

		public :
			ParticleSpring(Particle* other, real springConstant, real restLength);
			virtual void updateForce(Particle* particle, real duration);
	};
	//고정 스프링
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

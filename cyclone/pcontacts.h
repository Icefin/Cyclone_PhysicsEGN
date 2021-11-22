#pragma once
#include "core.h"
#include "particle.h"

namespace cyclone
{
	class ParticleContact
	{
		public:
			Particle* particle[2];		//접촉하는 입자들 저장
			real restitution;			//접촉점에서의 반발 계수
			Vector3 contactNormal;		//접촉 방향 벡터

			real penetration;			//물체가 얼마나 겹쳐져 있는지 저장 / 음수 : 겹친부분 x

		protected :
			void resolve(real duration);					//속도 업데이트를 통해 접촉 해소
			real calculateSeparatingVelocity() const;		//분리 속도 계산

		private :
			void resolveVelocity(real duration);			//접촉에 대한 충격량을 계산
			void resolveInterpenetration(real duration);	//겹쳐진 부분 처리
	};
}
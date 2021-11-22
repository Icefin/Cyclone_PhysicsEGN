#pragma once
#include "core.h"
#include "particle.h"

namespace cyclone
{
	class ParticleContact
	{
		public:
			Particle* particle[2];		//�����ϴ� ���ڵ� ����
			real restitution;			//������������ �ݹ� ���
			Vector3 contactNormal;		//���� ���� ����

			real penetration;			//��ü�� �󸶳� ������ �ִ��� ���� / ���� : ��ģ�κ� x

		protected :
			void resolve(real duration);					//�ӵ� ������Ʈ�� ���� ���� �ؼ�
			real calculateSeparatingVelocity() const;		//�и� �ӵ� ���

		private :
			void resolveVelocity(real duration);			//���˿� ���� ��ݷ��� ���
			void resolveInterpenetration(real duration);	//������ �κ� ó��
	};
}
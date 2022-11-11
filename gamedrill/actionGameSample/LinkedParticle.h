#ifndef __LINKED_PARTICLE_H__
#define __LINKED_PARTICLE_H__

#include <vector>
#include "Map.h"
#include "camera.h"

class LinkedParticle;

typedef struct LinkedParticleConnectionInfo
{

	LinkedParticle* m_particle;
	float           m_springLen;
	float           m_springConstant;

}LinkedParticleConnectionInfo;

typedef enum LP_STATE_ENUM
{

	LP_STATE_ENUM_CONSTRAINT,  // �S������Ă���
	LP_STATE_ENUM_SLEEP,       // �X���[�v
	LP_STATE_ENUM_ACTIVE,      // �������i�Փ˂��ĂȂ��j
	LP_STATE_ENUM_ON_GROUND,   // �ڒn���Ă���
	LP_STATE_ENUM_HIT,         // �ǂɃq�b�g���Ă���
	LP_STATE_ENUM_RESERVED,    // �����̊g���̗\��

}LP_STATE_ENUM;

class LinkedParticle
{
public:
	LinkedParticle();
	~LinkedParticle();

	void           linkCalc(Map* pMap)										; // �ڑ�����Ă��鎿�_���m�̌v�Z
	void           move( Map* pMap )										; // �ړ�����
	void           debugDraw(Camera* pCam)									; // �f�o�b�O�`��
	void           addForce(float addFx, float addFy)                       ; // �O�͂�������
	bool           isConstraint() { return mbConstraint; }                   // �R���X�g���C���g�i�S���j��Ԃ��H
	float          getPosY() { return my; }								  // �x���W�擾
	float          getPosX() { return mx; }								  // �w���W�擾
	void           link( LinkedParticle *p , float springStrength = 1.0)    ; // ���_�����N�ڑ�
	void           setMassPoint(float posx, float posy, float weight = 1.0f); // ���_������
	void           setConstraint();                  // �R���X�g���C���g�i�S���j���s�� 
	void           CutConstraint();              // �R���X�g���C���g�i�S���j�̉���
	void           reset()													; // ���_���Z�b�g

	static void    setMaxSpeed(float speed)									; // �ō����̃Z�b�g
	static void    setGravity(float gravity)								; // �d�͂̃Z�b�g
	static void    setEpsiron(float epsiron)								; // �����l�؂�̂Ă������l

private:
	float          mx                                                      ; // ���� x���W
	float          my                                                      ; // ���� y���W
	float          mPrevX                                                 ; // �P�t���[���O x���W
	float          mPrevY                                                 ; // �P�t���[���O y���W
	float          mFx                                                     ; // x�����ɂ�����͂̑��a
	float          mFy                                                     ; // y�����ɂ�����͂̑��a
	float          mWeight                                                 ; // ���̎��_�̏d��
	bool           mbActive                                                ; // ���s�Ώۂ��H
	bool           mbConstraint                                            ; // �R���X�g���C���g�i�S���j�p�[�e�B�N�����H
	bool           mbHitWall                                               ; // ���ݕǂɏՓ˂��Ă��邩�H
	LP_STATE_ENUM  mState                                                  ; // �p�[�e�B�N����� 
	std::vector<LinkedParticleConnectionInfo> mParticleArray               ; // �p�[�e�B�N���ڑ����

	static float   mMaxSpeed                                               ; // �ō����x
	static float   mGravity                                                ; // �d��
	static float   mFrictionRatio                                          ; // ���C�W��
	static float   mEpsiron                                                ; // �����l�؂�̂Ă������l

	void           mapHit(Map* pMap)										; // �}�b�v�Ƃ̂����蔻��
};


#endif
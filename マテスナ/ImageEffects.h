#pragma once

enum GraphicFx
{
	GraFxBlink,//�_��
	GraFxFadeIn,//�������s����
	GraFxFadeOut,//�s����������
	GraFxFadeInOut,//�s������������
	GraFxNone//�ʏ�`��
};

class Effect
{
public:
	void Init();
	void GraphicfxStart(GraphicFx* fx, int millTime, int millInterval, float deltaTime);

private:
	bool isFxStartFlag;//�`��G�t�F�N�g�t���O
	GraphicFx fx;//�`��G�t�F�N�g�̎��
	int fxMillTime;//�G�t�F�N�g���ԃJ�E���g
	int fxMillTimeMax;//�G�t�F�N�g���ԃJ�E���gMAX 

	int fxInterMillTime;//�G�t�F�N�g�Ԋu�J�E���g
	int fxInterMillTimeMax;//�G�t�F�N�g�Ԋu�E���gMAX
	float alpha;
	const int GraFxInfinity = -99999;
};
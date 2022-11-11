#ifndef __MATH2D_H__
#define __MATH2D_H__

#include <math.h>

class Point2D
{
public:
	Point2D() { x = 0.0f; y = 0.0f; }
	Point2D(float a, float b) 
	{
		x = a; 
		y = b;
	}
	~Point2D() {};

	// ���K��
	void normalize();

	// �����Ԃ�
	float length()
	{
		return sqrtf(x * x + y * y);
	}


	float x, y;      // �{�������o�[��private�ɂ��ׂ������A�����L���̊ȈՐ����炠����public�Ƃ���
};

Point2D operator+(const Point2D& a, const Point2D& b);

Point2D operator-(const Point2D& a, const Point2D& b);

// �X�J���[��
Point2D operator*(float f, const Point2D &point);

// �X�J���[��
Point2D operator/(const Point2D &point, float f);


// ���`��Ԏ� 1����

// ���`���(LINEAR) start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float linearInterporation(float start, float end, float percentage);
// �C�[�Y�C�� start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeIn(float start, float end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeOut(float start, float end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeInOut(float start, float end, float percentage);

// Cubic
// �C�[�Y�C�� start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeInCubic(float start, float end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeOutCubic(float start, float end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeInOutCubic(float start, float end, float percentage);

//Circular
float easeInCircular(float start, float end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeOutCircular(float start, float end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
float easeInOutCircular(float start, float end, float percentage);

float easeInExponential(float start, float end, float percentage);
float easeOutExponential(float start, float end, float percentage);
float easeInOutExponential(float start, float end, float percentage);

// ���`��Ԏ��@2����

// ���`���(LINEAR) start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D linearInterporation(const Point2D& start, const Point2D& end, float percentage);
// �C�[�Y�C�� start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeIn(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeOut(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeInOut(Point2D& start, Point2D& end, float percentage);

// Cubic
// �C�[�Y�C�� start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeInCubic(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeOutCubic(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeInOutCubic(Point2D& start, Point2D& end, float percentage);

// Cubic
// �C�[�Y�C�� start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeInCircular(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeOutCircular(Point2D& start, Point2D& end, float percentage);
// �C�[�Y�C���A�E�g start:�J�n�_ end:�I���_ percentage:(0.0�J�n-1.0�I��)��ԃp�[�Z���g
Point2D easeInOutCircular(Point2D& start, Point2D& end, float percentage);


Point2D easeInExponential(Point2D& start, Point2D& end, float percentage);
Point2D easeOutExponential(Point2D& start, Point2D& end, float percentage);
Point2D easeInOutExponential(Point2D& start, Point2D& end, float percentage);
#endif
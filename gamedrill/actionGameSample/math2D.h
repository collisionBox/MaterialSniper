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

	// 正規化
	void normalize();

	// 長さ返す
	float length()
	{
		return sqrtf(x * x + y * y);
	}


	float x, y;      // 本来メンバーはprivateにすべきだが、数式記入の簡易性からあえてpublicとした
};

Point2D operator+(const Point2D& a, const Point2D& b);

Point2D operator-(const Point2D& a, const Point2D& b);

// スカラー積
Point2D operator*(float f, const Point2D &point);

// スカラー商
Point2D operator/(const Point2D &point, float f);


// 線形補間式 1次元

// 線形補間(LINEAR) start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float linearInterporation(float start, float end, float percentage);
// イーズイン start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeIn(float start, float end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeOut(float start, float end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeInOut(float start, float end, float percentage);

// Cubic
// イーズイン start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeInCubic(float start, float end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeOutCubic(float start, float end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeInOutCubic(float start, float end, float percentage);

//Circular
float easeInCircular(float start, float end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeOutCircular(float start, float end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
float easeInOutCircular(float start, float end, float percentage);

float easeInExponential(float start, float end, float percentage);
float easeOutExponential(float start, float end, float percentage);
float easeInOutExponential(float start, float end, float percentage);

// 線形補間式　2次元

// 線形補間(LINEAR) start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D linearInterporation(const Point2D& start, const Point2D& end, float percentage);
// イーズイン start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeIn(Point2D& start, Point2D& end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeOut(Point2D& start, Point2D& end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeInOut(Point2D& start, Point2D& end, float percentage);

// Cubic
// イーズイン start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeInCubic(Point2D& start, Point2D& end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeOutCubic(Point2D& start, Point2D& end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeInOutCubic(Point2D& start, Point2D& end, float percentage);

// Cubic
// イーズイン start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeInCircular(Point2D& start, Point2D& end, float percentage);
// イーズアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeOutCircular(Point2D& start, Point2D& end, float percentage);
// イーズインアウト start:開始点 end:終了点 percentage:(0.0開始-1.0終了)補間パーセント
Point2D easeInOutCircular(Point2D& start, Point2D& end, float percentage);


Point2D easeInExponential(Point2D& start, Point2D& end, float percentage);
Point2D easeOutExponential(Point2D& start, Point2D& end, float percentage);
Point2D easeInOutExponential(Point2D& start, Point2D& end, float percentage);
#endif
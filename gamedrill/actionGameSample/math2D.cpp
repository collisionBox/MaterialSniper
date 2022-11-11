#include "math2D.h"


// +演算子
Point2D operator+(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

//-演算子
Point2D operator-(const Point2D& a, const Point2D& b)
{
	Point2D ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// スカラー積
Point2D operator*(float f, const Point2D &point)
{
	Point2D r;
	r.x = f * point.x;
	r.y = f * point.y;
	return r;
}

//スカラー商
Point2D operator/(const Point2D &point, float f)
{
	Point2D r;
	r.x = point.x / f;
	r.y = point.y / f;
	return r;
}

// 正規化
void Point2D::normalize()
{
	float len;
	len = length();

	x /= len; y /= len;
}

// 線形補間 startからendまでを percentageに応じて線形補間
float linearInterporation(float start, float end, float percentage)
{
	float diff; //開始から終了の差分
	diff = end - start;

	return diff * percentage + start;
}


float easeIn(float start, float end, float percentage)
{
	float diff; //開始から終了の差分
	diff = end - start;

	return diff * percentage * percentage + start;
}

float easeOut(float start, float end, float percentage)
{
	float diff; //開始から終了の差分
	diff = end - start;

	return -diff * percentage * ( percentage - 2.0f ) + start;
}

float easeInOut(float start, float end, float percentage)
{
	float t,diff;
	diff = end - start;

	//パーセンテージを2倍に引き伸ばし、easeIn/Out計算を分ける
	t = percentage * 2.0f;

	//easeIn部分
	if (t < 1.0f)
	{
		return  diff / 2.0f * t * t + start;
	}
	// easeOut部分
	t = t - 1.0f;
	return -diff / 2.0f * ( t * (t - 2.0f) - 1.0f) + start;
}


float easeInCubic(float start, float end, float percentage)
{
	float diff; //開始から終了の差分
	diff = end - start;

	return diff * percentage * percentage * percentage + start;
}

float easeOutCubic(float start, float end, float percentage)
{
	float diff; //開始から終了の差分
	diff = end - start;

	percentage = percentage - 1.0f;

	return diff * ( percentage * percentage * percentage + 1.0f) + start;
}

float easeInOutCubic(float start, float end, float percentage)
{
	float t, diff;
	diff = end - start;

	t = percentage * 2.0f;

	//easeIn部分
	if (t < 1.0f)
	{
		return  diff / 2.0f * t * t * t + start;
	}
	// easeOut部分
	t = t - 2.0f;
	return diff / 2.0f * (t * t * t + 2.0f) + start;
}


float easeInCircular(float start, float end, float percentage)
{
	float diff = end - start;

	return -diff * (sqrtf(1.0f - percentage * percentage) - 1.0f) + start;
}

float easeOutCircular(float start, float end, float percentage)
{
	float diff = end - start;
	percentage -= 1.0f;

	return diff * sqrtf(1.0f - percentage * percentage) + start;
}

float easeInOutCircular(float start, float end, float percentage)
{
	float t, diff;
	diff = end - start;

	t = percentage * 2.0f;

	//easeIn部分
	if (t < 1.0f)
	{
		return  -diff / 2.0f * (sqrtf( 1.0f - t * t) -1.0f) + start;
	}
	// easeOut部分
	t = t - 2.0f;

	return diff / 2.0f * ( sqrtf(1.0f - t * t) + 1.0f ) + start;
}

float easeInExponential(float start, float end, float percentage)
{
	float diff = end - start;

	return diff *(powf(2.0f, 10.0f * (percentage - 1.0f))) + start;
}

float easeOutExponential(float start, float end, float percentage)
{
	float diff = end - start;

	return diff * ( 1.0f - (powf(2.0f, -10.0f * percentage))) + start;
}

float easeInOutExponential(float start, float end, float percentage)
{
	float t, diff;
	diff = end - start;

	t = percentage * 2.0f;
	//easeIn部分
	if (t < 1.0f)
	{
		return  diff / 2.0f * powf( 2.0f, 10.0f * (t - 1.0f)) + start;
	}
	// easeOut部分
	t = t - 1.0f;

	return diff / 2.0f * ( 2.0f - (powf(2.0f, -10.0f * t)) ) + start;
}

Point2D linearInterporation(const Point2D& start,const Point2D& end ,float percentage)
{
	Point2D diff;

	diff = end - start;
	return percentage * diff + start;
}

Point2D easeIn( Point2D& start, Point2D& end, float percentage)
{
	Point2D diff;

	diff = end - start;
	return percentage * percentage * diff + start;
}

Point2D easeOut(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeOut(start.x, end.x, percentage);
	ret.y = easeOut(start.y, end.y, percentage);

	return ret;
}

Point2D easeInOut(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;

	ret.x = easeInOut(start.x, end.x, percentage);
	ret.y = easeInOut(start.y, end.y, percentage);

	return ret;
}


Point2D easeInCubic(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;

	ret.x = easeInCubic(start.x, end.x, percentage);
	ret.y = easeInCubic(start.y, end.y, percentage);

	return ret;
}

Point2D easeOutCubic(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeOutCubic(start.x, end.x, percentage);
	ret.y = easeOutCubic(start.y, end.y, percentage);
	return ret;
}

Point2D easeInOutCubic(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeInOutCubic(start.x, end.x, percentage);
	ret.y = easeInOutCubic(start.y, end.y, percentage);
	return ret;
}


Point2D easeInCircular(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;

	ret.x = easeInCircular(start.x, end.x, percentage);
	ret.y = easeInCircular(start.y, end.y, percentage);

	return ret;
}

Point2D easeOutCircular(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeOutCircular(start.x, end.x, percentage);
	ret.y = easeOutCircular(start.y, end.y, percentage);
	return ret;
}

Point2D easeInOutCircular(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeInOutCircular(start.x, end.x, percentage);
	ret.y = easeInOutCircular(start.y, end.y, percentage);
	return ret;
}


Point2D easeInExponential(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeInExponential(start.x, end.x,percentage);
	ret.y = easeInExponential(start.y, end.y,percentage);

	return ret;
}

Point2D easeOutExponential(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;
	ret.x = easeOutExponential(start.x, end.x, percentage);
	ret.y = easeOutExponential(start.y, end.y, percentage);
	return ret;
}

Point2D easeInOutExponential(Point2D& start, Point2D& end, float percentage)
{
	Point2D ret;

	ret.x = easeInOutExponential(start.x, end.x, percentage);
	ret.y = easeInOutExponential(start.y, end.y, percentage);
	return ret;
}
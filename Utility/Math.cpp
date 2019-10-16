/*
#include"stdafx.h"
#include"Math.h"
const float Math::PI=3.14159265f;
float Math::ToRadian(float degree)
{
	return degree*PI/180.0f;
}

float Math::ToDegree(float radian)
{
	return radian*180.0f/PI;
}

int Math::Random(int r1, int r2)
{
	return (int)(rand()%(r2-r1+1)+r1);
}

float Math::Random(float r1, float r2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = r2 - r1;
	float val = random * diff;
	return r1+val;
}

bool Math::SementIntersects(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	double ab = Ccw(a, b, c)*Ccw(a, b, c);
	float cd = Ccw(c, d, a)*Ccw(c, d, b);

	if (ab == 0 && cd == 0) {
		if (b < a)swap(a, b);
		if (d < c)swap(c, d);
		return !(b < c || b < a);
	}
	return ab<=0&&cd<=0;
}

float Math::Cross(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2)
{

	return vec1.x*vec2.y-vec2.x*vec1.y;
}

float Math::Ccw(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2)
{
	return Cross(vec1, vec2);
}

float Math::Ccw(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2, D3DXVECTOR2 vec3)
{
	return Ccw(vec2 - vec1, vec3 - vec1);
}
*/
#include "stdafx.h"
#include "Math.h"

const float Math::PI = 3.14159265f;

float Math::ToRadian(float degree)
{
	return degree * PI / 180.0f;
}

float Math::ToDegree(float radian)
{
	return radian * 180.0f / PI;
}

int Math::Random(int r1, int r2)
{
	return (int)(rand() % (r2 - r1 + 1)) + r1;
}

float Math::Random(float r1, float r2)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = r2 - r1;
	float val = random * diff;

	return r1 + val;
}

bool Math::SementIntersects(D3DXVECTOR2 a, D3DXVECTOR2 b, D3DXVECTOR2 c, D3DXVECTOR2 d)
{
	float ab = Ccw(a, b, c) * Ccw(a, b, d);
	float cd = Ccw(c, d, a) * Ccw(c, d, b);

	if (ab == 0 && cd == 0)
	{
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}

	return ab <= 0 && cd <= 0;
}

float Math::Cross(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2)
{
	return vec1.x * vec2.y - vec2.x * vec1.y;
}

float Math::Ccw(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2)
{
	return Cross(vec1, vec2);
}

float Math::Ccw(D3DXVECTOR2 vec1, D3DXVECTOR2 vec2, D3DXVECTOR2 vec3)
{
	return Ccw(vec2 - vec1, vec3 - vec1);
}

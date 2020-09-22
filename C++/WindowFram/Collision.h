#pragma once

#include "Global.h"

// 마우스와 도형의 충돌에 관한 클래스
// 싱글톤 적용

class Collision {
private:
	static Collision* pthis;
	Collision() {}
	~Collision() {}
public:
	static Collision* GetInstance();
	static void Destory();

	// 거리 공식
	double Lengthpts(int x1, int y1, int x2, int y2);

	// 원과 원이 부딪힐 시
	bool CollisionEnterinCircle(int x, int y, int mx, int my, int size);
	// 사각형과 점(마우스)가 부딪힐 시
	bool CollisionEnterinPoint(int x, int y, int mx, int my, int x_size, int y_size);
};
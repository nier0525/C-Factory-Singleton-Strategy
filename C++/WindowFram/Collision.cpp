#include "Collision.h"

Collision* Collision::pthis = nullptr;

Collision* Collision::GetInstance() {
	if (!pthis) {
		pthis = new Collision();
	}
	return pthis;
}

void Collision::Destory() {
	if (pthis) {
		delete pthis;
	}
}

// 충돌체와 충돌체의 거리를 계산하는 함수
double Collision::Lengthpts(int x1, int y1, int x2, int y2) {
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

// 원과 원이 충돌할 때의 공식을 구한 함수
bool Collision::CollisionEnterinCircle(int x, int y, int mx, int my, int size) {
	if (Collision::GetInstance()->Lengthpts(x, y, mx, my) < size) { return true; }
	else { return false; }
}

// 사각형과 점(마우스) 가 충돌할 때의 공식을 구한 함수
bool Collision::CollisionEnterinPoint(int x, int y, int mx, int my, int x_size, int y_size) {
	if ((x + x_size >= mx && mx >= x - x_size) && (y + y_size >= my && my >= y - y_size)) { return true; }
	else { return false; }
}
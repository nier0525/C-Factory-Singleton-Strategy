#pragma once

#include "Mouse.h"
#include "Collision.h"
#include "BackBit.h"
#include "KeyBoard.h"

#include "LoginManager.h"
#include "CharacterManager.h"

// 게임 매니저 클래스
// 모든 메뉴들의 부모 클래스이고, 메뉴를 그리는 함수의 정의는 다운 캐스팅을 통해 자식에게 맡긴다.

class GameManager {
protected:
	CMouse* mouse;	// 마우스 객체 변수
	Collision* col;	// 충돌 판정 객체 변수
public:
	GameManager() {
		mouse = CMouse::GetInstance();
		col = Collision::GetInstance();
	}
	~GameManager() {}

	virtual void DrawMenu(CBackBit* _bit) = 0;
};
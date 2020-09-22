#pragma once

#include "WindowFrame.h"

#include "LoginMenu.h"
#include "CharacterMenu.h"
#include "GameMenu.h"

// 전략 패턴 클래스
// 상황에 맞게 메뉴 클래스를 바꿔준다.
// 싱글톤 적용

class MainManager {
private:
	static MainManager* pthis;
	MainManager() {}
	~MainManager() {}

	// 게임 메뉴의 부모 객체
	GameManager* gamemenu;
public:
	// 매크로 메서드
	static MainManager* GetInstance();
	static void Destory();

	// 다운 캐스팅을 이용한 전략 패턴 구현
	void SetDrawMenu(GameManager* temp) {
		gamemenu = temp;
	}

	// 현재 적용된 클래스의 DrawMenu 를 그려준다.
	void DrawMenu(CBackBit* _bit) {
		gamemenu->DrawMenu(_bit);
	}
};
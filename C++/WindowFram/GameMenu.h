#pragma once

#include "GameManager.h"
#include "ItemStore.h"

// 게임 메뉴 클래스
// 캐릭터까지 선택한다면 실질적으로 게임이 진행(상점,인벤토리,장비 장착) 등을 담당하는 클래스이다.
// 싱글톤 매크로

class GameMenu : public GameManager {
	DECLARE_SINGLETONE(GameMenu)
private:
	// 생성자에서 변수들을 초기화해준다.
	GameMenu() {
		memset(name, 0, sizeof(name));
		inven = false;
		store = false;
		stats = false;
		
		buy = false;
		sell = false;
		on = false;
	}
	~GameMenu() {}

	char name[CHAR];	// 아이템 이름

	// 각 상황에 맞는 부울형 변수
	bool inven;
	bool store;
	bool stats;

	bool buy;
	bool sell;
	bool on;
public:

	// 게임 메뉴
	void DrawMenu(CBackBit* _bit);

	// 인벤토리 메뉴
	void ShowInven(HDC);
	// 상점 메뉴
	void ShowStore(HDC);
	// 스탯 메뉴
	void ShowStats(HDC);
	// 아이템 이름 입력 메뉴
	void SelectItem(HDC);
	
	// 쓰기 접근자
	void SetName(const char* name) { strcpy(this->name, name); }

	// 읽기 접근자
	const char* GetName() { return name; }

	bool Getbuystate() { return buy; }
	bool Getsellstate() { return sell; }
	bool Getonstate() { return on; }
};
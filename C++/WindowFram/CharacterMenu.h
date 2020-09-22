#pragma once

#include "GameManager.h"

// 캐릭터 메뉴 클래스
// 싱글톤 적용

class CharacterMenu : public GameManager {
private:
	static CharacterMenu* pthis;
	// 각각 변수들 초기화
	CharacterMenu() {
		memset(name, 0, sizeof(name));
		New = false;
		Sel_Oak = false;
		Sel_Elf = false;
		Select = false;
		Remove = false;
	}
	~CharacterMenu() {}

	char name[CHAR];	// 캐릭터 이름 입력

	// 각 상황에 따른 부울형 변수
	bool New;
	bool Sel_Oak;
	bool Sel_Elf;
	bool Select;
	bool Remove;
public:
	static CharacterMenu* GetInstance();
	static void Destory();

	// 쓰기 접근자
	void SetName(const char* _name) { strcpy(name, _name); }

	// 메뉴 호출
	void DrawMenu(CBackBit* _bit);
	// 캐릭터 세부 메뉴 호출
	void CharacterSeMenu(HDC hdc, CBackBit* _bit);


	// 읽기 접근자
	const char* GetName() { return name; }

	bool GetNewState() { return New; }
	bool GetSelect_Oak() { return Sel_Oak; }
	bool GetSelect_Elf() { return Sel_Elf; }
	bool GetSelect() { return Select; }
	bool GetRemove() { return Remove; }
};
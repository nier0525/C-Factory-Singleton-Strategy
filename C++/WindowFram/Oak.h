#pragma once

#include "Character.h"

// 오크 클래스 상속 객체
class Oak : public Character {
private:

public:
	Oak() : Character() {}
	// 종족에 따른 능력치 조정
	Oak(const char* _name, KindFactory* _kind) : Character(_name, _kind) {
		Character::SetHp(Character::GetHp() + 100);
		Character::SetMp(Character::GetMp() - 50);
		Character::SetDef(Character::GetDef() + 10);
	}
	~Oak() {

	}
};
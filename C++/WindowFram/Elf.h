#pragma once

#include "Character.h"

// 엘프 클래스 상속 객체
class Elf : public Character {
private:

public:
	Elf() : Character() {}
	// 종족에 따른 능력치 조정
	Elf(const char* _name, KindFactory* _kind) : Character(_name, _kind) {
		Character::SetHp(Character::GetHp() - 100);
		Character::SetMp(Character::GetMp() + 50);
		Character::SetAtt(Character::GetAtt() + 10);
	}
	~Elf() {

	}
};
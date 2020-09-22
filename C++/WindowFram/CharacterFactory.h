#pragma once

#include "Elf.h"
#include "Oak.h"
#include "KindFactory.h"

// 팩토리 패턴 사용

class CharacterFactory {
protected:
	// 순수 가상 함수이기 때문에 자식 객체에서 정의해준다.
	virtual Character* CreateCharacter(const char* , KindFactory*) = 0;
	virtual KindFactory* SelectKind() = 0;
public:
	CharacterFactory() {}
	virtual ~CharacterFactory() {}

	Character* MakeCharacter(const char* _name); // 캐릭터 생성 담당 메소드
};
#pragma once

#include "CharacterFactory.h"
#include "ElfItemFactory.h"

// 엘프 팩토리 패턴 클래스
// 싱글톤 매크로

class ElfFactory : public CharacterFactory {
	DECLARE_SINGLETONE(ElfFactory)
private:
	ElfFactory() {}
	~ElfFactory() {}

	// 부모 객체의 함수를 정의해줌
	virtual Character* CreateCharacter(const char*, KindFactory*);
	virtual KindFactory* SelectKind();
public:

};
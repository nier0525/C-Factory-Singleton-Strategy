#pragma once

#include "CharacterFactory.h"
#include "OakItemFactory.h"

// 오크 팩토리 패턴 클래스
// 싱글톤 매크로

class OakFactory : public CharacterFactory {
	DECLARE_SINGLETONE(OakFactory)
private:
	OakFactory() {}
	virtual ~OakFactory() {}

	// 부모 객체의 함수를 정의해줌
	virtual Character* CreateCharacter(const char*, KindFactory*);
	virtual KindFactory* SelectKind();
public:

};


#include "CharacterManager.h"

// 캐릭터 생성 담당 메소드
Character* CharacterFactory::MakeCharacter(const char* _name) {
	KindFactory* kind = SelectKind();	// 가상 함수를 통해 자식 객체에서 선택된 종족 팩토리 클래스로 대입
	Character* ptr = CreateCharacter(_name, kind);	// 캐릭터 생성

	return ptr;	// 생성된 캐릭터 반환
}
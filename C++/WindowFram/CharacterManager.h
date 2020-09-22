#pragma once

#include "LoginManager.h"
#include "OakFactory.h"
#include "ElfFactory.h"

// 캐릭터를 관리할 매니저 클래스
// 싱글톤 매크로

// 캐릭터 생성, 삭제, 선택 등등 전반적인 캐릭터에 관련된 일을 담당하는 클래스

class CharacterManager {
	DECLARE_SINGLETONE(CharacterManager)
private:
	CharacterManager() {}
	~CharacterManager() {}

	// 현재 접속중인 캐릭터를 위한 변수
	Character* NowCharacter;
public:

	void Init();	// 초기화 함수
	bool CreateCharacter(const char*, CharacterFactory*);	// 생성
	bool SelectCharacter(const char*);						// 선택
	bool DropCharacter(const char*);						// 삭제

	void PrintCharacter(HDC, int, int);						// 캐릭터 능력치 출력
	void ShowNowCharacterInven(HDC, int, int);				// 현재 접속중인 캐릭터의 인벤토리 내에 아이템 출력

	Character* GetNowCharacter() { return NowCharacter; }	// 현재 접속중인 캐릭터 읽기 접근자
};
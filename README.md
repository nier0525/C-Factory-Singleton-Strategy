# Factory-Singleton-Strategy
-----------------------------------------------------   
   
C++ 패턴 기법 중 Factory, Singleton, Strategy 패턴을 활용하여 만든 캐릭터 인벤토리 기능 입니다.   
WINAPI 를 이용하여 제작하였고 파일 입출력을 통해 저장, 불러오기를 구현하였습니다.   
   
   
## Factory 패턴
-----------------------------------------------------   
   
Factory 패턴을 활용하여 만든 기능은 종족 선택 기능 입니다.   
단어 그래도 공장처럼 찍어내는 Factory 패턴 특성을 활용하기에 제일 적합하다고 생각하여 적용하였습니다.   
소스 코드는 엘프, 오크, 인간 중 엘프만 기재하였고 풀 코드는 파일로 업로드 해두었습니다.   
   
### 소스 코드   
   
#### Kind Factory
   
```   
#pragma once

#include "Wenpon.h"
#include "Armor.h"
#include "Accessories.h"

// 종족 팩토리 클래스
// 각각 종족마다 다른 무기를 지급하기 위한 클래스임.
// 순수가상클래스

class KindFactory {
private:

public:
	KindFactory() {}
	virtual ~KindFactory() {}

	virtual Wenpon* CreateWenpon() = 0;
	virtual Armor* CreateArmor() = 0;
	virtual Accessories* CreteAccessories() = 0;
};
```   
   
#### Character Factory    
   
```   
Character Factory.h

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

-----------------------------------------------------------------

Character Factory.cpp

#include "CharacterManager.h"

// 캐릭터 생성 담당 메소드
Character* CharacterFactory::MakeCharacter(const char* _name) {
	KindFactory* kind = SelectKind();	// 가상 함수를 통해 자식 객체에서 선택된 종족 팩토리 클래스로 대입
	Character* ptr = CreateCharacter(_name, kind);	// 캐릭터 생성

	return ptr;	// 생성된 캐릭터 반환
}
```   
   
#### Elf   
   
```   
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
```   
   
### Elf Item Factory   
   
```   
Elf Item Factory.h

#pragma once

#include "KindFactory.h"

// 엘프 아이템 팩토리 클래스
// 싱글톤 매크로

class ElfItemFactory : public KindFactory {
	DECLARE_SINGLETONE(ElfItemFactory)
private:
	ElfItemFactory() {}
	virtual ~ElfItemFactory() {}
public:
	// 시작 장비 생성
	virtual Wenpon* CreateWenpon() {
		return new Wenpon("Bronze Sword", 2000, 50);
	}

	virtual Armor* CreateArmor() {
		return new Armor("Bronze Shield", 1500, 20);
	}

	virtual Accessories* CreteAccessories() {
		return new Accessories("Magic Chain", 3000, 0, 300);
	}
};

```   
   
#### Elf Factory   
   
```   
ElfFactory.h

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

-----------------------------------------------------------------

ElfFactory.cpp

#include "ElfFactory.h"
#include "ElfItemFactory.h"

ElfFactory* ElfFactory::mPthis = nullptr;

ElfFactory* ElfFactory::GetInstance() {
	if (!mPthis) {
		mPthis = new ElfFactory();
	}

	ElfItemFactory::GetInstance();

	return mPthis;
}

void ElfFactory::Destroy() {
	ElfItemFactory::Destroy();
	
	if (mPthis) {
		delete mPthis;
	}
}

// 엘프 클래스를 업캐스팅 해주고 반환한다.
Character* ElfFactory::CreateCharacter(const char* _name, KindFactory* _kind) {
	Character* ptr = new Elf(_name, _kind);
	return ptr;
}


KindFactory* ElfFactory::SelectKind() {
	KindFactory* ptr = ElfItemFactory::GetInstance(); // 팩토리 패턴 업캐스팅 후 반환
	return ptr;
}
```   
      
## Singleton 패턴
-----------------------------------------------------   
   
객체가 여러개가 생성되는 것을 방지하기 위한 패턴입니다.   
보통 Manager 클래스에 적용시키며, 하나 이상의 객체가 필요 없는 클래스에 적용시키는 패턴이기도 합니다.   
단, 여러모로 편리한 패턴이기 때문에 너무 남용하게 되면 자원 관리 같은 여러 부분에서 문제가 발생 할 수 있습니다.   
보편적으로 많이 쓰는 매크로 방식으로 구현하였고, Manager 클래스이면서 자주 쓰는 클래스에 적용하였습니다.   
   
#### Singleton 매크로
   
```   
#define MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
               CLASSNAME(const CLASSNAME&){}                                \
               CLASSNAME& operator=(const CLASSNAME&);

// 싱클톤 패턴 생성 매크로
#define DECLARE_SINGLETONE(CLASSNAME)                                       \
        MAKE_NO_COPY(CLASSNAME)                                             \
        private:                                                            \
			   static CLASSNAME* mPthis;									\
        public:                                                             \
			   static CLASSNAME* GetInstance();								\
               static void Destroy();										 

// 싱글톤 패턴 구현 매크로

#define IMPLEMENT_SINGLETON(CLASSNAME)                              \
               CLASSNAME* CLASSNAME::mPthis = nullptr;				\
                                                                    \
               CLASSNAME* CLASSNAME::GetInstance()					\
               {                                                    \
                       if(mPthis == nullptr)						\
						{											\
                              mPthis=new CLASSNAME();				\
						}											\
                        return mPthis;								\
               }													\
																	\
			   void CLASSNAME::Destroy()							\
               {													\
					if(mPthis) delete mPthis;						\
				}																												

#endif
```   
   
## Strategy 패턴
-----------------------------------------------------   
   
전략 패턴이라고도 불리는 이 패턴은 다양한 기능 중 내가 사용하고자 하는 기능만 사용 할 때 그 클래스로 바꿔주는 기능입니다.   
대표적으로 사용되는 곳은 스킬 시스템, 메뉴 시스템과 같이 다양한 기능 중 자신이 선택한 기능만 사용하는 시스템에 주로 적용됩니다.      
   
#### MainManager   
   
```   
MainManager.h

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

-----------------------------------------------------------------

MainManager.cpp

#include "MainManager.h"

MainManager* MainManager::pthis = nullptr;

MainManager* MainManager::GetInstance() {
	if (!pthis) {
		pthis = new MainManager();
	}

	LoginMenu::GetInstance();
	CharacterMenu::GetInstance();
	GameMenu::GetInstance();

	return pthis;
}

void MainManager::Destory() {
	LoginMenu::Destory();
	CharacterMenu::Destory();
	GameMenu::Destroy();

	if (pthis) {
		delete pthis;
	}
}
```   
   
   
   
   
   

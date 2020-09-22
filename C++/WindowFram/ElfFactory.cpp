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
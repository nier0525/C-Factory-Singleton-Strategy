#include "OakFactory.h"

OakFactory* OakFactory::mPthis = nullptr;

OakFactory* OakFactory::GetInstance() {
	if (!mPthis) {
		mPthis = new OakFactory();
	}

	OakItemFactory::GetInstance();

	return mPthis;
}

void OakFactory::Destroy() {
	OakItemFactory::Destroy();
	if (mPthis) {
		delete mPthis;
	}
}

// 오크 클래스를 업캐스팅 해주고 반환한다.
Character* OakFactory::CreateCharacter(const char* _name, KindFactory* _kind) {
	Character* ptr = new Oak(_name, _kind);
	return ptr;
}

KindFactory* OakFactory::SelectKind() {
	KindFactory* kind = OakItemFactory::GetInstance();	// 팩토리 패턴 업캐스팅 후 반환
	return kind;
}
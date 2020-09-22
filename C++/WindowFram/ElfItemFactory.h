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
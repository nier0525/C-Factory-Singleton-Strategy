#pragma once

#include "KindFactory.h"

// 오크 아이템 팩토리 클래스
// 싱글톤 매크로

class OakItemFactory : public KindFactory {
	DECLARE_SINGLETONE(OakItemFactory)
private:
	OakItemFactory() {}
	virtual ~OakItemFactory() {}
public:
	// 시작 장비 생성
	virtual Wenpon* CreateWenpon() {
		return new Wenpon("Steel Axe", 2000, 50);
	}

	virtual Armor* CreateArmor() {
		return new Armor("Steel Shield", 1500, 20);
	}

	virtual Accessories* CreteAccessories() {
		return new Accessories("Health Chain", 3000, 300, 0);
	}
};
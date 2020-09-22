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
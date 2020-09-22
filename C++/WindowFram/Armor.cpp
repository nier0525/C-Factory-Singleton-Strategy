#include "Armor.h"
#include "Character.h"

int Armor::Num = NODATA;

// 변수 초기화
Armor::Armor(const char* _name, int _price, int _Def) : Item(_name, _price) {
	Def = _Def;
}

Armor::~Armor() {

}

// 읽기 접근자

int Armor::GetFirstAbility() {
	return Def;
}

int Armor::GetSecordAbility() {
	return 0;
};

// 장비 착용시

bool Armor::OnItem(Character* index) {
	index->SetDef(index->GetDef() + Def);
	// 해당 아이템의 성능만큼 캐릭터의 스탯 향상
	return true;
}

// 장비 해제시

bool Armor::OffItem(Character* index) {
	index->SetDef(index->GetDef() - Def);
	// 해제한 장비의 성능만큼 캐릭터 스탯 감소
	return true;
}

// 아이템 생성마다 새로운 코드 생성

void Armor::MakeCode() {
	Armor::Num++;
	sprintf(Item::code, "%03d_%03d", ARMOR_CODE, Armor::Num);
}
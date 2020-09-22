#include "Accessories.h"
#include "Character.h"

int Accessories::Num = NODATA;

// 변수 초기화
Accessories::Accessories(const char* _name, int _price, int _HP, int _MP) : Item(_name, _price) {
	HP = _HP;
	MP = _MP;
}

Accessories::~Accessories() {

}

// 읽기 접근자

int Accessories::GetFirstAbility() {
	return HP;
}

int Accessories::GetSecordAbility() {
	return MP;
}

// 장비 착용시

bool Accessories::OnItem(Character* index) {
	index->SetHp(index->GetHp() + HP);
	index->SetMp(index->GetMp() + MP);
	// 해당 아이템의 성능만큼 캐릭터의 스탯 향상
	return true;
}

// 장비 해제시

bool Accessories::OffItem(Character* index) {
	index->SetHp(index->GetHp() - HP);
	index->SetMp(index->GetMp() - MP);
	// 해제한 장비의 성능만큼 캐릭터 스탯 감소
	return true;
}

// 아이템 생성마다 새로운 코드 생성

void Accessories::MakeCode() {
	Accessories::Num++;
	sprintf(Item::code, "%03d_%03d", ACCESSORIES_CODE, Accessories::Num);
}
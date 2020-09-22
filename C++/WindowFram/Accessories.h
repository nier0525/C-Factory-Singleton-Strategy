#pragma once

#include "Item.h"
#define ACCESSORIES_CODE 203	// 아이템 코드

class Character;

class Accessories : public Item {
private:
	// 능력치 및 일련 코드
	int HP;	
	int MP;
	static int Num;
public:
	Accessories(const char*, int, int, int); // 이름, 가격, 능력치, 능력치2
	~Accessories();

	// 읽기 접근자
	virtual int GetFirstAbility();
	virtual int GetSecordAbility();

	// 코드 생성
	virtual void MakeCode();
	// 아이템 착용,해제 시 캐릭터 스탯 변경 담당
	virtual bool OnItem(Character*);
	virtual bool OffItem(Character*);
};
#pragma once

#include "Global.h"

// 아이템 클래스

class Character;

class Item {
protected:
	char name[CHAR];	// 아이템 이름
	char code[CHAR];	// 아이템 코드
	int price;			// 아이템 가격
public:
	Item(const char*, int);	// 매게 변수는 이름과 가격
	virtual ~Item();

	// 읽기 접근자
	const char* GetItemName();
	const char* GetItemCode();
	int GetPrice();

	// 순수 가상 함수
	virtual void MakeCode() = 0;
	virtual bool OnItem(Character*) = 0;
	virtual bool OffItem(Character*) = 0;

	virtual int GetFirstAbility() = 0;
	virtual int GetSecordAbility() = 0;
};
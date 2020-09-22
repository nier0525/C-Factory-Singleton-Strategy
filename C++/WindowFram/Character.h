#pragma once

#include "ListNode.h"

#include "Wenpon.h"
#include "Armor.h"
#include "Accessories.h"

#include "KindFactory.h"

class Character {
private:
	char Name[CHAR];	// 캐릭터 이름

	int Level;			// 캐릭터 레벨
	int Hp;				// 캐릭터 체력
	int Mp;				// 캐릭터 마나
	int Att;			// 캐릭터 공격력
	int Def;			// 캐릭터 방어력

	int money;			// 캐릭터가 소지하고 있는 돈
	int m_count;			// 인벤토리 내에 아이템 개수

	Wenpon* m_wenpon;	// 현재 착용중인 무기
	Armor* m_armor;		// 현재 착용중인 방어구
	Accessories* m_accessories;	// 현재 착용중인 악세사리

	ListNode<Item*>* Inven;	// 캐릭터 인벤토리
	Node<Item*>* SearchItem;	// 인벤토리 서치 노드

	KindFactory* kind;
	// 처음 생성시 종족별로 다른 무기를 지급하기 위한 팩토리 패턴 클래스
public:
	Character();
	Character(const char*, KindFactory*);	// 매게 변수는 이름과 종족 팩토리 패턴
	virtual ~Character();					

	// 읽기 접근자
	const char* GetNickName();

	int GetLevel();
	int GetHp();
	int GetMp();
	int GetAtt();
	int GetDef();

	int GetMoney();
	int GetItemCount() {
		return m_count;
	}

	void SetMyWenpon(const char* name, int price, int att) {
		m_wenpon = new Wenpon(name, price, att);
	}

	void SetMyArmor(const char* name, int price, int def) {
		m_armor = new Armor(name, price, def);
	}

	void SetMyAccessories(const char* name, int price, int hp, int mp) {
		m_accessories = new Accessories(name, price, hp, mp);
	}

	Wenpon* GetMyWenpon() { return m_wenpon; }
	Armor* GetMyArmor() { return m_armor; }
	Accessories* GetMyAccessories() { return m_accessories; }

	// 쓰기 접근자
	void SetNickName(const char*);

	void LevelUp();
	void SetLevel(int);
	void SetHp(int);
	void SetMp(int);
	void SetAtt(int);
	void SetDef(int);
	void SetMoney(int);

	void SetItemCount(int _count) {
		m_count = _count;
	}

	// 아이템 구입,판매
	bool Sell(Item*);
	bool Buy(Item*);

	// 현재 가진 잔액 계산
	bool InCreseGameMoney(int);
	bool DeCreseGameMoney(int);

	// 착용 장비 교체
	bool ChangeItem(Item*);

	// 외부로 자료구조를 노출하지 않기 위해 자체적으로 리스트를 순회하는 함수
	void SearchEnd();
	bool GetItem(Item**);

	bool LoadInvenItem(Item* item) {
		if (item != nullptr) {
			Inven->Insert(item);
			return true;
		}
		return false;
	}
};
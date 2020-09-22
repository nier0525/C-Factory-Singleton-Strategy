#include "Character.h"

Character::Character() {
	memset(Name, 0, sizeof(Name));
	
	Level = NODATA;
	Hp = NODATA;
	Mp = NODATA;
	Att = NODATA;
	Def = NODATA;

	m_wenpon = nullptr;
	m_armor = nullptr;
	m_accessories = nullptr;

	money = NODATA;
	m_count = NODATA;

	Inven = new ListNode<Item*>();
	SearchItem = nullptr;
}

Character::Character(const char* _name, KindFactory* _kind) {
	// 초기화
	strcpy(Name, _name);

	Level = 1;
	Hp = 500;
	Mp = 200;
	Att = 20;
	Def = 10;

	// 팩토리 패턴에서 받은 인자값
	kind = _kind;

	// 팩토리 패턴 클래스에서 정해진 종족에 따른 무기 배분 후 착용
	m_wenpon = kind->CreateWenpon();
	m_wenpon->OnItem(this);
	m_armor = kind->CreateArmor();
	m_armor->OnItem(this);
	m_accessories = kind->CreteAccessories();
	m_accessories->OnItem(this);

	// 돈 초기화
	money = GAMEMONEY;
	m_count = NODATA;

	// 인벤토리 초기화 및 리스트 동적 할당
	Inven = new ListNode<Item*>();
	SearchItem = nullptr;
}

// 동적 할당 된 객체들 메모리 해제
Character::~Character() {
	if (m_wenpon != nullptr) {
		delete m_wenpon;
	}

	if (m_armor != nullptr) {
		delete m_armor;
	}

	if (m_accessories != nullptr) {
		delete m_accessories;
	}

	if (Inven != nullptr) {
		delete Inven;
	}
}

//------------------------------------------------------ 쓰기 접근자

void Character::SetNickName(const char* _name) {
	strcpy(Name, _name);
}

void Character::SetLevel(int _level) {
	Level = _level;
}

void Character::SetHp(int _hp) {
	Hp = _hp;
}

void Character::SetMp(int _mp) {
	Mp = _mp;
}

void Character::SetAtt(int _att) {
	Att = _att;
}

void Character::SetDef(int _def) {
	Def = _def;
}

void Character::LevelUp() {
	Level++;
}

void Character::SetMoney(int _money) {
	money = _money;
}

//---------------------------------------------------- 읽기 접근자

const char* Character::GetNickName() {
	return Name;
}

int Character::GetLevel() {
	return Level;
}

int Character::GetHp() {
	return Hp;
}

int Character::GetMp() {
	return Mp;
}

int Character::GetAtt() {
	return Att;
}

int Character::GetDef() {
	return Def;
}

int Character::GetMoney() {
	return money;
}

//----------------------------------------------------


bool Character::Sell(Item* _item) {
	SearchItem = Inven->GetHead()->GetNext();
	while (SearchItem) {	// 리스트 순회
		if (SearchItem->GetData() == _item) {	// 매게 변수(찾는 아이템) 과 일치한다면
			Item* ptr = SearchItem->GetData();	// 임시 포인터 변수에 저장
			this->InCreseGameMoney(ptr->GetPrice());	// 가격 계산
			Inven->Remove(SearchItem->GetData());		// 해당 아이템 리스트에서 삭제
			m_count--;
			this->SearchEnd();							// 순회한 노드 위치 초기화
			return true;
		}
		SearchItem = SearchItem->GetNext();				// 다음 노드로
	}
	return false;
}

bool Character::Buy(Item* _item) {
	if (_item != nullptr) {					
		if (this->DeCreseGameMoney(_item->GetPrice())) {	// 가격 계산 후 구매
			Inven->Insert(_item);	// 리스트에 추가
			m_count++;
			return true;
		}
	}
	else {
		return false;
	}
}

// 돈 계산을 위한 메소드

bool Character::InCreseGameMoney(int _money) {
	money += _money;
	return true;
}

bool Character::DeCreseGameMoney(int _money) {
	if (money - _money < NODATA) {
		return false;
	}
	else {
		money -= _money;
		return true;
	}
}

// ----------------------


// 장비 변경
bool Character::ChangeItem(Item* _item) {
	if (!Inven->Delete(_item)) {	// 인벤토리에 아이템이 없다.
		return false;
	}

	// 다이나믹 캐스트로 해당 아이템의 클래스형을 조사하고, 각각 파트에 장비를 착용한다.
	if (dynamic_cast<Wenpon*>(_item)) {
		m_wenpon->OffItem(this);	// 본래 착용하고 있던 장비는 해제
		Inven->Insert(m_wenpon);	// 다시 인벤토리로 넣는다.
		m_wenpon = dynamic_cast<Wenpon*>(_item);	// 그리고 새로운 장비를 착용

		m_wenpon->OnItem(this);	// 장비 착용 후 스탯 적용
		return true;
	}

	// 이하 동문

	if (dynamic_cast<Armor*>(_item)) {
		m_armor->OffItem(this);
		Inven->Insert(m_armor);
		m_armor = dynamic_cast<Armor*>(_item);

		m_armor->OnItem(this);
		return true;
	}

	if (dynamic_cast<Accessories*>(_item)) {
		m_accessories->OffItem(this);
		Inven->Insert(m_accessories);
		m_accessories = dynamic_cast<Accessories*>(_item);

		m_accessories->OnItem(this);
		return true;
	}

	return false;
}

//----------------------------------------------------

// 순회 노드 초기화
void Character::SearchEnd() {
	SearchItem = nullptr;
}

// 노드 순회 메소드
bool Character::GetItem(Item** temp) {
	if (SearchItem == nullptr) {	// 순회 노드가 nullptr 이라면
		SearchItem = Inven->GetHead();	// 순회 노드의 위치를 제일 처음으로 이동
	}

	SearchItem = SearchItem->GetNext();	// 순회 시작

	if (SearchItem != nullptr) {	// 순회 노드가 nullptr 이 아닌 데이터를 만나면
		*temp = SearchItem->GetData();	// 해당 노드에 현재 캐릭터의 순회 노드 위치의 아이템을 대입해준다.
		return true;
	}
	return false;
}

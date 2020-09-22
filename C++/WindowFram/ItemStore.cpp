#include "ItemStore.h"
IMPLEMENT_SINGLETON(ItemStore)
// 싱글톤 매크로 정의

// 아이템 리스트 초기화
void ItemStore::Init() {
	mItemInfo[mItemInfoCount++] = new Wenpon("Diamond Sword", 3000, 75);
	mItemInfo[mItemInfoCount++] = new Armor("Diamond Shield", 2000, 30);
	mItemInfo[mItemInfoCount++] = new Accessories("Balance Chain", 3000, 150, 150);
	mItemInfo[mItemInfoCount++] = new Wenpon("Dragon Bow", 5000, 125);
	mItemInfo[mItemInfoCount++] = new Armor("Timeless Shield", 4000, 60);
	mItemInfo[mItemInfoCount++] = new Accessories("Heaven Ring", 5000, 300, 300);
}

// 아이템 판매 (상점 시점에서)
bool ItemStore::Sell(const char* name) {
	Character* now = CharacterManager::GetInstance()->GetNowCharacter();
	// 현재 접속중인 캐릭터 저장

	// 아이템 리스트 순회
	for (int i = 0; i < mItemInfoCount; i++) {

		if (!strcmp(mItemInfo[i]->GetItemName(), name)) { // 아이템 목록 중에 캐릭터가 찾는 아이템이 있다면
			Item* item = nullptr; // 임시 객체

			// 다이나믹 캐스트로 종류를 분별하고, 그에 맞는 무기를 임시 객체에 저장한다.
			if (dynamic_cast<Wenpon*>(mItemInfo[i])) {
				item = new Wenpon(mItemInfo[i]->GetItemName(), mItemInfo[i]->GetPrice(), mItemInfo[i]->GetFirstAbility());
			}
			if (dynamic_cast<Armor*>(mItemInfo[i])) {
				item = new Armor(mItemInfo[i]->GetItemName(), mItemInfo[i]->GetPrice(), mItemInfo[i]->GetFirstAbility());
			}
			if (dynamic_cast<Accessories*>(mItemInfo[i])) {
				item = new Accessories(mItemInfo[i]->GetItemName(), mItemInfo[i]->GetPrice(), mItemInfo[i]->GetFirstAbility(),mItemInfo[i]->GetSecordAbility());
			}

			// 캐릭터가 그 아이템을 돈을 지불하고 구입한다.
			// 만일 돈이 부족하다면 구매할 수 없다.
			if (now->Buy(item)) {
				return true;
			}
		}
	}

	// 아이템을 못찾았거나, 돈이 부족할 시
	return false;
}

// 아이템 구매 (상점 시점에서)
bool ItemStore::Buy(const char* name) {
	Character* now = CharacterManager::GetInstance()->GetNowCharacter();
	// 현재 접속중인 캐릭터 저장

	Item* item = nullptr;
	while (now->GetItem(&item)) {	// 유저 캐릭터의 인벤토리 순회
		if (!strcmp(item->GetItemName(), name)) {	// 매개 변수의 이름과 일치하는 아이템이 있다면
			now->Sell(item);	// 캐릭터가 상점에게 판다.
			now->SearchEnd();	// 노드 위치 초기화
			return true;
		}
	}

	// 아이템을 찾지 못함.
	now->SearchEnd();	// 노드 위치 초기화
	return false;
}

// 아이템 리스트 출력
// 캐릭터 매니저와 마찬가지로 외부에 아이템 리스트를 출력하기 위한 함수이다.
// 무기의 클래스형을 분별하기 위해 다이나믹 캐스트를 사용했다.

void ItemStore::ShowItemInfo(HDC hdc, int x, int y) {
	char name[CHAR];
	char price[CHAR];
	char ability[CHAR];
	char ability2[CHAR];

	for (int i = 0; i < mItemInfoCount; i++) {

		wsprintf(name, mItemInfo[i]->GetItemName());
		wsprintf(price, "%d", mItemInfo[i]->GetPrice());
		wsprintf(ability, "%d", mItemInfo[i]->GetFirstAbility());
		wsprintf(ability2, "%d", mItemInfo[i]->GetSecordAbility());

		if (dynamic_cast<Wenpon*>(mItemInfo[i])) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 510, 230 + (20 * i), TEXT("Att + "), 6);
			TextOut(hdc, 540, 230 + (20 * i), ability, strlen(ability));
		}
		if (dynamic_cast<Armor*>(mItemInfo[i])) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 500, 230 + (20 * i), TEXT("Def + "), 6);
			TextOut(hdc, 540, 230 + (20 * i), ability, strlen(ability));
		}
		if (dynamic_cast<Accessories*>(mItemInfo[i])) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 450, 230 + (20 * i), TEXT("HP / MP + "), 10);
			TextOut(hdc, 520, 230 + (20 * i), ability, strlen(ability));
			TextOut(hdc, 550, 230 + (20 * i), TEXT(" / "), 3);
			TextOut(hdc, 560, 230 + (20 * i), ability2, strlen(ability2));
		}
	}
}

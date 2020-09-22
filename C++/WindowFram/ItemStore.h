#pragma once

#include "Wenpon.h"
#include "Armor.h"
#include "Accessories.h"

#include "CharacterManager.h"

// 아이템 상점을 담당하는 클래스
// 아이템 목록을 배열로 메뉴처럼 만들어놓음
// 싱글톤 매크로

class ItemStore {
	DECLARE_SINGLETONE(ItemStore)
private:
	// 생성자 초기화 작업
	ItemStore() {
		memset(mItemInfo, 0, sizeof(mItemInfo));
		mItemInfoCount = NODATA;
		mItemInfoIndex = NODATA;
	}
	// 아이템 포인터 배열 메모리 해제
	~ItemStore() {
		for (int i = 0; i < mItemInfoCount; i++) {
			delete mItemInfo[i];
		}
	}

	Item* mItemInfo[MAXITEM];	// 아이템 리스트
	int mItemInfoCount;			// 현재 아이템 리스트 개수
	int mItemInfoIndex;			// 아이템 리스트 순회
public:

	// 초기화
	void Init();

	// 판매 및 구입을 담당
	bool Sell(const char*);
	bool Buy(const char*);

	// 아이템 목록 출력
	void ShowItemInfo(HDC, int, int);

	// 읽기 접근자
	Item* GetItemInfo(int index) { return mItemInfo[index]; }
	int GetItemInfoCount() { return mItemInfoCount; }
	int GetItemInfoIndex() { return mItemInfoIndex; }
};
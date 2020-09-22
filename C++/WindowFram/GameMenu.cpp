#include "MainManager.h"


GameMenu* GameMenu::mPthis = nullptr;

GameMenu* GameMenu::GetInstance() {
	if (!mPthis) {
		mPthis = new GameMenu();
	}
	ItemStore::GetInstance();
	return mPthis;
}

void GameMenu::Destroy() {
	ItemStore::Destroy();
	if (mPthis) {
		delete mPthis;
	}
}

void GameMenu::DrawMenu(CBackBit* _bit) {
	// 각 도형의 좌표
	int Back_x = 80;
	int Back_y = 520;

	int inven_x = 700;
	int inven_y = 100;

	int store_x = 700;
	int store_y = 140;

	int stats_x = 700;
	int stats_y = 180;

	// 비트맵 함수
	HBITMAP bg;
	// RECT
	RECT rt;

	// 비트맵 할당
	bg = LoadBitmap(CWindowFrame::GetInstance()->GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP3));

	HDC hdc = _bit->GetBitmapDC();
	// Rect 호출
	GetClientRect(mouse->GetHWnd(), &rt);
	// 비트맵 그리기
	_bit->GdiBitMapDraw(hdc, 0, 0, rt.right, rt.bottom, bg);

	// 글자 배경 투명
	SetBkMode(hdc, TRANSPARENT);

	Rectangle(hdc, Back_x + 40 , Back_y + 20 , Back_x - 40 , Back_y - 20); // 이전으로 돌아가기

	Rectangle(hdc, inven_x + 40, inven_y + 15, inven_x - 40, inven_y - 15); // 인벤토리
	Rectangle(hdc, store_x + 40, store_y + 15, store_x - 40, store_y - 15); // 상점
	Rectangle(hdc, stats_x + 40, stats_y + 15, stats_x - 40, stats_y - 15); // 스탯

	// 문자열 출력
	TextOut(hdc, Back_x - 16, Back_y - 10, TEXT("Back"), 4);
	TextOut(hdc, inven_x - 35, inven_y - 10, TEXT("Inventory"), 9);
	TextOut(hdc, store_x - 23, store_y - 10, TEXT("Store"), 5);
	TextOut(hdc, stats_x - 23, stats_y - 10, TEXT("Stats"), 5);

	if (mouse->GetClick()) {	// 마우스 클릭 시
		if (col->CollisionEnterinPoint(Back_x, Back_y, mouse->GetX(), mouse->Gety(), 40, 20)) {	 // 이전으로 돌아가기
			// 초기화 작업 진행 후 이전 메뉴로 돌아간다.
			stats = false;
			inven = false;
			store = false;
			on = false;

			KeyBoard::GetInstance()->Init_Char();
			memset(name, 0, sizeof(name));

			// 전략 패턴
			MainManager::GetInstance()->SetDrawMenu(CharacterMenu::GetInstance());
		}

		if (col->CollisionEnterinPoint(inven_x, inven_y, mouse->GetX(), mouse->Gety(), 40, 15)) { // 인벤토리 메뉴 버튼
			if (!inven) {
				inven = true;
				store = false;
			}
			else if (inven && !buy && !sell && !on) {
				inven = false;
			}
		}

		if (col->CollisionEnterinPoint(store_x, store_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 상점 메뉴 버튼
			if (!store) {
				store = true;
				inven = false;
			}
			else if (store && !buy && !sell && !on) {
				store = false;
			}
		}

		if (col->CollisionEnterinPoint(stats_x, stats_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 스탯 메뉴 버튼
			if (!stats) {
				stats = true;
			}
			else {
				stats = false;
			}
		}
	}
	

	// 각각 인벤토리,상점,스탯 메뉴 활성화
	if (inven) {
		this->ShowInven(hdc);
	}
	if (store) {
		this->ShowStore(hdc);
	}
	if (stats) {
		this->ShowStats(hdc);
	}

	// 아이템 이름 입력 메뉴 활성화
	if (buy || sell || on) {
		SelectItem(hdc);
	}

	// 비트맵 해제
	//DeleteObject(bg);
	// DC 해제
	_bit->DeleteBitmapDC(hdc);
}

void GameMenu::SelectItem(HDC hdc) {
	Character* NowCharacter = CharacterManager::GetInstance()->GetNowCharacter();
	// 현재 접속중인 캐릭터를 임시 변수에 저장

	// 도형 좌표
	int ok_x = 355;
	int ok_y = 170;

	int cansel_x = 445;
	int cansel_y = 170;

	// BackGround
	Rectangle(hdc, 300, 75, 500, 200);
	TextOut(hdc, 365, 90, TEXT("Item Name"), 9);

	// 아이템 이름 입력란
	Rectangle(hdc, 310, 120, 490, 140);
	TextOut(hdc, 320, 125, name, strlen(name));

	Rectangle(hdc, ok_x + 40, ok_y + 20, ok_x - 40, ok_y - 20);
	Rectangle(hdc, cansel_x + 40, cansel_y + 20, cansel_x - 40, cansel_y - 20);

	TextOut(hdc, ok_x - 10, ok_y - 10, TEXT("OK"), 2);
	TextOut(hdc, cansel_x - 25, cansel_y - 10, TEXT("Cansel"), 6);
	//--------------------------------------------------------------------------

	if (mouse->GetClick()) {	// 마우스 클릭 시
		if (strcmp(name, "")) { // 아이템 이름이 공백이 아니라면
			if (col->CollisionEnterinPoint(ok_x, ok_y, mouse->GetX(), mouse->Gety(), 40, 20)) { // OK 버튼

				KillTimer(mouse->GetHWnd(), 0);

				if (buy) {	// 아이템 구매
					if (ItemStore::GetInstance()->Sell(name)) {
						MessageBox(mouse->GetHWnd(), "아이템을 구입했습니다.", "", MB_OK);
					}
					else {
						MessageBox(mouse->GetHWnd(), "아이템을 구입 할 수 없습니다.", "", MB_OK);
					}
				}
				if (sell) {	// 아이템 판매
					if (ItemStore::GetInstance()->Buy(name)) {
						MessageBox(mouse->GetHWnd(), "아이템을 판매했습니다.", "", MB_OK);
					}
					else {
						MessageBox(mouse->GetHWnd(), "아이템을 판매 할 수 없습니다.", "", MB_OK);
					}
				}

				if (on) {	// 장비 변경
					Item* ptr = nullptr;
					bool flug = false;

					while (NowCharacter->GetItem(&ptr)) {	 // 현재 접속중인 캐릭터의 인벤토리 순회
						if (!strcmp(ptr->GetItemName(), name)) {	// 장착할 아이템을 찾았다면
							NowCharacter->ChangeItem(ptr);	// 장비 변경
							MessageBox(mouse->GetHWnd(), "해당 아이템을 장착했습니다.", "", MB_OK);
							NowCharacter->SearchEnd();	// 노드 초기화
							flug = true;
							break;
						}
					}
					NowCharacter->SearchEnd();	// 노드 초기화

					if (!flug) {	// 아이템을 찾지 못함.
						MessageBox(mouse->GetHWnd(), "해당 아이템은 인벤토리에 없습니다.", "", MB_OK);
					}
 				}
			}

			// 초기화 작업

			buy = false;
			sell = false;
			on = false;

			KeyBoard::GetInstance()->Init_Char();
			memset(name, 0, sizeof(name));

			SetTimer(mouse->GetHWnd(), 0, 100, nullptr);
		}

		if (col->CollisionEnterinPoint(cansel_x, cansel_y, mouse->GetX(), mouse->Gety(), 40, 20)) { // 취소 버튼
			// 초기화 작업
			buy = false;
			sell = false;
			on = false;

			KeyBoard::GetInstance()->Init_Char();
			memset(name, 0, sizeof(name));
		}
	}
}

void GameMenu::ShowInven(HDC hdc) {

	// 도형 좌표
	int on_x = 460;
	int on_y = 470;

	int cansel_x = 560;
	int cansel_y = 470;

	// 글자 배경 투명
	SetBkMode(hdc, TRANSPARENT);

	// BackGround
	Rectangle(hdc, 200, 200, 600, 450);
	Rectangle(hdc, 210, 210, 590, 440);
	Rectangle(hdc, 210, 210, 590, 230);

	Rectangle(hdc, on_x + 40, on_y + 15, on_x - 40, on_y - 15); // 판매
	Rectangle(hdc, cansel_x + 40, cansel_y + 15, cansel_x - 40, cansel_y - 15); // 종료

	// 문자열 출력
	TextOut(hdc, on_x - 35, on_y - 10, TEXT("Equipment"), 9);
	TextOut(hdc, cansel_x - 25, cansel_y - 10, TEXT("Cansel"), 6);

	TextOut(hdc, 220, 210, TEXT("Name"), 4);
	TextOut(hdc, 380, 210, TEXT("Price"), 5);
	TextOut(hdc, 500, 210, TEXT("Ability"), 7);

	// 현재 접속중인 캐릭터가 보유한 아이템 출력
	CharacterManager::GetInstance()->ShowNowCharacterInven(hdc, 0, 0);

	if (mouse->GetClick()) {	 // 마우스 클릭 시
		if (col->CollisionEnterinPoint(on_x, on_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 장비 변경 버튼
			on = true;
		}

		if (col->CollisionEnterinPoint(cansel_x, cansel_y, mouse->GetX(), mouse->Gety(), 40, 15)) { // 취소 버튼
			inven = false;
		}
	}
}

void GameMenu::ShowStore(HDC hdc) {
	// 도형 좌표
	int buy_x = 360;
	int buy_y = 470;

	int sell_x = 460;
	int sell_y = 470;

	int cansel_x = 560;
	int cansel_y = 470;

	// 글자 배경 투명
	SetBkMode(hdc, TRANSPARENT);

	// BackGround
	Rectangle(hdc, 200, 200, 600, 450);
	Rectangle(hdc, 210, 210, 590, 440);
	Rectangle(hdc, 210, 210, 590, 230);

	Rectangle(hdc, buy_x + 40, buy_y + 15, buy_x - 40, buy_y - 15); // 구입
	Rectangle(hdc, sell_x + 40, sell_y + 15, sell_x - 40, sell_y - 15); // 판매
	Rectangle(hdc, cansel_x + 40, cansel_y + 15, cansel_x - 40, cansel_y - 15); // 종료

	// 문자열 출력
	TextOut(hdc, buy_x - 20, buy_y - 10, TEXT("Buy"), 3);
	TextOut(hdc, sell_x - 20, sell_y - 10, TEXT("Sell"), 4);
	TextOut(hdc, cansel_x - 25, cansel_y - 10, TEXT("Cansel"), 6);

	TextOut(hdc, 220, 210, TEXT("Name"), 4);
	TextOut(hdc, 380, 210, TEXT("Price"), 5);
	TextOut(hdc, 500, 210, TEXT("Ability"), 7);

	// 상점의 판매 아이템 리스트 출력
	ItemStore::GetInstance()->ShowItemInfo(hdc, 0, 0);

	if (mouse->GetClick() && !buy && !sell) {	// 마우스 클릭 and 구매,판매 혼선 방지
		if (col->CollisionEnterinPoint(buy_x, buy_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 구매 버튼
			buy = true;
		}

		if (col->CollisionEnterinPoint(sell_x, sell_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 판매 버튼
			sell = true;
		}

		if (col->CollisionEnterinPoint(cansel_x, cansel_y, mouse->GetX(), mouse->Gety(), 40, 15)) {	// 취소 버튼
			store = false;
		}
	}
}

void GameMenu::ShowStats(HDC hdc) {

	// 도형 좌표
	int esc_x = 140;
	int esc_y = 270;

	// 글자 배경 투명
	SetBkMode(hdc, TRANSPARENT);

	// 현재 접속된 캐릭터 정보
	CharacterManager::GetInstance()->PrintCharacter(hdc, 0, 0);

	// 닫기 버튼
	Rectangle(hdc, esc_x + 30, esc_y + 15, esc_x - 30, esc_y - 15);

	TextOut(hdc, esc_x - 22, esc_y - 10, TEXT("Cansel"), 6);

	if (mouse->GetClick()) {	// 마우스 클릭 시
		if (col->CollisionEnterinPoint(esc_x, esc_y, mouse->GetX(), mouse->Gety(), 30, 15)) {	// 취소 버튼
			stats = false;
		}
	}
}

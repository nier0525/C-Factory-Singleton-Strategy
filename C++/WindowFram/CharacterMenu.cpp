#include "CharacterMenu.h"
#include "MainManager.h"

CharacterMenu* CharacterMenu::pthis = nullptr;

CharacterMenu* CharacterMenu::GetInstance() {
	if (!pthis) {
		pthis = new CharacterMenu();
	}

	CharacterManager::GetInstance();
	return pthis;
}

void CharacterMenu::Destory() {
	CharacterManager::Destroy();
	if (pthis) {
		delete pthis;
	}
}

// 메뉴 메서드
void CharacterMenu::DrawMenu(CBackBit* _bit) {

	// 각각 도형의 위치를 저장한 정수형 변수
	int logout_x = 80;
	int logout_y = 520;
	int del_x = 180;
	int del_y = 520;

	int sel_x = 700;
	int sel_y = 100;

	int make_x = 700;
	int make_y = 140;

	int remove_x = 700;
	int remove_y = 180;

	int x[MAXCOUNT];
	int y[MAXCOUNT];
	
	// 비트맵 배경 변수
	HBITMAP bg;
	// RECT
	RECT rt;

	// 비트맵 할당
	bg = LoadBitmap(CWindowFrame::GetInstance()->GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP2));

	// 백비트의 DC 를 저장
	HDC hdc = _bit->GetBitmapDC();

	// RECT 호출
	GetClientRect(mouse->GetHWnd(), &rt);
	// 비트맵 그리기
	_bit->GdiBitMapDraw(hdc, 0, 0, rt.right, rt.bottom, bg);

	Rectangle(hdc, logout_x + 40, logout_y + 20, logout_x - 40, logout_y - 20);	// 로그아웃
	Rectangle(hdc, del_x + 40, del_y + 20, del_x - 40, del_y - 20);	// 회원탈퇴

	Rectangle(hdc, sel_x + 40, sel_y + 15, sel_x - 40, sel_y - 15);	// 선택
	Rectangle(hdc, make_x + 40, make_y + 15, make_x - 40, make_y - 15);	// 생성
	Rectangle(hdc, remove_x + 40, remove_y + 15, remove_x - 40, remove_y - 15);	// 삭제

	User* NowUser = LoginManager::GetInstance()->GetNowUser();
	// 현재 접속중인 유저 객체
	Character* ptr = nullptr;
	// 임시 캐릭터 객체


	// 캐릭터가 생성될 때마다 캐릭터창에 생성되는 캐릭터 정보를 구현
	for (int i = 0; i < LoginManager::GetInstance()->GetNowUser()->GetCount(); i++) { // 캐릭터 개수의 for 문
		// 도형과 텍스트 좌표
		x[i] = 310;
		y[i] = 100 + (i * 50);

		// 출력 내용
		Rectangle(hdc, x[i] + 300, y[i] + 20 , x[i] - 300, y[i] - 20);
		if (NowUser->GetCharacter(&ptr)) {
			TextOut(hdc, x[i] - 290, y[i] - 10, "Name : ", 6);
			TextOut(hdc, x[i] - 230, y[i] - 10, ptr->GetNickName(), strlen(ptr->GetNickName()));
			TextOut(hdc, x[i] + 120, y[i] - 10, "Brood :", 7);
			if (dynamic_cast<Oak*>(ptr)) {
				TextOut(hdc, x[i] + 180, y[i] - 10, "Oak", 3);
			}
			if (dynamic_cast<Elf*>(ptr)) {
				TextOut(hdc, x[i] + 180, y[i] - 10, "Elf", 3);
			}
		}
	}

	// 노드 초기화
	NowUser->SearchEnd();

	// 텍스트 출력
	TextOut(hdc, logout_x - 25, logout_y - 10, TEXT("LogOut"), 6);
	TextOut(hdc, del_x - 16 , del_y - 10, TEXT("Drop"), 4);
	TextOut(hdc, sel_x - 25, sel_y - 10, TEXT("Select"), 6);
	TextOut(hdc, make_x - 25, make_y - 10, TEXT("New"), 3);
	TextOut(hdc, remove_x - 25, remove_y - 10, TEXT("Delete"), 6);

	// 마우스 클릭 시 충돌 이벤트
	if (mouse->GetClick() && !New && !Remove && !Select) {
		KillTimer(mouse->GetHWnd(), 0);
		// 로그아웃 버튼을 눌렀을 때
		if (col->CollisionEnterinPoint(logout_x, logout_y, mouse->GetX(), mouse->Gety(), 40, 20)) {
			LoginManager::GetInstance()->LogOut(); // 로그아웃 상태 전환
			MainManager::GetInstance()->SetDrawMenu(LoginMenu::GetInstance()); // 전략 패턴으로 이용해 로그인 메뉴로 변경
		}

		// 드롭(회원탈퇴) 버튼을 눌렀을 때
		if (col->CollisionEnterinPoint(del_x, del_y, mouse->GetX(), mouse->Gety(), 40, 20)) {
			LoginManager::GetInstance()->Delete(); // 현재 접속중인 유저 정보 삭제
			MainManager::GetInstance()->SetDrawMenu(LoginMenu::GetInstance()); // 위와 같음
		}

		// 캐릭터 생성 버튼
		if (col->CollisionEnterinPoint(make_x, make_y, mouse->GetX(), mouse->Gety(), 40, 15)) {
			New = true;
		}

		// 캐릭터 선택 버튼
		if (col->CollisionEnterinPoint(sel_x, sel_y, mouse->GetX(), mouse->Gety(), 40, 15)) {
			Select = true;
		}

		// 캐릭터 삭제 버튼
		if (col->CollisionEnterinPoint(remove_x, remove_y, mouse->GetX(), mouse->Gety(), 40, 15)) {
			Remove = true;
		}

		SetTimer(mouse->GetHWnd(), 0, 100, nullptr);

		// 킬타이머로 타이머를 중지하고, 모든 작업 끝난 후 다시 타이머를 돌리게 한다.
		// if 문이 계속 돌아가는 문제를 해결하고자 이렇게 사용하였다.
	}

	// 생성,선택,삭제 버튼을 눌렀다면
	if (New || Select || Remove) {
		this->CharacterSeMenu(hdc, _bit); // 캐릭터 세부 메뉴 활성화
	}

	DeleteObject(bg); // 비트맵 메모리 해제
	_bit->DeleteBitmapDC(hdc); // DC 해제
}

void CharacterMenu::CharacterSeMenu(HDC hdc, CBackBit* _bit) {

	// 각각 도형의 위치
	int x1 = 280;
	int y1 = 200;

	int x2 = 520;
	int y2 = 200;

	int back_x = 400;
	int back_y = 350;

	int ok_x = 360;
	int ok_y = 330;

	int no_x = 440;
	int no_y = 330;

	// 비트맵 변수
	HBITMAP oak, elf;

	// 비트맵 할당
	oak = LoadBitmap(CWindowFrame::GetInstance()->GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP4));
	elf = LoadBitmap(CWindowFrame::GetInstance()->GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP5));

	// 글자 배경 투명색
	SetBkMode(hdc, TRANSPARENT);

	// 캐릭터 생성 시 캐릭터 선택에 관련된 메뉴
	if (!Sel_Oak && !Sel_Elf && !Remove && !Select) {

		// 관련 도형
		Rectangle(hdc, x1 + 100, y1 + 100, x1 - 100, y1 - 100);
		Rectangle(hdc, x2 + 100, y2 + 100, x2 - 100, y2 - 100);
		Rectangle(hdc, back_x + 40, back_y + 20, back_x - 40, back_y - 20);

		// 비트맵 그리기
		_bit->GdiBitMapDraw(hdc, 180, 100, 200, 200, oak);
		_bit->GdiBitMapDraw(hdc, 420, 100, 200, 200, elf);

		// 텍스트 출력
		TextOut(hdc, x1 - 10, y1, TEXT("Oak"), 3);
		TextOut(hdc, x2 - 10, y2, TEXT("Elf"), 3);
		TextOut(hdc, back_x - 15, back_y - 10, TEXT("Back"), 4);

		// 마우스 클릭 시
		if (mouse->GetClick()) {
			// 오크 선택 시
			if (col->CollisionEnterinPoint(x1, y1, mouse->GetX(), mouse->Gety(), 100, 100)) {
				Sel_Oak = true;
			}
			// 엘프 선택 시
			if (col->CollisionEnterinPoint(x2, y2, mouse->GetX(), mouse->Gety(), 100, 100)) {
				Sel_Elf = true;
			}
			// 취소 버튼
			if (col->CollisionEnterinPoint(back_x, back_y, mouse->GetX(), mouse->Gety(), 40, 20)) {
				New = false;
			}
		}
	}

	// 누른 버튼에 따라 이벤트가 나뉜다.
	if (Sel_Oak || Sel_Elf || Select || Remove) {
		if (mouse->GetClick()) {	// 마우스 클릭 시
			if (strcmp(name, "")) {	// 이름이 공백이 아니라면
				if (col->CollisionEnterinPoint(ok_x, ok_y, mouse->GetX(), mouse->Gety(), 30, 15)) {

					KillTimer(mouse->GetHWnd(), 0);

					// 입력된 이름의 값으로 메서드를 진행한다.

					if (Sel_Oak) {	// 오크 생성
						if (CharacterManager::GetInstance()->CreateCharacter(name, OakFactory::GetInstance())) {
							MessageBox(mouse->GetHWnd(), "오크 종족을 생성했습니다.", "", MB_OK);
						}
						else {
							MessageBox(mouse->GetHWnd(), "캐릭터 생성에 실패했습니다.", "", MB_OK);
						}
					}

					if (Sel_Elf) {	// 엘프 생성
						if (CharacterManager::GetInstance()->CreateCharacter(name, ElfFactory::GetInstance())) {
							MessageBox(mouse->GetHWnd(), "엘프 종족을 생성했습니다.", "", MB_OK);
						}
						else {
							MessageBox(mouse->GetHWnd(), "캐릭터 생성에 실패했습니다.", "", MB_OK);
						}
					}

					if (Select) {	// 캐릭터 선택
						if (CharacterManager::GetInstance()->SelectCharacter(name)) {
							MainManager::GetInstance()->SetDrawMenu(GameMenu::GetInstance());
						}
						else {
							MessageBox(mouse->GetHWnd(), "해당 캐릭터를 찾을 수 없습니다.", "", MB_OK);
						}
					}

					if (Remove) {	// 캐릭터 삭제
						if (CharacterManager::GetInstance()->DropCharacter(name)) {
							MessageBox(mouse->GetHWnd(), "해당 캐릭터를 삭제합니다.", "", MB_OK);
						}
						else {
							MessageBox(mouse->GetHWnd(), "해당 캐릭터를 찾을 수 없습니다.", "", MB_OK);
						}
					}

					// 값 초기화 작업

					New = false;
					Sel_Oak = false;
					Sel_Elf = false;

					Select = false;
					Remove = false;

					KeyBoard::GetInstance()->Init_Char();
					memset(name, 0, sizeof(name));

					SetTimer(mouse->GetHWnd(), 0, 100, nullptr);
				}
			}

			if (col->CollisionEnterinPoint(no_x, no_y, mouse->GetX(), mouse->Gety(), 30, 15)) {	// 취소 버튼
				Sel_Oak = false;
				Sel_Elf = false;
				Select = false;
				Remove = false;

				KeyBoard::GetInstance()->Init_Char();
				memset(name, 0, sizeof(name));
			}
		}
	}

	// 캐릭터 이름 입력 메뉴
	if (Sel_Oak || Sel_Elf || Select || Remove) {
		Rectangle(hdc, 300, 250, 500, 350);
		Rectangle(hdc, 320, 280, 480, 300);
		TextOut(hdc, 350, 260, TEXT("Character Name"), 14);

		Rectangle(hdc, ok_x + 30 , ok_y + 15 , ok_x - 30, ok_y - 15);
		Rectangle(hdc, no_x + 30, no_y + 15, no_x - 30, no_y - 15);
		TextOut(hdc, ok_x - 10, ok_y - 10, TEXT("OK"), 2);
		TextOut(hdc, no_x - 22, no_y - 10, TEXT("Cansel"), 6);

		TextOut(hdc, 325, 280, name, strlen(name));
	}

	DeleteObject(oak);
	DeleteObject(elf);
}
#include "LoginMenu.h"
#include "MainManager.h"

LoginMenu* LoginMenu::pthis = nullptr;

LoginMenu* LoginMenu::GetInstance() {
	if (!pthis) {
		pthis = new LoginMenu();
	}
	LoginManager::GetInstance();
	return pthis;
}

void LoginMenu::Destory() {
	LoginManager::Destory();

	if (pthis) {
		delete pthis;
	}
}

void LoginMenu::DrawMenu(CBackBit* _bit) {

	// 도형 좌표
	int id_x = 400;
	int id_y = 280;
	int pass_x = 400;
	int pass_y = 320;

	int new_x = 340;
	int new_y = 380;
	int login_x = 460;
	int login_y = 380;
	int Exit_x = 400;
	int Exit_y = 420;

	// Rect
	RECT rt;

	// 비트맵 변수
	HBITMAP bg;
	// 비트맵 할당
	bg = LoadBitmap(CWindowFrame::GetInstance()->GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP1));

	HDC hdc = _bit->GetBitmapDC();

	// Rect 호출
	GetClientRect(mouse->GetHWnd(), &rt);
	// 비트맵 그리기
	_bit->GdiBitMapDraw(hdc, 0, 0, rt.right, rt.bottom, bg);

	Rectangle(hdc, id_x + 100, id_y + 10, id_x - 100, id_y - 10); // ID 입력란
	Rectangle(hdc, pass_x + 100, pass_y + 10, pass_x - 100, pass_y - 10); // PASS 입력란

	Rectangle(hdc, new_x + 40, new_y + 20, new_x - 40, new_y - 20); // 회원가입
	Rectangle(hdc, login_x + 40, login_y + 20, login_x - 40, login_y - 20); // 로그인
	Rectangle(hdc, Exit_x + 100, Exit_y + 10, Exit_x - 100, Exit_y - 10); // 종료

	// 글자 배경 투명
	SetBkMode(hdc, TRANSPARENT);

	// 각 UI 텍스트
	TextOut(hdc, id_x - 120, id_y - 10, TEXT("ID"), 2);
	TextOut(hdc, pass_x - 185, pass_y - 10, TEXT("PASSWORD"), 8);
	TextOut(hdc, new_x - 15, new_y - 10, TEXT("New"), 3);
	TextOut(hdc, login_x - 17, login_y - 10, TEXT("Login"), 5);
	TextOut(hdc, Exit_x - 16, Exit_y - 10, TEXT("EXIT"), 4);

	if (ID) {
		Ellipse(hdc, id_x + 130 , id_y + 10, id_x + 110, id_y - 10);	// ID 선택
	}
	if (PASS) {
		Ellipse(hdc, pass_x + 130, pass_y + 10, pass_x + 110, pass_y - 10); // PASSWORD 선택
	}

	// id, pass 출력
	TextOut(hdc, id_x - 90, id_y - 10, id, strlen(id));	
	TextOut(hdc, pass_x - 90, pass_y - 10, pass, strlen(pass));
	
	if (mouse->GetClick()) {	// 마우스 클릭 시
		if (col->CollisionEnterinPoint(id_x, id_y, mouse->GetX(), mouse->Gety(), 100, 10)) {	// ID 입력란
			ID = true;
			PASS = false;
			memset(id, 0, sizeof(id));
			KeyBoard::GetInstance()->Init_Char();
		}

		else if (col->CollisionEnterinPoint(pass_x, pass_y, mouse->GetX(), mouse->Gety(), 100, 10)) {	// PASSWORD 입력란
			ID = false;
			PASS = true;
			memset(pass, 0, sizeof(pass));
			KeyBoard::GetInstance()->Init_Char();
		}

		else {	// 그 외에 곳을 클릭한다면 초기화
			ID = false;
			PASS = false;
		}

		if (col->CollisionEnterinPoint(new_x, new_y, mouse->GetX(), mouse->Gety(), 40, 20) && strcmp(id, "") && strcmp(pass, "")) {	// 회원가입 버튼
			
			KillTimer(mouse->GetHWnd(), 0);

			if (LoginManager::GetInstance()->New(id, pass)) {
				MessageBox(mouse->GetHWnd(), "회원가입 되었습니다.", "", MB_OK);
			}
			else {
				MessageBox(mouse->GetHWnd(), "중복된 ID 입니다.", "", MB_OK);
			}
		}
	
		if (col->CollisionEnterinPoint(login_x, login_y, mouse->GetX(), mouse->Gety(), 40, 20) && strcmp(id, "") && strcmp(pass, "")) {	// 로그인 버튼
		
			KillTimer(mouse->GetHWnd(), 0);

			if (LoginManager::GetInstance()->Login(id, pass)) {
				MainManager::GetInstance()->SetDrawMenu(CharacterMenu::GetInstance());	// 로그인 성공 시 캐릭터 메뉴로 전환
				KeyBoard::GetInstance()->Init_Char();
			}
			else {
				MessageBox(mouse->GetHWnd(), "ID 또는 PASSWORD 가 일치하지 않습니다.", "", MB_OK);
			}
		}

		if (col->CollisionEnterinPoint(Exit_x, Exit_y, mouse->GetX(), mouse->Gety(), 100, 10)) {	// 종료 버튼
			PostQuitMessage(0); // 윈도우 프로시저 종료
		}

		mouse->SetclickUp();
		SetTimer(mouse->GetHWnd(), 0, 10, nullptr);
	}

	// 비트맵,DC 해제
	DeleteObject(bg);
	_bit->DeleteBitmapDC(hdc);
}
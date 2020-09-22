#include "KeyBoard.h"

KeyBoard* KeyBoard::pthis = nullptr;

KeyBoard* KeyBoard::GetInstance() {
	if (!pthis) {
		pthis = new KeyBoard();
	}
	return pthis;
}

void KeyBoard::Destory() {
	if (pthis) {
		delete pthis;
	}
}

// 초기화 작업
void KeyBoard::Init(HWND hWnd, WPARAM wParam) {
	m_hWnd = hWnd;
	m_wParam = wParam;
	KeyDown = false;

	memset(str, NULL, sizeof(str));
	len = NULL;
}

// 입력한 문자열 초기화
void KeyBoard::Init_Char() {
	memset(str, NULL, sizeof(str));
	len = NULL;
}

// 연결된 좌표를 방향키에 따라서 이동시켜주는 간단한 함수
void KeyBoard::VK_move(int* x, int* y, int move) {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		*x -= move;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		*x += move;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		*y += move;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		*y -= move;
	}
}

// 키보드에서 문자열을 입력 받아 반환해준다.
const char* KeyBoard::GetKeyChar() {
	len = strlen(str);	// 문자열의 길이를 저장한다.
	if (len <= 20) {	// 문자열은 최대 20 까지
		str[len] = (char)m_wParam;	// 키보드 입력을 char 로 형변환 시킨 후 str 문자열에 저장한다.
		str[len + 1] = NULL;	// 입력된 문자열 다음 문자열은 nullptr
	}

	if (m_wParam == VK_BACK && len != NULL) {	// 문자열이 빈 상태에서 백키를 누를 시 아무것도 안한다.
		str[len - 1] = NULL;
	}
	if (m_wParam == VK_BACK && len == NULL) {	// 백키를 누르면 입력된 문자 중 하나를 지운다.
		str[len] = NULL;
	}

	return str; // 문자열 반환
}
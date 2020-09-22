#pragma once

#include "Global.h"

// 키보드 클래스
// 엄청 간단하게 구현해놓았다.
// 싱글톤 적용

class KeyBoard {
private:
	static KeyBoard* pthis;
	KeyBoard() {}
	~KeyBoard() {}

	HWND m_hWnd;	// 핸들 변수
	WPARAM m_wParam;	// wParam 을 저장할 변수
	bool KeyDown;		// 키보드가 눌렀는 지 체크

    char str[CHAR];		// 문자열 입력 시 값을 저장할 변수
	int len;			// 문자열 길이
public:
	static KeyBoard* GetInstance();
	static void Destory();

	void Init(HWND hWnd, WPARAM wParam);	// 초기화 작업

	void SetKey(WPARAM wParam) { m_wParam = wParam; }	// wParam 쓰기 접근자
	void VK_move(int* x, int* y, int move);	// 상,하,좌,우 이동에 관련된 간단한 함수 구현
	void Init_Char();	// 입력된 문자열 초기화

	void Down() { KeyDown = true; }	// 키보드 다운
	void Up() { KeyDown = false; }	// 키보드 업
	bool State() { return KeyDown; }	// 키보드 상태

	// 읽기 접근자
	WPARAM GetKeyCode() const { return m_wParam; }
	HWND GethWnd() { return m_hWnd; }
	const char* GetKeyChar();
};
#pragma once

#include "GameManager.h"

// 로그인 메뉴 클래스
// 회원가입,로그인,종료 등을 담당하는 게임 내에 타이틀 화면 역할을 담당하는 클래스
// 싱글톤 적용

class LoginMenu : public GameManager {
private:
	static LoginMenu* pthis;
	// 생성자 초기화 작업
	LoginMenu() {
		memset(id, 0, sizeof(id));
		memset(pass, 0, sizeof(pass));
	}
	~LoginMenu() {}

	char id[CHAR];	// ID 
	char pass[CHAR];	// PASSWORD

	bool ID = true;
	bool PASS = false;
public:
	static LoginMenu* GetInstance();
	static void Destory();

	// 로그인 메뉴
	void DrawMenu(CBackBit* _bit);

	// 쓰기 접근자
	void SetId(const char* _id) { strcpy(id,_id); }
	void SetPass(const char* _pass) { strcpy(pass, _pass); }

	// 읽기 접근자
	const char* GetId() { return id; }
	const char* GetPass() { return pass; }

	bool GetIdState() { return ID; }
	bool GetPassState() { return PASS; }
};
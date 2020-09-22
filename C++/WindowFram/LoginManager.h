#pragma once

#include "User.h"

// 로그인 매니저 클래스
// 유저 생성,삭제,로그인,로그아웃 등을 담당함
// 싱글톤 적용

class LoginManager {
private:
	// 유저 리스트
	ListNode<User*>* UserList;
	// 유저 리스트 순회 노드
	Node<User*>* SearchUser;
	// 현재 접속중인 유저
	User* NowUser;

	static LoginManager* pthis;
	LoginManager();
	~LoginManager();
public:
	// 싱글톤 메서드
	static LoginManager* GetInstance();
	static void Destory();

	// 현재 접속 유저 읽기 접근자
	User* GetNowUser();
	void Init(); // 초기화 메서드

	// 생성,로그인,로그아웃,삭제 메서드
	bool New(const char* id, const char* pass);
	bool Login(const char* id, const char* pass);
	void LogOut();
	void Delete();

	// 유저 리스트 순회 메서드
	bool GetUser(User**);
	// 순회 노드 초기화
	void SearchEnd();

	void LoadUserList(User* user) {
		SearchUser = UserList->GetHead()->GetNext();
		// 순회 노드에 첫 노드를 저장

		while (SearchUser) { // 순회 시작
			if (!strcmp(SearchUser->GetData()->GetId(), user->GetId())) { // 현재 유저 리스트 중에 중복된 아이디가 있는 지 검사
				return; // 있으면 false
			}
			SearchUser = SearchUser->GetNext(); // 다음 노드로 이동
		}
		UserList->Insert(user);
	}
};
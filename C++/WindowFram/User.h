#pragma once

#include "ListNode.h"
#include "Character.h"

// 유저 객체

class User {
private:
	char id[CHAR];	// ID
	char pass[CHAR];	// PASSWORD
	bool state;			// 로그인 상태

	int count;			// 가지고 있는 캐릭터 개수

	// 보유하고 있는 캐릭터 리스트
	ListNode<Character*>* UserCharacterList;
	// 캐릭터 리스트 순회 노드
	Node<Character*>* SearchCharacter;

public:
	User(const char*, const char*);	 // 매개 변수는 ID, PASSWORD
	~User();

	// 쓰기 접근자
	void SetId(const char*);
	void SetPass(const char*);
	void SetCount(int);

	// 읽기 접근자
	const char* GetId();
	const char* GetPass();
	int GetCount();

	// 로그인,로그아웃에 따른 state 값 변경
	bool Login();
	bool LogOut();

	// 캐릭터 생성,삭제, 최대 보유량 검사를 담당
	bool NewCharacter(Character*);
	bool DelCharacter(Character*);
	bool CharacterCountCheak();

	// 순회 노드 초기화
	void SearchEnd();
	// 캐릭터 리스트 순회 메서드
	bool GetCharacter(Character**);

	void LoadCharacter(Character* temp) {
		SearchCharacter = UserCharacterList->GetHead()->GetNext();

		while (SearchCharacter) {
			if (!strcmp(SearchCharacter->GetData()->GetNickName(), temp->GetNickName())) {
				return;
			}
			SearchCharacter = SearchCharacter->GetNext();
		}
		UserCharacterList->Insert(temp);
	}
};
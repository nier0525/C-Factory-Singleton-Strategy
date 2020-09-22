#include "User.h"

// 생성자 초기화 작업
User::User(const char* _id, const char* _pass) {
	strcpy(id, _id);
	strcpy(pass, _pass);
	count = NODATA;

	state = false;

	UserCharacterList = new ListNode<Character*>();	// 아이템 리스트 동적 할당
	SearchCharacter = nullptr;
}

// 동적할당 된 아이템 리스트 메모리 해제
User::~User() {
	if (UserCharacterList != nullptr) { delete UserCharacterList; }
}

// -------------------------------------------------------- 쓰기 접근자

void User::SetId(const char* _id) {
	strcpy(id, _id);
}

void User::SetPass(const char* _pass) {
	strcpy(pass, _pass);
}

void User::SetCount(int _count) {
	count = _count;
}

// -------------------------------------------------------- 읽기 접근자

const char* User::GetId() {
	return id;
}

const char* User::GetPass() {
	return pass;
}

int User::GetCount() {
	return count;
}

// --------------------------------------------------------

// 로그인, 로그아웃에 따른 state 값 변경 후 반환
bool User::Login() {
	state = true;
	return state;
}

bool User::LogOut() {
	state = false;
	return state;
}

// 순회 노드 초기화
void User::SearchEnd() {
	SearchCharacter = nullptr;
}

 // --------------------------------------------------------

// 캐릭터 생성 메서드
bool User::NewCharacter(Character* temp) {
	UserCharacterList->Insert(temp);
	count++;
	return true;
}

// 캐릭터 삭제 메서드
bool User::DelCharacter(Character* temp) {
	if (!UserCharacterList->Remove(temp)) {
		return false;
	}
	count--;
	return true;
}

// 캐릭터 최대 보유량 확인 메서드
bool User::CharacterCountCheak() {
	if (count < MAXCOUNT) {
		return true;
	}
	return false;
}

// 캐릭터 리스트 순회
bool User::GetCharacter(Character** temp) {
	if (SearchCharacter == nullptr) {	// 순회 노드가 nullptr 라면
		SearchCharacter = UserCharacterList->GetHead();	// 순회 노드 위치를 첫 노드로 이동
	}
	SearchCharacter = SearchCharacter->GetNext();	// 순회 시작

	if (SearchCharacter != nullptr) {	// 순회 노드가 노드를 만날때마다
		*temp = SearchCharacter->GetData();	// 매개변수에 데이터 값을 넘김
		return true;
	}
	return false;
}

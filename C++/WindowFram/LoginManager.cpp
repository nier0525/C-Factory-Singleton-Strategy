#include "LoginManager.h"

LoginManager* LoginManager::pthis = nullptr;

LoginManager* LoginManager::GetInstance() {
	if (!pthis) {
		pthis = new LoginManager();
	}
	return pthis;
}

void LoginManager::Destory() {
	if (pthis) {
		delete pthis;
		pthis = nullptr;
	}
}

// 생성자 초기화
LoginManager::LoginManager() {
	UserList = nullptr;
	SearchUser = nullptr;
	NowUser = nullptr;
}

// 유저 리스트 메모리 해제
LoginManager::~LoginManager() {
	delete UserList;
}

void LoginManager::Init() {
	UserList = new ListNode<User*>();	// 유저 리스트 동적 할당
}

// 현재 접속중인 유저 객체 반환
User* LoginManager::GetNowUser() {
	return NowUser;
}

// 유저 생성
bool LoginManager::New(const char* id, const char* pass) {
	SearchUser = UserList->GetHead()->GetNext();
	// 순회 노드에 첫 노드를 저장

	while (SearchUser) { // 순회 시작
		if (!strcmp(SearchUser->GetData()->GetId(), id)) { // 현재 유저 리스트 중에 중복된 아이디가 있는 지 검사
			return false; // 있으면 false
		}
		SearchUser = SearchUser->GetNext(); // 다음 노드로 이동
	}
	
	UserList->Insert(new User(id, pass)); // 유저 리스트에 추가
	return true;
}

// 로그인
bool LoginManager::Login(const char* id, const char* pass) {
	SearchUser = UserList->GetHead()->GetNext();
	// 순회 노드에 첫 노드를 저장
	bool flug = false;

	while (SearchUser) { // 순회 시작
		if (!strcmp(SearchUser->GetData()->GetId(), id)) { // 만약 유저 리스트에 입력 받은 아이디가 있다면
			flug = true; // 부울형 참
			break; // 순회 중단
		}
		SearchUser = SearchUser->GetNext(); // 다음 노드로
	}

	// 유저 정보를 찾지 못했을 경우
	if (!flug) {
		return false;
	}

	// 패스워드까지 일치한다면
	if (!strcmp(SearchUser->GetData()->GetPass(), pass)) {
		NowUser = SearchUser->GetData(); // 현재 접속중인 유저의 객체에 저장
		NowUser->Login(); // 로그인 상태
		return true;
	}

	// 패스워드 불일치 시
	return false;
}

// 로그아웃
void LoginManager::LogOut() {
	NowUser->LogOut(); // 로그아웃 상태
	NowUser = nullptr; // 초기화
}

// 삭제
void LoginManager::Delete() {
	UserList->Remove(NowUser); // 현재 접속중인 유저 정보를 삭제한다.
	NowUser = nullptr; // 초기화
}

// 순회 노드 초기화
void LoginManager::SearchEnd() {
	SearchUser = nullptr;
}

// 유저 리스트 순회
bool LoginManager::GetUser(User** temp) {
	if (SearchUser == nullptr) { // 순회 노드가 nullptr 라면
		SearchUser = UserList->GetHead(); // 순회 노드의 위치를 첫 노드로
	}

	SearchUser = SearchUser->GetNext(); // 순회 시작

	if (SearchUser != nullptr) {	// 노드를 만나면
		*temp = SearchUser->GetData(); // 매개 변수에게 노드의 데이터를 넘겨줌
		return true;
	}
	return false;
}
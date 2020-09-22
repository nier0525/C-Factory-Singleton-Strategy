#include "CharacterManager.h"

CharacterManager* CharacterManager::mPthis = nullptr;

CharacterManager* CharacterManager::GetInstance() {
	if (!mPthis) {
		mPthis = new CharacterManager();
	}

	OakFactory::GetInstance();
	ElfFactory::GetInstance();

	return mPthis;
}

void CharacterManager::Destroy() {
	OakFactory::Destroy();
	ElfFactory::Destroy();

	if (mPthis) {
		delete mPthis;
	}
}

void CharacterManager::Init() {

}

// 캐릭터 생성 담당
bool CharacterManager::CreateCharacter(const char* _name, CharacterFactory* charater) {
	User* user = LoginManager::GetInstance()->GetNowUser(); // 현재 접속중인 유저를 저장

	if (!user->CharacterCountCheak()) { // 유저의 최대 캐릭터 보유량이 초과했을 경우
		return false;
	}

	Character* ptr = nullptr;	// 캐릭터 임시 포인터 변수

	// 매게 변수로 받은 이름이 현재 유저가 보유하고 있는 캐릭터와 중복이 있는 지 검사
	while (user->GetCharacter(&ptr)) {
		if (!strcmp(ptr->GetNickName(), _name)) {	// 중복이 있다면
			user->SearchEnd();	// 노드 위치 초기화 후
			return false;	// false 리턴
		}
	}

	user->SearchEnd();	// 노드 위치 초기화

	user->NewCharacter(charater->MakeCharacter(_name));	
	// 중복이 없다면 매게 변수로 받은 이름으로 캐릭터 팩토리 클래스에서 캐릭터를 생성해준다.
	// 종족 선택은 UI 에서 팩토리 패턴을 통해 매개 변수로 넘겨주기 때문에 여기서 할 필요가 없다.
	return true;
}


// 캐릭터 선택을 담당하는 메소드
bool CharacterManager::SelectCharacter(const char* _name) {
	User* user = LoginManager::GetInstance()->GetNowUser();	// 현재 접속중인 유저를 저장

	if (user->GetCount() == NODATA) {	// 유저가 캐릭터를 하나도 보유하고 있지 않다면
		return false;
	}

	Character* ptr = nullptr;	// 캐릭터 임시 포인터 변수

	// 매개 변수로 받은 이름으로 유저가 보유중인 캐릭터 중 선택 할 캐릭터를 찾는다.
	while (user->GetCharacter(&ptr)) {
		if (!strcmp(ptr->GetNickName(), _name)) {	// 캐릭터를 찾았다면
			NowCharacter = ptr;	// 캐릭터를 접속 상태가 되므로 현재 접속한 캐릭터를 위한 변수에 저장
			user->SearchEnd();	// 노드 위치 초기화
			return true;
		}
	}
	// 끝까지 돌았다면 못찾은 것.
	user->SearchEnd();	// 노드 위치 초기화
	return false;
}

// 캐릭터 삭제 담당 메소드
bool CharacterManager::DropCharacter(const char* _name) {
	User* user = LoginManager::GetInstance()->GetNowUser();	// 현재 접속중인 유저를 저장

	if (user->GetCount() == NODATA) {	// 유저가 캐릭터를 하나도 보유하고 있지 않다면
		return false;
	}

	Character* ptr = nullptr;	// 캐릭터 임시 포인터 변수

	// 매개 변수로 받은 이름으로 유저가 보유중인 캐릭터 중 삭제 할 캐릭터를 찾는다.
	while (user->GetCharacter(&ptr)) {
		if (!strcmp(ptr->GetNickName(), _name)) {	// 캐릭터를 찾았다면
			user->DelCharacter(ptr); // 유저의 캐릭터 리스트에서 해당 캐릭터를 삭제한다.
			user->SearchEnd();		// 노드 위치 초기화
			return true;
		}
	}
	// 끝까지 돌았다면 못찾은 것.
	user->SearchEnd();	// 노드 위치 초기화
	return false;
}

// 아래는 UI 에서 캐릭터의 능력치와 캐릭터의 인벤토리를 출력하기 위한 메소드이다.
// 다이나믹 캐스트 검사를 통해 클래스형을 분별하고 그에 따라 적절한 값을 출력함.

void CharacterManager::PrintCharacter(HDC hdc, int x, int y) {
	char level[CHAR];
	char att[CHAR];
	char def[CHAR];
	char hp[CHAR];
	char mp[CHAR];
	char money[CHAR];

	// int -> char 변환
	// TextOut 은 오로지 문자열만 출력함..
	wsprintf(level, "%d", NowCharacter->GetLevel());
	wsprintf(att, "%d", NowCharacter->GetAtt());
	wsprintf(def, "%d", NowCharacter->GetDef());
	wsprintf(hp, "%d", NowCharacter->GetHp());
	wsprintf(mp, "%d", NowCharacter->GetMp());
	wsprintf(money, "%d", NowCharacter->GetMoney());

	Rectangle(hdc, 30, 30, 180, 300);

	// 이름
	TextOut(hdc, 35, 45, TEXT("Name : "), 7);
	TextOut(hdc, 90, 45, NowCharacter->GetNickName(), strlen(NowCharacter->GetNickName()));

	// 종족
	TextOut(hdc, 35, 65, TEXT("Brood : "), 8);
	if (dynamic_cast<Oak*>(NowCharacter)) {
		TextOut(hdc, 90, 65, TEXT("Oak"), 3);
	}
	if (dynamic_cast<Elf*>(NowCharacter)) {
		TextOut(hdc, 90, 65, TEXT("Elf"), 3);
	}

	// 레벨
	TextOut(hdc, 35, 85, TEXT("Level : "), 8);
	TextOut(hdc, 90, 85, level, strlen(level));

	// 공격력
	TextOut(hdc, 35, 105, TEXT("Attack : "), 9);
	TextOut(hdc, 90, 105, att, strlen(att));

	// 방어력
	TextOut(hdc, 35, 125, TEXT("Defence : "), 10);
	TextOut(hdc, 100, 125, def, strlen(def));

	// 체력
	TextOut(hdc, 35, 145, TEXT("Health : "), 9);
	TextOut(hdc, 90, 145, hp, strlen(hp));

	// 마력
	TextOut(hdc, 35, 165, TEXT("Magic : "), 8);
	TextOut(hdc, 90, 165, mp, strlen(mp));

	// 소유하고 있는 돈
	TextOut(hdc, 35, 185, TEXT("Money : "), 8);
	TextOut(hdc, 90, 185, money, strlen(money));


	// 착용중인 장비들
	Rectangle(hdc, 180, 30, 450, 150);

	TextOut(hdc, 200, 40, TEXT("On Equipment"), 12);
	TextOut(hdc, 200, 80, TEXT("Wenpon : "), 9);
	TextOut(hdc, 200, 100, TEXT("Armor : "), 8);
	TextOut(hdc, 200, 120, TEXT("Accessories : "), 14);

	// 착용중인 장비들 이름
	TextOut(hdc, 270, 80, NowCharacter->GetMyWenpon()->GetItemName(), strlen(NowCharacter->GetMyWenpon()->GetItemName()));
	TextOut(hdc, 260, 100, NowCharacter->GetMyArmor()->GetItemName(), strlen(NowCharacter->GetMyArmor()->GetItemName()));
	TextOut(hdc, 300, 120, NowCharacter->GetMyAccessories()->GetItemName(), strlen(NowCharacter->GetMyAccessories()->GetItemName()));
}

void CharacterManager::ShowNowCharacterInven(HDC hdc, int x, int y) {
	char name[CHAR];
	char price[CHAR];
	char ability[CHAR];
	char ability2[CHAR];
	int i = 0;

	Item* ptr = nullptr;
	
	// 현재 접속중인 캐릭터의 인벤토리를 끝까지 순회한다.
	// 아이템이 없다면 당연히 아무것도 출력되지 않는다.
	while(NowCharacter->GetItem(&ptr)) {

		// 문자열 변환을 위한 함수
		wsprintf(name, ptr->GetItemName());
		wsprintf(price, "%d", ptr->GetPrice());
		wsprintf(ability, "%d", ptr->GetFirstAbility());
		wsprintf(ability2, "%d", ptr->GetSecordAbility());

		// 다이나믹 캐스트를 통한 분별을 한 이유는 각각 장비마다 향상되는 능력이 다르기 때문에 분별했다.
		if (dynamic_cast<Wenpon*>(ptr)) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 510, 230 + (20 * i), TEXT("Att + "), 6);
			TextOut(hdc, 540, 230 + (20 * i), ability, strlen(ability));
		}
		if (dynamic_cast<Armor*>(ptr)) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 500, 230 + (20 * i), TEXT("Def + "), 6);
			TextOut(hdc, 540, 230 + (20 * i), ability, strlen(ability));
		}
		if (dynamic_cast<Accessories*>(ptr)) {
			TextOut(hdc, 220, 230 + (20 * i), name, strlen(name));
			TextOut(hdc, 380, 230 + (20 * i), price, strlen(price));
			TextOut(hdc, 450, 230 + (20 * i), TEXT("HP / MP + "), 10);
			TextOut(hdc, 520, 230 + (20 * i), ability, strlen(ability));
			TextOut(hdc, 550, 230 + (20 * i), TEXT(" / "), 3);
			TextOut(hdc, 560, 230 + (20 * i), ability2, strlen(ability2));
		}
		// i 정수는 while 문이 한 번 돈 이후에 출력하는 문자열들의 y 축을 증가 시키기 위함.
		i++;
	}

	// 노드 초기화
	NowCharacter->SearchEnd();
}
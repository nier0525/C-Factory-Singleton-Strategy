#include "FileDataBase.h"
#include "Mouse.h"
IMPLEMENT_SINGLETON(FileDataSystem)

struct SUser {
	char id[CHAR];
	char pass[CHAR];
	int  count;
}user_s;

struct SCharacter {
	char name[CHAR];
	int level;
	int hp;
	int mp;
	int att;
	int def;
	int money;
}character_s;

struct SWenpon {
	char name[CHAR];
	int price;
	int att;
}wenpon_s;

struct SArmor {
	char name[CHAR];
	int price;
	int def;
}armor_s;

struct SAccessories {
	char name[CHAR];
	int price;
	int hp;
	int mp;
}accessories_s;

struct Code {
	int character_code;
	int item_code;
	int item_count;
}code;

bool FileDataSystem::DataLoad() {
	LoginManager::GetInstance()->Init();
	FILE* fp = fopen("UserData.dll", "rb");

	if (fp == nullptr) {
		return false;
	}

	while (1) {
		if (!feof(fp)) {
			// 데이터 호출
			// 유저 정보
			fgets(user_s.id, CHAR, fp);
			user_s.id[strlen(user_s.id) - 1] = '\0';

			fgets(user_s.pass, CHAR, fp);
			user_s.pass[strlen(user_s.pass) - 1] = '\0';

			fscanf(fp, "%d\n", &user_s.count);

			Item* item = nullptr;
			Character* character = nullptr;

			User* user = new User(user_s.id, user_s.pass);
			user->SetCount(user_s.count);

			// 캐릭터 정보
			if (user_s.count != 0) {
				for (int i = 0; i < user_s.count; i++) {
					fscanf(fp, "%d\n", &code.character_code);

					fgets(character_s.name, CHAR, fp);
					character_s.name[strlen(character_s.name) - 1] = '\0';
					fscanf(fp, "%d %d %d %d %d %d\n", &character_s.level, &character_s.hp, &character_s.mp,
						&character_s.att, &character_s.def, &character_s.money);

					fgets(wenpon_s.name, CHAR, fp);
					wenpon_s.name[strlen(wenpon_s.name) - 1] = '\0';
					fscanf(fp, "%d %d\n", &wenpon_s.price, &wenpon_s.att);
					
					fgets(armor_s.name, CHAR, fp);
					armor_s.name[strlen(armor_s.name) - 1] = '\0';
					fscanf(fp, "%d %d\n", &armor_s.price, &armor_s.def);

					fgets(accessories_s.name, CHAR, fp);
					accessories_s.name[strlen(accessories_s.name) - 1] = '\0';
					fscanf(fp, "%d %d %d\n", &accessories_s.price, &accessories_s.hp, &accessories_s.mp);

					fscanf(fp, "%d\n", &code.item_count);

					if (code.character_code == OAK) {
						character = new Oak();

						character->SetNickName(character_s.name);
						character->SetLevel(character_s.level);
						character->SetHp(character_s.hp);
						character->SetMp(character_s.mp);
						character->SetAtt(character_s.att);
						character->SetDef(character_s.def);
						character->SetMoney(character_s.money);
						character->SetItemCount(code.item_count);

						character->SetMyWenpon(wenpon_s.name, wenpon_s.price, wenpon_s.att);
						character->SetMyArmor(armor_s.name, armor_s.price, armor_s.def);
						character->SetMyAccessories(accessories_s.name, accessories_s.price, accessories_s.hp, accessories_s.mp);

						if (code.item_count != 0) {
							for (int j = 0; j < code.item_count; j++) {
								fscanf(fp, "%d\n", &code.item_code);

								if (code.item_code == WENPON) {
									fgets(wenpon_s.name, CHAR, fp);
									wenpon_s.name[strlen(wenpon_s.name) - 1] = '\0';
									fscanf(fp, "%d %d\n", &wenpon_s.price, &wenpon_s.att);

									character->LoadInvenItem(new Wenpon(wenpon_s.name, wenpon_s.price, wenpon_s.att));
								}

								if (code.item_code == ARMOR) {
									fgets(armor_s.name, CHAR, fp);
									armor_s.name[strlen(armor_s.name) - 1] = '\0';
									fscanf(fp, "%d %d\n", &armor_s.price, &armor_s.def);

									character->LoadInvenItem(new Armor(armor_s.name, armor_s.price, armor_s.def));
								}

								if (code.item_code == ACCESSORIES) {
									fgets(accessories_s.name, CHAR, fp);
									accessories_s.name[strlen(accessories_s.name) - 1] = '\0';
									fscanf(fp, "%d %d %d\n", &accessories_s.price, &accessories_s.hp, &accessories_s.mp);

									character->LoadInvenItem(new Accessories(accessories_s.name, accessories_s.price, accessories_s.hp, accessories_s.mp));
								}
							}
						}

						user->LoadCharacter(character);
					}

					if (code.character_code == ELF) {
						character = new Elf();

						character->SetNickName(character_s.name);
						character->SetLevel(character_s.level);
						character->SetHp(character_s.hp);
						character->SetMp(character_s.mp);
						character->SetAtt(character_s.att);
						character->SetDef(character_s.def);
						character->SetMoney(character_s.money);
						character->SetItemCount(code.item_count);

						character->SetMyWenpon(wenpon_s.name, wenpon_s.price, wenpon_s.att);
						character->SetMyArmor(armor_s.name, armor_s.price, armor_s.def);
						character->SetMyAccessories(accessories_s.name, accessories_s.price, accessories_s.hp, accessories_s.mp);

						if (code.item_count != 0) {
							for (int j = 0; j < code.item_count; j++) {
								fscanf(fp, "%d\n", &code.item_code);

								if (code.item_code == WENPON) {
									fgets(wenpon_s.name, CHAR, fp);
									wenpon_s.name[strlen(wenpon_s.name) - 1] = '\0';
									fscanf(fp, "%d %d\n", &wenpon_s.price, &wenpon_s.att);

									character->LoadInvenItem(new Wenpon(wenpon_s.name, wenpon_s.price, wenpon_s.att));
								}

								if (code.item_code == ARMOR) {
									fgets(armor_s.name, CHAR, fp);
									armor_s.name[strlen(armor_s.name) - 1] = '\0';
									fscanf(fp, "%d %d\n", &armor_s.price, &armor_s.def);

									character->LoadInvenItem(new Armor(armor_s.name, armor_s.price, armor_s.def));
								}

								if (code.item_code == ACCESSORIES) {
									fgets(accessories_s.name, 100, fp);
									accessories_s.name[strlen(accessories_s.name) - 1] = '\0';
									fscanf(fp, "%d %d %d\n", &accessories_s.price, &accessories_s.hp, &accessories_s.mp);

									character->LoadInvenItem(new Accessories(accessories_s.name, accessories_s.price, accessories_s.hp, accessories_s.mp));
								}
							}
						}
						user->LoadCharacter(character);
					}
				}
			}			
			LoginManager::GetInstance()->LoadUserList(user);
			//MessageBox(CMouse::GetInstance()->GetHWnd(), "데이터 로드 완료", "Load Complete", MB_OK);
		}
		else {
			break;
		}
	}

	fclose(fp);
	return true;
}

void FileDataSystem::DataSave() {
	FILE* fp = fopen("UserData.dll", "wb");


	User* user = nullptr;
	Character* charater = nullptr;
	Item* item = nullptr;

	LoginManager::GetInstance()->SearchEnd();

	if (fp == nullptr) {
		return;
	}

	if (fp) {
		while (LoginManager::GetInstance()->GetUser(&user)) {
			if (strcmp(user->GetId(), "") && strcmp(user->GetPass(), "")) {
				fprintf(fp, "%s\n%s\n%d\n", user->GetId(), user->GetPass(), user->GetCount());

				while (user->GetCharacter(&charater)) {
					if (strcmp(charater->GetNickName(), "")) {
						// 캐릭터 정보
						if (dynamic_cast<Oak*>(charater)) {
							fprintf(fp, "%d\n", OAK);
						}
						if (dynamic_cast<Elf*>(charater)) {
							fprintf(fp, "%d\n", ELF);
						}

						fprintf(fp, "%s\n", charater->GetNickName());
						fprintf(fp, "%d %d %d %d %d %d\n", charater->GetLevel(),
							charater->GetHp(), charater->GetMp(), charater->GetAtt(), charater->GetDef(), charater->GetMoney());


						// 캐릭터 착용 무기
						fprintf(fp, "%s\n", charater->GetMyWenpon()->GetItemName());
						fprintf(fp, "%d %d\n", charater->GetMyWenpon()->GetPrice(), charater->GetMyWenpon()->GetFirstAbility());
						
						fprintf(fp, "%s\n", charater->GetMyArmor()->GetItemName());
						fprintf(fp, "%d %d\n", charater->GetMyArmor()->GetPrice(), charater->GetMyArmor()->GetFirstAbility());
					
						fprintf(fp, "%s\n", charater->GetMyAccessories()->GetItemName());
						fprintf(fp, "%d %d %d\n", charater->GetMyAccessories()->GetPrice(), charater->GetMyAccessories()->GetFirstAbility(), charater->GetMyAccessories()->GetSecordAbility());

						fprintf(fp, "%d\n", charater->GetItemCount());

						while (charater->GetItem(&item)) {
							if (strcmp(item->GetItemName(), "")) {
								if (dynamic_cast<Wenpon*>(item)) {
									fprintf(fp, "%d\n", WENPON);
									fprintf(fp, "%s\n%d %d\n", item->GetItemName(), item->GetPrice(), item->GetFirstAbility());
								}
								if (dynamic_cast<Armor*>(item)) {
									fprintf(fp, "%d\n", ARMOR);
									fprintf(fp, "%s\n%d %d\n", item->GetItemName(), item->GetPrice(), item->GetFirstAbility());
								}
								if (dynamic_cast<Accessories*>(item)) {
									fprintf(fp, "%d\n", ACCESSORIES);
									fprintf(fp, "%s\n%d %d %d\n", item->GetItemName(), item->GetPrice(), item->GetFirstAbility(),
										item->GetSecordAbility());
								}
							}
						}
					}
				}

			}
		}
	}	

	//MessageBox(CMouse::GetInstance()->GetHWnd(), "데이터 저장 완료", "Save Complete", MB_OK);
	fclose(fp);
}
#include "MainManager.h"

MainManager* MainManager::pthis = nullptr;

MainManager* MainManager::GetInstance() {
	if (!pthis) {
		pthis = new MainManager();
	}

	LoginMenu::GetInstance();
	CharacterMenu::GetInstance();
	GameMenu::GetInstance();

	return pthis;
}

void MainManager::Destory() {
	LoginMenu::Destory();
	CharacterMenu::Destory();
	GameMenu::Destroy();

	if (pthis) {
		delete pthis;
	}
}

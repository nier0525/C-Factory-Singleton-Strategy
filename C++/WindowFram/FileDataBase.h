#pragma once

#include <fstream>
#include "LoginManager.h"
#include "CharacterManager.h"
#include "ItemStore.h"

class FileDataSystem {
	DECLARE_SINGLETONE(FileDataSystem)
private:
	FileDataSystem() {
		index = 0;
	}
	~FileDataSystem() {}

	int index;
public:
	void DataSave();
	bool DataLoad();
};
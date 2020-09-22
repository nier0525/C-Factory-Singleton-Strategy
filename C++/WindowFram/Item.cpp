#include "Item.h"

// 생성자 초기화 작업
Item::Item(const char* _name, int _price) {
	strcpy(name, _name);
	memset(code, 0, sizeof(code));
	price = _price;
}

Item::~Item() {

}

//----------------------------------------------

// 읽기 접근자
const char* Item::GetItemName() {
	return name;
}

const char* Item::GetItemCode() {
	return code;
}

int Item::GetPrice() {
	return price;
}

//----------------------------------------------